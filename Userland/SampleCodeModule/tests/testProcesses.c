#include <stdlib.h>
#include <testProcesses.h>
#include <testUtil.h>

void testProcesses(int argc, char argv[ARG_QTY][ARG_LEN]) {
  uint8_t rq;
  uint8_t alive = 0;
  uint8_t action;
  uint64_t maxProcesses;

  if (argc != 2) {
    printf("One argument expected: number of processes\n");
    exit();
    return;
  }

  if ((maxProcesses = atoi(argv[1])) <= 0) {
    printf("The argument must be a number greater than 0\n");
    exit();
    return;
  }

  p_rq prqs[maxProcesses];

  char aux[ARG_QTY][ARG_LEN];
  strcpy(aux[0], "_loop");

  while (1) {
    for (rq = 0; rq < maxProcesses; rq++) {
      prqs[rq].pid =
          createProcess((uint64_t)endlessLoop, 3, 1, aux, NULL, NULL);

      if (prqs[rq].pid == -1) {
        printf("testProcesses: ERROR creating process\n");
        return;
      } else {
        prqs[rq].state = RUNNING;
        alive++;
      }
    }

    ps();
    putchar('\n');
    sleep(2000);

    while (alive > 0) {
      for (rq = 0; rq < maxProcesses; rq++) {
        action = GetUniform(100) % 2;

        switch (action) {
          case 0:
            if (prqs[rq].state == RUNNING || prqs[rq].state == BLOCKED) {
              if (kill(prqs[rq].pid) == -1) {
                printf("testProcesses: ERROR killing process\n");
                return;
              }
              prqs[rq].state = KILLED;
              alive--;
            }
            break;

          case 1:
            if (prqs[rq].state == RUNNING) {
              if (block(prqs[rq].pid) == -1) {
                printf("testProcesses: ERROR blocking process\n");
                return;
              }
              prqs[rq].state = BLOCKED;
            }
            break;
        }
      }

      for (rq = 0; rq < maxProcesses; rq++) {
        if (prqs[rq].state == BLOCKED && GetUniform(100) % 2) {
          if (block(prqs[rq].pid) == -1) {
            printf("testProcesses: ERROR unblocking process\n");
            return;
          }
          prqs[rq].state = RUNNING;
        }
      }

      ps();
      putchar('\n');
      sleep(2000);
    }
  }
}
