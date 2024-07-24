#ifndef CORE_UA_H
#define CORE_UA_H

#include <core.h>
#include <linux/uaccess.h>

extern pp_obj_trait *pp_ua_t;
typedef struct       pp_ua  {
    pp_obj       head;
    u64_t        len;
    u64_t        off;
    __user u8_t* ua;
}   pp_ua;

u64_t  pp_ua_copy_from(pp_ua*, void*, u64_t);
u64_t  pp_ua_copy_to  (pp_ua*, void*, u64_t);
u64_t  pp_ua_len      (pp_ua*)              ;

#endif
