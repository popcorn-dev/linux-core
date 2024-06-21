#include "wait.h"

po_obj_trait po_wait_trait = po_make_trait (
    po_wait_new    ,
    po_wait_clone  ,
    null_t         ,
    po_wait_del    ,
    sizeof(po_wait),
    null_t
);

po_obj_trait *po_wait_t = &po_wait_trait;

bool_t
    po_wait_new
        (po_wait* self, u32_t count, va_list arg) {
            init_waitqueue_head(&self->wait);
            return true_t;
}

bool_t po_wait_clone(po_wait* self, po_wait* clone) { return false_t; }
void   po_wait_del  (po_wait* self)                 {                 }

bool_t
    po_wait_on_timeout
        (po_wait* self, bool_t intr, u64_t time)              {
            if (po_trait_of(self) != po_wait_t) return false_t;
            u64_t ret = -1;
            po_ref (self);

            if (intr == 1) ret = wait_event_interruptible_timeout(self->wait, true_t, time);
            if (intr == 0) ret = wait_event_timeout              (self->wait, true_t, time);

            if (ret == -1) return false_t;
            po_del (self);
            return true_t;
}

void
    po_wait_on
        (po_wait* self, bool_t intr)                  {
            if (po_trait_of(self) != po_wait_t) return;
            po_ref (self);

            if (intr == 1) wait_event_interruptible(self->wait, true_t);
            if (intr == 0) wait_event              (self->wait, true_t);
            po_del (self);
}

bool_t
    po_wake
        (po_wait* self, bool_t intr)                          {
            if (po_trait_of(self) != po_wait_t) return false_t;

            if (intr == 1) wake_up_interruptible(&self->wait);
            if (intr == 0) wake_up              (&self->wait);
            return true_t;
}

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_wait_t);
EXPORT_SYMBOL(po_wait_on_timeout);
EXPORT_SYMBOL(po_wait_on);
EXPORT_SYMBOL(po_wake);