#include <core.h>

#include <linux/module.h>
#include <linux/atomic.h>

MODULE_LICENSE("GPL");

#if PRESET_ARCH_BIT >= 32
u32_t pp_lock_add32(u32_t* self, u32_t add) { return atomic_add_return(add, (atomic_t*) self); }
u32_t pp_lock_sub32(u32_t* self, u32_t sub) { return atomic_sub_return(sub, (atomic_t*) self); }
u32_t pp_lock_inc32(u32_t* self)            { return atomic_inc_return((atomic_t*) self); }
u32_t pp_lock_dec32(u32_t* self)            { return atomic_dec_return((atomic_t*) self); }

u32_t pp_cas32      (u32_t* self, u32_t old, u32_t new) { return atomic_cmpxchg((atomic_t*) self, old, new); }
u32_t pp_xchg32     (u32_t* self, u32_t new)            { return atomic_xchg   ((atomic_t*) self, new); }

u32_t pp_lock_cas32 (u32_t* self, u32_t old, u32_t new) { return atomic_cmpxchg((atomic_t*) self, old, new); }
u32_t pp_lock_xchg32(u32_t* self, u32_t new)            { return atomic_xchg   ((atomic_t*) self, new); }

EXPORT_SYMBOL(pp_lock_add32);
EXPORT_SYMBOL(pp_lock_sub32);
EXPORT_SYMBOL(pp_lock_inc32);
EXPORT_SYMBOL(pp_lock_dec32);

EXPORT_SYMBOL(pp_cas32);
EXPORT_SYMBOL(pp_xchg32);
EXPORT_SYMBOL(pp_lock_cas32);
EXPORT_SYMBOL(pp_lock_xchg32);

#endif

#if PRESET_ARCH_BIT >= 64
u64_t pp_lock_add64(u64_t* self, u64_t add) { return atomic64_add_return(add, (atomic64_t*) self); }
u64_t pp_lock_sub64(u64_t* self, u64_t sub) { return atomic64_sub_return(sub, (atomic64_t*) self); }
u64_t pp_lock_inc64(u64_t* self)            { return atomic64_inc_return((atomic64_t*) self); }
u64_t pp_lock_dec64(u64_t* self)            { return atomic64_dec_return((atomic64_t*) self); }

u64_t pp_cas64      (u64_t* self, u64_t old, u64_t new) { return atomic64_cmpxchg((atomic64_t*) self, old, new); }
u64_t pp_xchg64     (u64_t* self, u64_t new)            { return atomic64_xchg   ((atomic64_t*) self, new); }

u64_t pp_lock_cas64 (u64_t* self, u64_t old, u64_t new) { return atomic64_cmpxchg((atomic64_t*) self, old, new); }
u64_t pp_lock_xchg64(u64_t* self, u64_t new)            { return atomic64_xchg   ((atomic64_t*) self, new); }

EXPORT_SYMBOL(pp_lock_add64);
EXPORT_SYMBOL(pp_lock_sub64);
EXPORT_SYMBOL(pp_lock_inc64);
EXPORT_SYMBOL(pp_lock_dec64);

EXPORT_SYMBOL(pp_cas64);
EXPORT_SYMBOL(pp_xchg64);
EXPORT_SYMBOL(pp_lock_cas64);
EXPORT_SYMBOL(pp_lock_xchg64);

#endif


#if PRESET_ARCH_BIT >= 32
u32_t
    pp_lock_cas_inc32
        (u32_t* par)         {
            u32_t ret_inc = 0;
            u32_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_inc   = ret + 1;
            } while (pp_lock_cas32(par, ret, ret_inc) != ret);

            return ret_inc;
}

u32_t
    pp_lock_cas_dec32
        (u32_t* par)         {
            u32_t ret_dec = 0;
            u32_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_dec   = ret - 1;
            } while (pp_lock_cas32(par, ret, ret_dec) != ret);

            return ret_dec;
}

u32_t
    pp_cas_inc32
        (u32_t* par)         {
            u32_t ret_inc = 0;
            u32_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_inc   = ret + 1;
            } while (pp_cas32(par, ret, ret_inc) != ret);

            return ret_inc;
}

u32_t
    pp_cas_dec32
        (u32_t* par)         {
            u32_t ret_dec = 0;
            u32_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_dec   = ret - 1;
            } while (pp_cas32(par, ret, ret_dec) != ret);

            return ret_dec;
}

#endif

#if PRESET_ARCH_BIT >= 64
u64_t
    pp_lock_cas_inc64
        (u64_t* par)         {
            u64_t ret_inc = 0;
            u64_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_inc   = ret + 1;
            } while (pp_lock_cas64(par, ret, ret_inc) != ret);

            return ret_inc;
}

u64_t
    pp_lock_cas_dec64
        (u64_t* par)         {
            u64_t ret_dec = 0;
            u64_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_dec   = ret - 1;
            } while (pp_lock_cas64(par, ret, ret_dec) != ret);

            return ret_dec;
}

u64_t
    pp_cas_inc64
        (u64_t* par)         {
            u64_t ret_inc = 0;
            u64_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_inc   = ret + 1;
            } while (pp_cas64(par, ret, ret_inc) != ret);

            return ret_inc;
}

u64_t
    pp_cas_dec64
        (u64_t* par)         {
            u64_t ret_dec = 0;
            u64_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_dec   = ret - 1;
            } while (pp_cas64(par, ret, ret_dec) != ret);

            return ret_dec;
}

EXPORT_SYMBOL(pp_lock_cas_inc32);
EXPORT_SYMBOL(pp_lock_cas_inc64);
EXPORT_SYMBOL(pp_cas_inc32);
EXPORT_SYMBOL(pp_cas_inc64);

EXPORT_SYMBOL(pp_lock_cas_dec32);
EXPORT_SYMBOL(pp_lock_cas_dec64);
EXPORT_SYMBOL(pp_cas_dec32);
EXPORT_SYMBOL(pp_cas_dec64);

#endif