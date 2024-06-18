#ifndef PO_LINUX_UA_H
#define PO_LINUX_UA_H

#include <core.h>
#include <linux/uaccess.h>

extern po_obj_trait *po_ua_t;
typedef struct       po_ua  {
    po_obj       head;
    u64_t        len;
    __user u8_t* ua;
}   po_ua;

bool_t po_ua_new      (po_ua*, u32_t, va_list);
bool_t po_ua_clone    (po_ua*, po_ua*)        ;
void   po_ua_del      (po_ua*)                ;

u64_t  po_ua_copy_from(po_ua*, void*, u64_t);
u64_t  po_ua_copy_to  (po_ua*, void*, u64_t);
u64_t  po_ua_len      (po_ua*)              ;

#endif
