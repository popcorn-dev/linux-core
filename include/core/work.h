#ifndef __PO_WORK_H__
#define __PO_WORK_H__

#include "core.h"

extern po_obj_trait *po_wqe_t;
typedef struct       po_wqe { u8_t wqe[128]; } po_wqe;

po_fut* po_wqe_fut  (po_wqe*);

#endif