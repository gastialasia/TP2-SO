#include "../include/test_util.h"
#include "../include/stdlib.h"
#include "../include/test_prio_2.h"

#define MAX_PROCESSES 3
#define MAX_ARGS 4
#define ARGS_COUNT 2

static void loop_prio(int argc, char argv[6][21]){
    if(argc != ARGS_COUNT){
        printf("Incorrect number of arguments for loop_prio\n");
        exit();
    }
    while(1){
        printf(argv[1]);
        putchar(' ');
        sleep(100);
    }
}

int test_prio_2(int argc, char argv[6][21]){
    if(argc != MAX_ARGS){
        printf("Incorrect number of arguments. You should input 3 numbers\n");
        exit();
    }
    int priority;
    char args[6][21];
    strcpy(args[0], "_loop_prio");
    
    for(int i=1; i<=MAX_PROCESSES; i++){
        strcpy(args[1], argv[i]);
        priority = atoi(argv[i]);
        createProcess((uint64_t)loop_prio, (uint8_t)priority, ARGS_COUNT, args, NULL, NULL);
    }
    exit();
    return 0;
}