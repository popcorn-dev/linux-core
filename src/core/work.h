#ifndef CORE_WORK_H
#define CORE_WORK_H

#include <core.h>
#include <linux/workqueue.h>

extern pp_obj_trait *pp_wqe_t;
typedef struct       pp_wqe  {
    pp_obj             head;
    struct work_struct work;
    pp_task           *task;
    u64_t              stat;
    any_t              ret;
}   pp_wqe;

pp_fut* pp_wqe_fut(pp_wqe*);

#endif
