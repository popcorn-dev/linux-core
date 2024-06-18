#include "dev.h"
#include "class.h"

#include <linux/fs.h>

po_obj_trait po_dev_trait = po_make_trait (
    po_dev_new    ,
    po_dev_clone  ,
    null_t        ,
    po_dev_del    ,
    sizeof(po_dev),
    null_t
);

po_obj_trait *po_dev_t = &po_dev_trait;

bool_t
    po_dev_new
        (po_dev* self, u32_t count, va_list arg)                                 {
            const char *name  = null_t; if (count > 0) name  = va_arg(arg, any_t);
            dev_t       num   = 0;      if (count > 1) num   = va_arg(arg, dev_t);
            any_t       sub   = 0;      if (count > 2) sub   = va_arg(arg, any_t);
            po_class   *class = null_t; if (count > 3) class = va_arg(arg, any_t);
            po_dev     *sup   = null_t; if (count > 4) sup   = va_arg(arg, any_t);
            if (po_trait_of(class) != po_class_t) return false_t;
            if (!name)                            return false_t;
            struct device *parent;

            if (po_trait_of(sup) == po_dev_t) parent = sup->dev;
            self->dev = device_create                          (
                &class->class,
                parent       ,
                num          ,
                sub          ,
                name
            );

            if (IS_ERR(self->dev))    return false_t;
            self->class = (po_class*) po_ref (class);
            self->sup   = (po_dev*)   po_ref (sup);
            self->num   = num;
            return true_t;
}

bool_t
    po_dev_clone
        (po_dev* self, po_dev* clone) {
            return false_t;
}

void
    po_dev_del
        (po_dev* self)                                    {
            device_destroy(&self->class->class, self->num);
            po_del (self->class);
            po_del (self->sup);
}

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_dev_t);