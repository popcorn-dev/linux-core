#ifndef PO_LINUX_CORE_H
#define PO_LINUX_CORE_H

#include <core.h>
#include <linux/workqueue.h>

extern po_obj_trait *po_wqe_t;
typedef struct       po_wqe  {
    po_obj             head;
    struct work_struct work;
    po_task           *task;
    u64_t              stat;
    any_t              ret;
}   po_wqe;

bool_t  po_wqe_new  (po_wqe*, u32_t, va_list);
bool_t  po_wqe_clone(po_wqe*, po_wqe*)       ;
void    po_wqe_del  (po_wqe*)                ;
po_fut* po_wqe_fut  (po_wqe*)                ;

#endif
