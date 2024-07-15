#ifndef LINUX_THREAD_MTX_H
#define LINUX_THREAD_MTX_H

#include <core.h>

extern pp_obj_trait   *pp_mut_t;
typedef struct         pp_mut { u8_t pp_mtx[64]; } pp_mut;

bool_t pp_mut_lock_try(pp_mut*);
void   pp_mut_lock    (pp_mut*);
void   pp_mut_unlock  (pp_mut*);

#endif
