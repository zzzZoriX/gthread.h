#include "gthread.h"

void gthread_main_scheduler_init(gthread_scheduler_t* sch) {
    if(sch == NULL)
    // read gthread.h desc for first arg in this function
        sch = &gthread_main_scheduler;

    *sch = (gthread_scheduler_t){
        .gthread_count = 0,
        .gthread_current = -1
    };

    memset(sch->gthread_queue, 0, sizeof(gthread_t));
}

void gthread_run_first(gthread_scheduler_t* sch) {
    if(sch == NULL)
    // read gthread.h desc for first arg in this function
        sch = &gthread_main_scheduler;

    sch->gthread_queue[0].status = ST_RUNNING;
    sch->gthread_current = 0;
}

void gthread_run_most_priority(gthread_scheduler_t* sch) {
    if(sch == NULL)
    // read gthread.h desc for first arg in this function
        sch = &gthread_main_scheduler;

    i8 most_prio_gthread_id = gthread_get_most_priority(sch)->id;
    
    sch->gthread_queue[most_prio_gthread_id].status = ST_RUNNING;
    sch->gthread_current = most_prio_gthread_id;
}

gthread_t* gthread_get_first(gthread_scheduler_t* sch) {
    if(sch == NULL)
    // read gthread.h desc for first arg in this function
        sch = &gthread_main_scheduler;

    return &sch->gthread_queue[0];
}

gthread_t* gthread_get_most_priority(gthread_scheduler_t* sch) {
    if(sch == NULL)
    // read gthread.h desc for first arg in this function
        sch = &gthread_main_scheduler;

    i8 most_prio_gthread_id = 0;
    for(i8 i = 1; i < sch->gthread_count; ++i)
        if(sch->gthread_queue[i].prio > sch->gthread_queue[most_prio_gthread_id].prio)
            most_prio_gthread_id = i;

    return &sch->gthread_queue[most_prio_gthread_id];
}