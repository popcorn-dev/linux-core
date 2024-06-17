#ifndef __UA_H__
#define __UA_H__

#include <core.h>

extern po_obj_trait *po_ua_t;
typedef struct       po_ua { u8_t ua[128]; } po_ua;

u64_t  po_ua_copy_from(po_ua*, void*, u64_t);
u64_t  po_ua_copy_to  (po_ua*, void*, u64_t);
u64_t  po_ua_len      (po_ua*)              ;

#endif
