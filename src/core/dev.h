#ifndef CORE_DEV_H
#define CORE_DEV_H

#include <core.h>
#include <linux/device.h>

struct pp_class;
extern pp_obj_trait *pp_dev_t;
typedef struct       pp_dev  {
    pp_obj           head;
    struct pp_class *class;
    struct device   *dev;
    struct pp_dev   *sup;
    dev_t            num;
}   pp_dev;

#endif
