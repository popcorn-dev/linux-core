#ifndef __PO_WAIT_H__
#define __PO_WAIT_H__

#include "core.h"

extern po_obj_trait *po_wait_t;
typedef struct       po_wait { u8_t wait[128]; } po_wait;

bool_t po_wait_on_timeout(po_wait*, bool_t, u64_t);
void   po_wait_on        (po_wait*, bool_t);
bool_t po_wake           (po_wait*, bool_t);

#endif
