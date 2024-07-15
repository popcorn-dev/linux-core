#ifndef THREAD_THD_H
#define THREAD_THD_H

#include "../../../popcorn/src/core.h"
#include "../../../popcorn/src/collections.h"

#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/err.h>

extern pp_obj_trait *pp_thd_t;
typedef struct       pp_thd  {
    pp_obj              head;
    u64_t               stat;
    pp_task            *task;
    void               *ret;
    struct task_struct *thd;
}   pp_thd;

pp_fut* pp_thd_fut(pp_thd*);

#endif
