#ifndef THREAD_MUT_H
#define THREAD_MUT_H

#include "../../../popcorn/src/core.h"
#include <linux/mutex.h>

extern pp_obj_trait *pp_mut_t;
typedef struct       pp_mut  {
    pp_obj       head;
    struct mutex mut ;
}   pp_mut;

bool_t pp_mut_lock_try(pp_mut*);
void   pp_mut_lock    (pp_mut*);
void   pp_mut_unlock  (pp_mut*);

#endif