// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <MemoryManagerWrapper.h>
#include <naiveConsole.h>
#include <pipes.h>
#include <scheduler.h>
#include <semaphore.h>
#include <syscalls.h>
#include <time.h>

#define STDIN 1
#define DEFAULT_RETVALUE -1
#define F1 17
#define F2 18

static char mayusc = 0;
unsigned char last;

registersT primary, secondary;
registersT *primaryBackup = &primary;
registersT *secondaryBackup = &secondary;

int64_t write(const char *buffer, size_t count) {
  fd *stdout = getCurrentStdout();

  if (!stdout) {
    for (int i = 0; i < count; i++) {
      if (buffer[i] == '~') {
        ncTogglePrintColor();
      } else {
        ncPrintChar(buffer[i]);
      }
    }
  } else {
    pipeWrite(stdout, buffer);
  }
  return count;
}

int64_t read(char *buffer, size_t count) {
  int k = 0;
  unsigned char key;
  fd *stdin = getCurrentStdin();
  pcb *currentProcess = getCurrentProcess();

  if (stdin == NULL && currentProcess->priority != 1) {
    buffer[0] = 0;
    return 0;
  }

  while (k < count || count == -1) {
    if (!stdin) {
      addToKeyboardList();
      key = readKey();
    } else {
      key = (unsigned char)pipeRead(stdin, NULL, 1);
    }

    switch (key) {
      case (unsigned char)-1:
        return -1;

      case 0:
        if (!stdin)
          continue;
        else {
          buffer[k] = 0;
          return k;
        }
        break;

      case '\n':
        if (!stdin) {
          ncNewline();
        }
        buffer[k] = 0;
        return k;

      case 8:
      {
        if (k > 0) {
          ncDeleteChar();
          k--;
        }
        break;
      }

      case 14:
      case 15:
        mayusc = 1;
        break;

      case F1:
        loadBackupRegs(primaryBackup, secondaryBackup);
        break;

      case F2:
        if (getCurrentPID() != 1) exitProcess();
        break;

      case 170:
      case 182:
        mayusc = 0;
        break;

      default:
        if (mayusc) key = toMayusc(key);
        if (k < 100) buffer[k] = key;
        if (!stdin && count != 1) ncPrintChar(key);
        k++;
        break;
    }
  }
  buffer[k] = 0;
  return k;
}

void snapshotRegs() { loadBackupRegs(primaryBackup, secondaryBackup); }

void clear() { ncClear(); }

int64_t date(char value) { return rtcGetter(value); }

void loadBackupRegs(registersT *regs, registersT *backup) {
  regs->rax = backup->rax;
  regs->rbx = backup->rbx;
  regs->rcx = backup->rcx;
  regs->rdx = backup->rdx;
  regs->rbp = backup->rbp;
  regs->rdi = backup->rdi;
  regs->rsi = backup->rsi;
  regs->r8 = backup->r8;
  regs->r9 = backup->r9;
  regs->r10 = backup->r10;
  regs->r11 = backup->r11;
  regs->r12 = backup->r12;
  regs->r13 = backup->r13;
  regs->r14 = backup->r14;
  regs->r15 = backup->r15;
}

void saveBackup() { saveRegisters(secondaryBackup); }

void inforeg(registersT *regs) { loadBackupRegs(regs, primaryBackup); }

int64_t getLast() { return last; }

void sleep(int ms) { tSleep(ms); }

void exitProcess() {
  closeFd(getCurrentStdin());
  closeFd(getCurrentStdout());
  exitCurrentProcess();
  runScheduler();
}