## Green-Thread library

how to use?

create the scheduler object with type gthread_scheduler_t and use it in every gthread functions

ALSO

you can don't create the scheduler object and use NULL in every functions(even in gthread_scheduler_init),
and as scheduler will be used default scheduler, defined in gthread.h file

then, when you're decides which scheduler you will use, now you can create a gthread objects with type gthread_t

but it need to initialize. now, you must call function gthread_create which initialize your gthread object

after you're initializes a gthread and decides scheduler, you can call the gthread_run_(first/most_priority) function and after
it work you must call the gthread_term to terminate thread


## Typedefs

- u8 - unsigned int(1 byte)
- u16 - unsigned int(2 byte)
- u32 - unsigned int(4 byte)
- u64 - unsigned int(8 byte)

- i8 - int(1 byte)
- i16 - int(2 byte)
- i32 - int(4 byte)
- i64 - int(8 byte)

- stack_t - pointer to char
- stack_ptr - pointer to unsigned int(8 byte)

- x64_reg - unsigned int(8 byte)
- x32_reg - unsigned int(4 byte)


## Functions

- void gthread_scheduler_init(gthread_scheduler_t*) - initialize given scheduler with default value

- void gthread_run_first(gthread_scheduler_t*) - run first created thread
- void gthread_run_most_priority(gthread_scheduler_t*) - run thread with biggest priority

- gthread* gthread_get_first(gthread_scheduler_t*) - return first created gthread object
- gthread* gthread_get_most_priority(gthread_scheduler_t*) - return gthread object with biggest priority

- i8 gthread_create(gthread_scheduler_t*, gthread_t*, const i16, void (*)(void*), void*) - initialize given gthread object
- void gthread_yield(gthread_scheduler_t*) - switch currently working gthread to currently free

- void gthread_term(gthread_scheduler_t*) - terminate currently working
- void gthread_term(gthread_scheduler_t*) - terminate all threads