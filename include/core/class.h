#ifndef CORE_CLASS_H
#define CORE_CLASS_H

#include "core.h"
#include "collections.h"

struct pp_dev;
typedef struct pp_class_ops               {
    bool_t (*add)(pp_obj*, struct pp_dev*);
    bool_t (*del)(pp_obj*, struct pp_dev*);
}   pp_class_ops;

extern pp_obj_trait *pp_class_t;
typedef struct       pp_class { u8_t class[512]; } pp_class;

struct pp_dev* pp_class_find(pp_class*, const char*, u64_t);

#endif
