#ifndef CORE_WORK_H
#define CORE_WORK_H

#include <core.h>

extern pp_obj_trait *pp_wqe_t;
typedef struct       pp_wqe { u8_t wqe[128]; } pp_wqe;

pp_fut* pp_wqe_fut  (pp_wqe*);

#endif