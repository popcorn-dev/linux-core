#ifndef __WAIT_H__
#define __WAIT_H__

#include "core.h"

#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/wait.h>

extern po_obj_trait *po_wait_t;
typedef struct       po_wait  {
    po_obj            head;
    wait_queue_head_t wait;
}   po_wait;

bool_t po_wait_new       (po_wait*, u32_t, va_list);
bool_t po_wait_clone     (po_wait*, po_wait*)      ;
void   po_wait_del       (po_wait*)                ;

bool_t po_wait_on_timeout(po_wait*, bool_t, u64_t);
void   po_wait_on        (po_wait*, bool_t);
bool_t po_wake           (po_wait*, bool_t);

#endif