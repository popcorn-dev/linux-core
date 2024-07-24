add_kernel_source       (
    popcorn-linux-thread

    mut.h
    mut.c

    thd.h
    thd.c
)

inc                           (
    popcorn-linux-thread
    ../../include/thread/thd.h
    ../../include/thread/mut.h
    ../../include/thread.h
)