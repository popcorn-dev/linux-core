#ifndef CORE_WAIT_H
#define CORE_WAIT_H

#include <core.h>

#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/wait.h>

extern pp_obj_trait *pp_wait_t;
typedef struct       pp_wait  {
    pp_obj            head;
    wait_queue_head_t wait;
}   pp_wait;

bool_t pp_wait_on_timeout(pp_wait*, bool_t, u64_t);
void   pp_wait_on        (pp_wait*, bool_t);
bool_t pp_wake           (pp_wait*, bool_t);

#endif