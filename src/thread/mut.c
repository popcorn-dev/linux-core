#include "mut.h"

static bool_t do_new  (pp_mut* self, u32_t count, va_list arg) { mutex_init(&self->mut); return true_t; }
static bool_t do_clone(pp_mut* self, pp_mut* clone)            { return false_t; }
static void   do_del  (pp_mut* self)                           { mutex_destroy(&self->mut); }

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_mut),
        null_t
);

pp_obj_trait *pp_mut_t = &do_obj;

void   pp_mut_lock    (pp_mut* self) { if (pp_trait_of(self) != pp_mut_t) return;                mutex_lock   (&self->mut); }
bool_t pp_mut_lock_try(pp_mut* self) { if (pp_trait_of(self) != pp_mut_t) return false_t; return mutex_trylock(&self->mut); }
void   pp_mut_unlock  (pp_mut* self) { if (pp_trait_of(self) != pp_mut_t) return;                mutex_unlock (&self->mut); }

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_mut_unlock)  ;
EXPORT_SYMBOL(pp_mut_lock_try);
EXPORT_SYMBOL(pp_mut_lock)    ;
EXPORT_SYMBOL(pp_mut_t)       ;