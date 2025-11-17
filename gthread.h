#ifndef _GTHREADH_
#define _GTHREADH_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define     _GT_MAX_GTHREAD_COUNT_      32
#define     _GT_STACK_SIZE_FOR_THREAD_  4096

typedef uint8_t     u8;
typedef int8_t      i8;
typedef uint16_t    u16;
typedef int16_t     i16;
typedef uint32_t    u32;
typedef int32_t     i32;
typedef uint64_t    u64;
typedef int64_t     i64;

typedef char*       stack_t;
typedef uint64_t    x64_reg;
typedef uint64_t*   stack_ptr;
typedef int32_t     x32_reg;

typedef enum {
    ST_RUNNING,
    ST_BLOCKED,
    ST_TERMINATED,
    ST_READY
} thread_status_t;

typedef struct gthread_t {
// registers
    stack_t thread_stack_start_ptr;
    x64_reg rsp;
    x64_reg rbp;
    x64_reg rbx;
    x64_reg r12;
    x64_reg r13; 
    x64_reg r14;
    x64_reg r15;

    thread_status_t status;
    i16 prio;
    u32 id;
} gthread_t;

typedef struct gthread_scheduler_t {
    gthread_t gthread_queue[
            _GT_MAX_GTHREAD_COUNT_
        ];
    i32 gthread_count;
    u32 gthread_current; // current working gthread
} gthread_scheduler_t;

static gthread_scheduler_t 
gthread_main_scheduler = (gthread_scheduler_t){
    .gthread_count = -1,
    .gthread_current = UINT32_MAX
};

void gthread_main_scheduler_init(
        void
    );
i8 gthread_create(
        gthread_scheduler_t*,   // pointer to object of gthread_scheduler
                                // if == NULL, then will used gthread_main_sheduler

        gthread_t*,             // pointer to object of gthread
        const i16,              // gthread priority
        void (*)(void*),        // gthread function
        void*                   // count of arguments in function
    );
void gthread_yield(
        gthread_t*              // pointer to object of gthread
    );
void gthread_term(
        gthread_scheduler_t*,   // pointer to object of gthread_scheduler
                                // if == NULL, then will used gthread_main_sheduler

        gthread_t*              // pointer to object of gthread
    );

#ifdef __cplusplus
}
#endif

#endif //_GTHREADH_