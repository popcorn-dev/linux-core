#include "work.h"
#include <linux/sched.h>

po_obj_trait po_wqe_trait = po_make_trait (
    po_wqe_new    ,
    po_wqe_clone  ,
    null_t        ,
    po_wqe_del    ,
    sizeof(po_wqe),
    null_t
);

po_obj_trait *po_wqe_t = &po_wqe_trait;

static void
    do_run
        (struct work_struct* par)                         {
            po_wqe* self = container_of(par, po_wqe, work);

            if (po_trait_of(self) != po_wqe_t) return;
            self->ret  = po_task_run(self->task);
            self->stat = po_fut_ready;
}

bool_t
    po_wqe_new
        (po_wqe* self, u32_t count, va_list arg)                            {
            po_task *task = null_t; if (count > 0) task = va_arg(arg, any_t);
            if (po_trait_of(task) != po_task_t) return false_t;
            INIT_WORK(&self->work, do_run);

            self->task = (po_task*) po_ref (task);
            self->stat = po_fut_pend;
            self->ret  = null_t;

            if(!schedule_work(&self->work)) goto err;
            return true_t;
    err:    po_del (self->task);
            return false_t;
}

bool_t
    po_wqe_clone
        (po_wqe* self, po_wqe* clone)     {
            INIT_WORK(&self->work, do_run);

            self->task = (po_task*) po_ref (clone->task);
            self->stat = po_fut_pend;
            self->ret  = null_t;

            if (!schedule_work(&self->work)) goto err;
            return true_t;
    err:    po_del (self->task);
            return false_t;
}

void
    po_wqe_del
        (po_wqe* self)                                     {
            for ( ; self->stat == po_fut_pend ; schedule());
            po_del (self->task);
}

static u64_t
    do_poll
        (po_wqe* self)                                          {
            if (po_trait_of(self) != po_wqe_t) return po_fut_err;
            return self->stat;
}

static any_t
    do_ret
        (po_wqe* self)                                      {
            if (po_trait_of(self) != po_wqe_t) return null_t;
            return self->ret;
}

static po_fut_ops
    do_fut = po_make_fut_ops (
    do_poll,
    do_ret
);

po_fut*
    po_wqe_fut
        (po_wqe* self)                                      {
            if (po_trait_of(self) != po_wqe_t) return null_t;
            return po_make (po_fut) from     (
                2      ,
                &do_fut,
                self
            );
}

EXPORT_SYMBOL(po_wqe_fut);
EXPORT_SYMBOL(po_wqe_t);