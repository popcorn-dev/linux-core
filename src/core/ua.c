#include "ua.h"

static i8_t
    do_as_i8
        (pp_ua* self)                                 {
            if (pp_trait_of(self) != pp_ua_t) return 0;
            i8_t ret = 0;

            copy_from_user(&ret, self->ua + self->off, 1);
            self->off += 1;
            return ret;
}

static u8_t
    do_as_u8
        (pp_ua* self)                                 {
            if (pp_trait_of(self) != pp_ua_t) return 0;
            u8_t ret = 0;

            copy_from_user(&ret, self->ua + self->off, 1);
            self->off += 1;
            return ret;
}

static i16_t
    do_as_i16
        (pp_ua* self)                                 {
            if (pp_trait_of(self) != pp_ua_t) return 0;
            i16_t ret = 0;

            copy_from_user(&ret, self->ua + self->off, 2);
            self->off += 2;
            return ret;
}

static u16_t
    do_as_u16
        (pp_ua* self)                                 {
            if (pp_trait_of(self) != pp_ua_t) return 0;
            u16_t ret = 0;

            copy_from_user(&ret, self->ua + self->off, 2);
            self->off += 2;
            return ret;
}

static i32_t
    do_as_i32
        (pp_ua* self)                                 {
            if (pp_trait_of(self) != pp_ua_t) return 0;
            i32_t ret = 0;

            copy_from_user(&ret, self->ua + self->off, 4);
            self->off += 4;
            return ret;
}

static u32_t
    do_as_u32
        (pp_ua* self)                                 {
            if (pp_trait_of(self) != pp_ua_t) return 0;
            u32_t ret = 0;

            copy_from_user(&ret, self->ua + self->off, 4);
            self->off += 4;
            return ret;
}

static i64_t
    do_as_i64
        (pp_ua* self)                                 {
            if (pp_trait_of(self) != pp_ua_t) return 0;
            i64_t ret = 0;

            copy_from_user(&ret, self->ua + self->off, 8);
            self->off += 8;
            return ret;
}

static u64_t
    do_as_u64
        (pp_ua* self)                                 {
            if (pp_trait_of(self) != pp_ua_t) return 0;
            u64_t ret = 0;

            copy_from_user(&ret, self->ua + self->off, 8);
            self->off += 8;
            return ret;
}

static any_t
    do_as_any
        (pp_ua* self)                                 {
            if (pp_trait_of(self) != pp_ua_t) return 0;
            any_t ret = 0;

            copy_from_user(&ret, self->ua + self->off, sizeof(ret));
            self->off += sizeof(ret);
            return ret;
}

static pp_cast
    do_cast = pp_make_cast (
        null_t   ,
        do_as_i8 ,
        do_as_u8 ,
        do_as_i16,
        do_as_u16,
        do_as_i32,
        do_as_u32,
        do_as_i64,
        do_as_u64,
        do_as_any
);

static pp_obj_ops
    do_ops = { .cast = &do_cast };

static bool_t
    do_new
        (pp_ua* self, u32_t count, va_list arg)                        {
            u8_t* ua  = null_t; if (count > 0) ua  = va_arg(arg, any_t);
            u64_t len = 0ull  ; if (count > 1) len = va_arg(arg, u64_t);

            if (!ua) return false_t;
            self->off = 0ull;
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
        &do_ops
);

pp_obj_trait *pp_ua_t = &do_obj;

u64_t
    pp_ua_copy_from
        (pp_ua* self, void* from, u64_t len)             {
            if (pp_trait_of(self) != pp_ua_t) return 0ull;
            if (!from)                        return 0ull;
            if (!len)                         return 0ull;

            if (len > self->len) len = self->len;
            u64_t ret = copy_to_user            (
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

            if (len > self->len) len = self->len;
            u64_t ret = copy_from_user          (
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