#include "class.h"
#include "dev.h"

static int
    do_add
        (struct device *arg)                                           {
            po_class *self = container_of(arg->class, po_class, class);
            if (po_trait_of(self) != po_class_t) return -1;
            po_dev *dev = po_make (po_dev) from (0);

            if (po_trait_of(dev) != po_dev_t) return -1;
            dev->dev = get_device(arg);
            if (!self->ops->add(self->obj, dev)) {
                po_del(dev);
                return -1;
            }

            po_ref(self);
            return 0;
}

static void
    do_del
        (struct device *arg)                                          {
            po_class *self = container_of(arg->class, po_class, class);
            if (po_trait_of(self) != po_class_t) return;
            po_dev *dev = po_make (po_dev) from (0);

            if (po_trait_of(dev) != po_dev_t)   return;
            dev->dev = get_device(arg);
            if (!self->ops->del(self->obj, dev)) {
                po_del(dev);
                return;
            }

            po_del(self);
}

static struct class_interface do_ops = {
    .add_dev    = do_add,
    .remove_dev = do_del
};

po_obj_trait po_class_trait = po_make_trait (
    po_class_new    ,
    po_class_clone  ,
    null_t          ,
    po_class_del    ,
    sizeof(po_class),
    null_t
);

po_obj_trait *po_class_t = &po_class_trait;

bool_t
    po_class_new
        (po_class* self, u32_t count, va_list arg)                               {
            po_str       *name = null_t; if (count > 0) name = va_arg(arg, any_t);
            po_class_ops *ops  = null_t; if (count > 1) ops  = va_arg(arg, any_t);
            po_obj       *obj  = null_t; if (count > 2) obj  = va_arg(arg, any_t);
            if (po_trait_of (name) != po_str_t) return false_t;
            self->class.name = po_str_ptr(name);

            if (class_register(&self->class)) return false_t;
            if (count < 3)                                  {
                self->obj = po_ref(obj);
                self->ops = null_t     ;
                return true_t;
            }

            self->type.class = &self->class;
            self->type       = do_ops;
            if (!ops)      goto err;
            if (!ops->add) goto err;
            if (!ops->del) goto err;

            if (class_interface_register(&self->type)) goto err;
            self->name = po_ref(name);
            self->obj  = po_ref(obj);
            self->ops  = ops;
            return true_t;
    err:    class_unregister(&self->class);
            return false_t;
}

bool_t
    po_class_clone
        (po_class* self, po_class* clone) {
            return false_t;
}

void
    po_class_del
        (po_class* self)                            {
            class_interface_unregister(&self->type) ;
            class_unregister          (&self->class);
            po_del(self->name);
            po_del(self->obj);
}

struct po_dev*
    po_class_find_cstr
        (po_class* self, const char* name, u64_t len)         {
            if (po_trait_of(self) != po_class_t) return null_t;
            if (!name)                           return null_t;
            if (!len)                            return null_t;
            po_dev *ret = po_make (po_dev) from (0);

            struct device *dev = class_find_device_by_name(&self->class, name);
            if (po_trait_of(ret) != po_dev_t) goto err;
            if (IS_ERR(dev))                  goto err;
            ret->dev = get_device(dev);

            if (!ret->dev) goto err;
            return ret;
    err:    po_del  (ret);
            return null_t;
}

struct po_dev*
    po_class_find
        (po_class* self, po_str* str)                         {
            if (po_trait_of(self) != po_class_t) return null_t;
            if (po_trait_of(str)  != po_str_t)   return null_t;
            const char* name = po_str_ptr(str);
            u64_t       len  = po_str_len(str);

            return po_class_find_cstr (
                self,
                name,
                len
            );
}

#include <linux/module.h>
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_class_find_cstr);
EXPORT_SYMBOL(po_class_find);
EXPORT_SYMBOL(po_class_t);