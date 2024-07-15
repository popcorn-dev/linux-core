#include "work.h"
#include <linux/sched.h>

static void
    do_run
        (struct work_struct* par)                         {
            pp_wqe* self = container_of(par, pp_wqe, work);

            if (pp_trait_of(self) != pp_wqe_t) return;
            self->ret  = pp_task_run(self->task);
            self->stat = pp_fut_ready;
}

static bool_t
    do_new
        (pp_wqe* self, u32_t count, va_list arg)                            {
            pp_task *task = null_t; if (count > 0) task = va_arg(arg, any_t);
            if (pp_trait_of(task) != pp_task_t) return false_t;
            INIT_WORK(&self->work, do_run);

            self->task = (pp_task*) pp_ref (task);
            self->stat = pp_fut_pend;
            self->ret  = null_t;

            if(!schedule_work(&self->work)) goto err;
            return true_t;
    err:    pp_del (self->task);
            return false_t;
}

static bool_t
    do_clone
        (pp_wqe* self, pp_wqe* clone)     {
            INIT_WORK(&self->work, do_run);

            self->task = (pp_task*) pp_ref (clone->task);
            self->stat = pp_fut_pend;
            self->ret  = null_t;

            if (!schedule_work(&self->work)) goto err;
            return true_t;
    err:    pp_del (self->task);
            return false_t;
}

static void
    do_del
        (pp_wqe* self)                                     {
            for ( ; self->stat == pp_fut_pend ; schedule());
            pp_del (self->task);
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_wqe),
        null_t
);

pp_obj_trait *pp_wqe_t = &do_obj;

static u64_t do_poll(pp_wqe* self) { if (pp_trait_of(self) != pp_wqe_t) return pp_fut_err; return self->stat; }
static any_t do_ret (pp_wqe* self) { if (pp_trait_of(self) != pp_wqe_t) return null_t;     return self->ret; }

static pp_fut_ops
    do_fut = pp_make_fut_ops (
    do_poll,
    do_ret
);

pp_fut*
    pp_wqe_fut
        (pp_wqe* self)                                      {
            if (pp_trait_of(self) != pp_wqe_t) return null_t;
            return pp_make (pp_fut) from     (
                2      ,
                &do_fut,
                self
            );
}

EXPORT_SYMBOL(pp_wqe_fut);
EXPORT_SYMBOL(pp_wqe_t);