#ifndef PO_LINUX_CLASS_H
#define PO_LINUX_CLASS_H

#include <core.h>
#include <collections.h>

#include <linux/device.h>

struct po_dev;

typedef struct po_class_ops               {
    bool_t (*add)(po_obj*, struct po_dev*);
    bool_t (*del)(po_obj*, struct po_dev*);
}   po_class_ops;

extern po_obj_trait *po_class_t ;
typedef struct       po_class   {
    po_obj                 head ;
    struct class           class;
    struct class_interface type;
    po_class_ops          *ops;
    po_obj                *obj;
}   po_class;

bool_t         po_class_new      (po_class*, u32_t, va_list);
bool_t         po_class_clone    (po_class*, po_class*)     ;
void           po_class_del      (po_class*)                ;

struct po_dev* po_class_find_cstr(po_class*, const char*, u64_t);
struct po_dev* po_class_find     (po_class*, po_str*)           ;

#endif