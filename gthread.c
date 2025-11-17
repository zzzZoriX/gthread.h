#include "gthread.h"

i8 gthread_create(
        gthread_scheduler_t* sch, 
        gthread_t* gth, 
        const i16 prio,
        void (*work)(void *), 
        void* arg
) {

    if(sch == NULL)
    // read gthread.h desc for first arg in this function
        sch = &gthread_main_scheduler;

    if(sch->gthread_count + 1 > _GT_MAX_GTHREAD_COUNT_)
        return -1;

    u32 gth_id = ++sch->gthread_count;

    gth = &sch->gthread_queue[
                gth_id
            ];

    gth->thread_stack_start_ptr = (stack_t)malloc(_GT_STACK_SIZE_FOR_THREAD_);
    if(!gth->thread_stack_start_ptr)
        return -1;
    
    stack_ptr stack_top = (stack_ptr)(gth->thread_stack_start_ptr + _GT_STACK_SIZE_FOR_THREAD_);

    *(--stack_top) = (u64)work;
    *(--stack_top) = (u64)arg;
    *(--stack_top) = (u64)gthread_term;

    gth->rsp = (x64_reg)stack_top;

    gth->rbp = gth->rsp;
    gth->rbx = 0;
    gth->r12 = 0;
    gth->r13 = 0;
    gth->r14 = 0;
    gth->r15 = 0;

    gth->status = ST_READY;
    gth->id = gth_id;
    gth->prio = prio;

    return 0;
}

extern void gthread_switch(gthread_t* old, gthread_t* new);

void gthread_yield(
        gthread_scheduler_t* sch
) {
    if(sch == NULL)
    // read gthread.h desc for first arg in this function
        sch = &gthread_main_scheduler;

    u32 next_ready_gthread = 0;

    // this "while" equals to while(*same condition, but wo next_ready_gthread++*) ++next_ready_gthread;
    while(sch->gthread_queue[next_ready_gthread].status != ST_READY && next_ready_gthread++ != sch->gthread_current);

    if(next_ready_gthread == sch->gthread_current) return;

    // set new current working gthread
    u32 old_gthread_id = sch->gthread_current;
    sch->gthread_current = next_ready_gthread;

    if(old_gthread_id != UINT32_MAX) // check for object is initialized
        sch->gthread_queue[old_gthread_id].status = ST_READY;
    sch->gthread_queue[sch->gthread_current].status = ST_RUNNING;

    gthread_switch(
        &sch->gthread_queue[old_gthread_id],
        &sch->gthread_queue[sch->gthread_current]
    );
}