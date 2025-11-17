#include "gthread.h"

void gthread_main_scheduler_init(void) {
    gthread_main_scheduler = (gthread_scheduler_t){
        .gthread_count = 0,
        .gthread_current = 0
    };

    memset(gthread_main_scheduler.gthread_queue, 0, sizeof(gthread_t));
}