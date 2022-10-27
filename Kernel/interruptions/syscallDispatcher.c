// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <syscalls.h>
#include <stdint.h>
#include <stddef.h>
#include <syscalls.h>
#include <naiveConsole.h>

static int syscallnumber;

void syscallsetter(int64_t syscall){
	syscallnumber = syscall;
}

int64_t syscallDispatcher(int64_t arg0, int64_t arg1, int64_t arg2) {
    switch (syscallnumber)
    {
    case 1:
        return read((int) arg0, (char*) arg1, (size_t) arg2);
    case 2:
        return write((int) arg0, (const char*) arg1, (size_t) arg2);
    case 3:
        clear();
        break;
    case 4:
	   	printMem((uint64_t) arg0,(unsigned char*)arg1);
		break;
    case 5:
        inforeg((registersT*)arg0);
        break;
    case 6:
        return date((char)arg0);
	case 7:
		sleep((int)arg0);
		break;
	case 8:
		return getLast();
    case 9:
        snapshotRegs();
        break;
    case 10:
        return malloc((unsigned int)arg0);
        break;
    case 11:
        mfree((void *)arg0);
        break;
    case 12:
        mStatus((void *)arg0);
        break;
    default:
        return -1;
    }
    return -1;
}
