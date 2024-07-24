#ifndef CORE_UA_H
#define CORE_UA_H

#include <core.h>

extern pp_obj_trait *pp_ua_t;
typedef struct       pp_ua { u8_t ua[128]; } pp_ua;

u64_t  pp_ua_copy_from(pp_ua*, void*, u64_t);
u64_t  pp_ua_copy_to  (pp_ua*, void*, u64_t);
u64_t  pp_ua_len      (pp_ua*)              ;

#endif
