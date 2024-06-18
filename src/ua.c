#include "ua.h"

po_obj_trait po_ua_trait = po_make_trait (
    po_ua_new    ,
    po_ua_clone  ,
    null_t       ,
    po_ua_del    ,
    sizeof(po_ua),
    null_t
);

po_obj_trait *po_ua_t = &po_ua_trait;

bool_t
    po_ua_new
        (po_ua* self, u32_t count, va_list arg)                        {
            u64_t len = 0ull  ; if (count > 1) len = va_arg(arg, u64_t);
            u8_t* ua  = null_t; if (count > 0) ua  = va_arg(arg, any_t);

            if (!ua) return false_t;
            self->len = len;
            self->ua  = ua;
            return true_t;
}

bool_t
    po_ua_clone
        (po_ua* self, po_ua* clone) {
            self->len = clone->len;
            self->ua  = clone->ua ;
            return true_t;
}

void
    po_ua_del
        (po_ua* self) {
            return;
}

u64_t
    po_ua_copy_from
        (po_ua* self, void* from, u64_t len)          {
            if (po_trait_of(self) != po_ua_t) return 0;
            if (!from)                        return 0;
            if (!len)                         return 0;
            u64_t ret = copy_to_user                  (
                self->ua,
                from    ,
                len
            );

            len -= ret;
            return len;
}

u64_t
    po_ua_copy_to
        (po_ua* self, void* to, u64_t len)            {
            if (po_trait_of(self) != po_ua_t) return 0;
            if (!len)                         return 0;
            if (!to)                          return 0;
            u64_t ret = copy_from_user                (
                to      ,
                self->ua,
                len
            );

            len -= ret;
            return len;
}

u64_t
    po_ua_len
        (po_ua* self)                                       {
            if (po_trait_of(self) != po_ua_t) return false_t;
            return self->len;
}