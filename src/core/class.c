#include "class.h"
#include "dev.h"

static int
    do_dev_add
        (struct device *arg)                                           {
            pp_class *self = container_of(arg->class, pp_class, class);
            if (pp_trait_of(self) != pp_class_t) return -1;
            pp_dev *dev = pp_make (pp_dev) from (0);

            if (pp_trait_of(dev) != pp_dev_t) return -1;
            dev->dev = get_device(arg);
            if (!self->ops->add(self->obj, dev)) {
                pp_del(dev);
                return -1;
            }

            pp_ref(self);
            return 0;
}

static void
    do_dev_del
        (struct device *arg)                                          {
            pp_class *self = container_of(arg->class, pp_class, class);
            if (pp_trait_of(self) != pp_class_t) return;
            pp_dev *dev = pp_make (pp_dev) from (0);

            if (pp_trait_of(dev) != pp_dev_t)   return;
            dev->dev = get_device(arg);
            if (!self->ops->del(self->obj, dev)) {
                pp_del(dev);
                return;
            }

            pp_del(self);
}

static struct class_interface do_ops = {
    .add_dev    = do_dev_add,
    .remove_dev = do_dev_del
};

static bool_t
    do_new
        (pp_class* self, u32_t count, va_list arg)                               {
            const char   *name = null_t; if (count > 0) name = va_arg(arg, any_t);
            pp_class_ops *ops  = null_t; if (count > 1) ops  = va_arg(arg, any_t);
            pp_obj       *obj  = null_t; if (count > 2) obj  = va_arg(arg, any_t);
            if (!name) return false_t;
            self->class.name = name;

            if (class_register(&self->class)) return false_t;
            if (count < 3)                                  {
                self->obj = pp_ref(obj);
                self->ops = null_t     ;
                return true_t;
            }

            self->type.class = &self->class;
            self->type       = do_ops;
            if (!ops)      goto err;
            if (!ops->add) goto err;
            if (!ops->del) goto err;

            if (class_interface_register(&self->type)) goto err;
            self->obj  = pp_ref(obj);
            self->ops  = ops;
            return true_t;
    err:    class_unregister(&self->class);
            return false_t;
}

static bool_t
    do_clone
        (pp_class* self, pp_class* clone) {
            return false_t;
}

static void
    do_del
        (pp_class* self)                            {
            class_interface_unregister(&self->type) ;
            class_unregister          (&self->class);
            pp_del(self->obj);
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new          ,
        do_clone        ,
        null_t          ,
        do_del          ,
        sizeof(pp_class),
        null_t
);

pp_obj_trait *pp_class_t = &do_obj;

struct pp_dev*
    pp_class_find
        (pp_class* self, const char* name, u64_t len)         {
            if (pp_trait_of(self) != pp_class_t) return null_t;
            if (!name)                           return null_t;
            if (!len)                            return null_t;
            pp_dev *ret = pp_make (pp_dev) from (0);

            struct device *dev = class_find_device_by_name(&self->class, name);
            if (pp_trait_of(ret) != pp_dev_t) goto err;
            if (IS_ERR(dev))                  goto err;
            ret->dev = get_device(dev);

            if (!ret->dev) goto err;
            return ret;
    err:    pp_del  (ret);
            return null_t;
}

#include <linux/module.h>
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_class_find);
EXPORT_SYMBOL(pp_class_t);