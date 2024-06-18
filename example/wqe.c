#include <core.h>
#include <core/work.h>
#include <thread.h>

#include <linux/module.h>

static void
    do_run
        (const char* arg) {
            po_info(arg);
}

static int
    mod_init (void)                                                   {
        po_task *run = po_make (po_task) from (2, do_run, "Hello WQE");
        po_wqe  *wqe = po_make (po_wqe)  from (1, run);

        po_await(po_wqe_fut(wqe));
        po_del  (run);
        po_del  (wqe);
        return 0;
}

static void
    mod_exit (void)                   {
        po_info ("Goodbye Popcorn !!");
}

module_init(mod_init)
module_exit(mod_exit)

MODULE_LICENSE("GPL");