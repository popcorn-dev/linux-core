#include "wait.h"

static bool_t
    do_new
        (pp_wait* self, u32_t count, va_list arg) {
            init_waitqueue_head(&self->wait);
            return true_t;
}

static bool_t do_clone(pp_wait* self, pp_wait* clone) { return false_t; }
static void   do_del  (pp_wait* self)                 {                 }

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new         ,
        do_clone       ,
        null_t         ,
        do_del         ,
        sizeof(pp_wait),
        null_t
);

pp_obj_trait *pp_wait_t = &do_obj;

bool_t
    pp_wait_on_timeout
        (pp_wait* self, bool_t intr, u64_t time)              {
            if (pp_trait_of(self) != pp_wait_t) return false_t;
            u64_t ret = -1;
            pp_ref (self);

            if (intr == 1) ret = wait_event_interruptible_timeout(self->wait, true_t, time);
            if (intr == 0) ret = wait_event_timeout              (self->wait, true_t, time);

            if (ret == -1) return false_t;
            pp_del (self);
            return true_t;
}

void
    pp_wait_on
        (pp_wait* self, bool_t intr)                  {
            if (pp_trait_of(self) != pp_wait_t) return;
            pp_ref (self);

            if (intr == 1) wait_event_interruptible(self->wait, true_t);
            if (intr == 0) wait_event              (self->wait, true_t);
            pp_del (self);
}

bool_t
    pp_wake
        (pp_wait* self, bool_t intr)                          {
            if (pp_trait_of(self) != pp_wait_t) return false_t;

            if (intr == 1) wake_up_interruptible(&self->wait);
            if (intr == 0) wake_up              (&self->wait);
            return true_t;
}

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_wait_t);
EXPORT_SYMBOL(pp_wait_on_timeout);
EXPORT_SYMBOL(pp_wait_on);
EXPORT_SYMBOL(pp_wake);