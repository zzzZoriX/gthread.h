#include "gthread.h"

i8 gthread_create(
        gthread_scheduler_t* sch, 
        gthread_t* gth, 
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

    return 0;
}