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
        (po_dev* self, u32_t count, va_list arg) {
            self->dev = null_t;
            return true_t;
}

bool_t
    po_dev_clone
        (po_dev* self, po_dev* clone)         {
            self->dev = get_device(clone->dev);

            if (IS_ERR(self->dev)) return false_t;
            return true_t;
}

void
    po_dev_del
        (po_dev* self)           {
            put_device(self->dev);
}

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_dev_t);