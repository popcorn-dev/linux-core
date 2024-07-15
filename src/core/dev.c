#include "dev.h"
#include "class.h"

#include <linux/fs.h>

static bool_t
    do_new
        (pp_dev* self, u32_t count, va_list arg)                                 {
            const char *name  = null_t; if (count > 0) name  = va_arg(arg, any_t);
            dev_t       num   = 0;      if (count > 1) num   = va_arg(arg, dev_t);
            any_t       sub   = 0;      if (count > 2) sub   = va_arg(arg, any_t);
            pp_class   *class = null_t; if (count > 3) class = va_arg(arg, any_t);
            pp_dev     *sup   = null_t; if (count > 4) sup   = va_arg(arg, any_t);
            if (pp_trait_of(class) != pp_class_t) return false_t;
            if (!name)                            return false_t;
            struct device *parent;

            if (pp_trait_of(sup) == pp_dev_t) parent = sup->dev;
            self->dev = device_create                          (
                &class->class,
                parent       ,
                num          ,
                sub          ,
                name
            );

            if (IS_ERR(self->dev))    return false_t;
            self->class = (pp_class*) pp_ref (class);
            self->sup   = (pp_dev*)   pp_ref (sup);
            self->num   = num;
            return true_t;
}

static bool_t
    do_clone
        (pp_dev* self, pp_dev* clone) {
            return false_t;
}

static void
    do_del
        (pp_dev* self)                                    {
            device_destroy(&self->class->class, self->num);
            pp_del (self->class);
            pp_del (self->sup);
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_dev),
        null_t
);

pp_obj_trait *pp_dev_t = &do_obj;

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_dev_t);