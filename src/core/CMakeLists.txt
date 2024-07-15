add_kernel_source     (
    popcorn-linux-core

    atom.c
    bit.c
    heap_atomic.c
    heap.c
    mem.c
    mod.c
    print.c
    this.c

    class.h
    class.c

    dev.h
    dev.c

    work.h
    work.c

    wait.h
    wait.c

    ua.h
    ua.c
)

inc                           (
    popcorn-linux-core-include
    ../../include/core/class.h
    ../../include/core/wait.h
    ../../include/core/work.h
    ../../include/core/dev.h
    ../../include/core/ua.h
)