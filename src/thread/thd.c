#include "thd.h"
#include <linux/kthread.h>
#include <linux/ktime.h>

static int
    do_run
        (any_t arg)                                    {
            if (pp_trait_of(arg) != pp_thd_t) return -1;
            pp_thd *thd = (pp_thd*) arg;

            thd->ret  = pp_task_run(thd->task);
            thd->stat = pp_fut_ready          ;
            return 0;
}

static bool_t
    do_new
        (pp_thd* self, u32_t count, va_list arg)                               {
            const char *name = null_t; if (count > 0) name = va_arg(arg, any_t);
            pp_task    *task = null_t; if (count > 1) task = va_arg(arg, any_t);
            if (pp_trait_of(task) != pp_task_t) return false_t;

            self->task = (pp_task*) pp_ref(task);
            self->stat = pp_fut_pend;

            self->thd  = kthread_run (do_run, (any_t) self, name);
            if (!self->thd) return false_t;
            return true_t;
}

static bool_t
    do_clone
        (pp_thd* par, pp_thd* par_clone) {
            return false_t;
}

static void
    do_del
        (pp_thd* self)                                     {
            for ( ; self->stat == pp_fut_pend ; schedule());
            pp_del(self->task);
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_thd),
        null_t
);

pp_obj_trait *pp_thd_t = &do_obj;

static u64_t do_poll(pp_thd* self) { if (pp_trait_of(self) != pp_thd_t) return pp_fut_err; return self->stat; }
static any_t do_ret (pp_thd* self) { if (pp_trait_of(self) != pp_thd_t) return null_t;     return self->ret ; }

static pp_fut_ops
    do_fut = pp_make_fut_ops (
        do_poll,
        do_ret
);

pp_fut*
    pp_thd_fut
        (pp_thd* self)                                      {
            if (pp_trait_of(self) != pp_thd_t) return null_t;
            return pp_make (pp_fut) from     (
                2      ,
                &do_fut,
                self
            );
}


#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_thd_fut);
EXPORT_SYMBOL(pp_thd_t);