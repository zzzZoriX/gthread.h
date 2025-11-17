#include <stdio.h>
#include "../gthread/gthread.h"

gthread_scheduler_t main_scheduler;

void work1(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 5; ++i){
        printf("id: %d : i: %d\n", id, i);
        gthread_yield(NULL);
    }
}

void work2(void* arg){
    char* msg = (char*)arg;
    for(int i = 0; i < 3; ++i){
        printf("msg: %s : i: %d\n", msg, i);
        gthread_yield(NULL);
    }
}

int
main(void) {
    gthread_scheduler_init(&main_scheduler);

    int a = 1;
    char* b = "Hello from gthread!";

    gthread_t gthread1, gthread2;

    gthread_create(
        NULL,
        &gthread1,
        12,
        work1,
        &a
    );

    gthread_create(
        NULL,
        &gthread2,
        13,
        work1,
        &b
    );

    gthread_run_most_priority(NULL);

    printf("\nEnd of programm!\n\n");

    return 0;
}