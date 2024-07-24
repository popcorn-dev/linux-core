#ifndef LINUX_THREAD_THD_H
#define LINUX_THREAD_THD_H

#include <core.h>

extern pp_obj_trait *pp_thd_t;
typedef struct       pp_thd { u8_t thd[64]; } pp_thd;

pp_fut* pp_thd_fut(pp_thd*);

#endif