#include "ua.h"

static bool_t
    do_new
        (pp_ua* self, u32_t count, va_list arg)                        {
            u8_t* ua  = null_t; if (count > 0) ua  = va_arg(arg, any_t);
            u64_t len = 0ull  ; if (count > 1) len = va_arg(arg, u64_t);

            if (!ua) return false_t;
            self->len = len;
            self->ua  = ua;
            return true_t;
}

static bool_t
    do_clone
        (pp_ua* self, pp_ua* clone) {
            self->len = clone->len;
            self->ua  = clone->ua ;
            return true_t;
}

static void
    do_del
        (pp_ua* self) {
            return;
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new       ,
        do_clone     ,
        null_t       ,
        do_del       ,
        sizeof(pp_ua),
        null_t
);

pp_obj_trait *pp_ua_t = &do_obj;

u64_t
    pp_ua_copy_from
        (pp_ua* self, void* from, u64_t len)             {
            if (pp_trait_of(self) != pp_ua_t) return 0ull;
            if (!from)                        return 0ull;
            if (!len)                         return 0ull;
            u64_t ret = copy_to_user                     (
                self->ua,
                from    ,
                len
            );

            len -= ret;
            return len;
}

u64_t
    pp_ua_copy_to
        (pp_ua* self, void* to, u64_t len)               {
            if (pp_trait_of(self) != pp_ua_t) return 0ull;
            if (!len)                         return 0ull;
            if (!to)                          return 0ull;
            u64_t ret = copy_from_user                   (
                to      ,
                self->ua,
                len
            );

            len -= ret;
            return len;
}

u64_t
    pp_ua_len
        (pp_ua* self)                                       {
            if (pp_trait_of(self) != pp_ua_t) return false_t;
            return self->len;
}

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_ua_t);
EXPORT_SYMBOL(pp_ua_copy_from);
EXPORT_SYMBOL(pp_ua_copy_to);
EXPORT_SYMBOL(pp_ua_len);