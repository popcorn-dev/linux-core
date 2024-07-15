#include <core.h>

#include <linux/module.h>
#include <linux/bitops.h>

MODULE_LICENSE("GPL");

#if PRESET_ARCH_BIT >= 32
u32_t pp_btc32     (u32_t* self, u32_t bit) { return __test_and_change_bit(bit, (volatile unsigned long*) self); }
u32_t pp_btr32     (u32_t* self, u32_t bit) { return __test_and_clear_bit (bit, (volatile unsigned long*) self); }
u32_t pp_bts32     (u32_t* self, u32_t bit) { return __test_and_set_bit   (bit, (volatile unsigned long*) self); }
u32_t pp_bsr32     (u32_t  self)                { return fls(par); }
u32_t pp_bsf32     (u32_t  self)                { return ffs(par); }

u32_t pp_lock_btc32(u32_t* self, u32_t bit) { return test_and_change_bit(bit, (volatile unsigned long*) self); }
u32_t pp_lock_btr32(u32_t* self, u32_t bit) { return test_and_clear_bit (bit, (volatile unsigned long*) self); }
u32_t pp_lock_bts32(u32_t* self, u32_t bit) { return test_and_set_bit   (bit, (volatile unsigned long*) self); }

EXPORT_SYMBOL(pp_btc32);
EXPORT_SYMBOL(pp_btr32);
EXPORT_SYMBOL(pp_bts32);
EXPORT_SYMBOL(pp_bsr32);
EXPORT_SYMBOL(pp_bsf32);
EXPORT_SYMBOL(pp_lock_btc32);
EXPORT_SYMBOL(pp_lock_btr32);
EXPORT_SYMBOL(pp_lock_bts32);

#endif

#if PRESET_ARCH_BIT >= 64
u64_t pp_btc64     (u64_t* self, u64_t bit) { return __test_and_change_bit(bit, (volatile unsigned long*) self); }
u64_t pp_btr64     (u64_t* self, u64_t bit) { return __test_and_clear_bit (bit, (volatile unsigned long*) self); }
u64_t pp_bts64     (u64_t* self, u64_t bit) { return __test_and_set_bit   (bit, (volatile unsigned long*) self); }
u64_t pp_bsr64     (u64_t  self)            { return fls64(self); }
u64_t pp_bsf64     (u64_t  self)            { return __ffs64((long long int)self); }

u64_t pp_lock_btc64(u64_t* self, u64_t bit) { return test_and_change_bit(bit, (volatile unsigned long*) self); }
u64_t pp_lock_btr64(u64_t* self, u64_t bit) { return test_and_clear_bit (bit, (volatile unsigned long*) self); }
u64_t pp_lock_bts64(u64_t* self, u64_t bit) { return test_and_set_bit   (bit, (volatile unsigned long*) self); }

EXPORT_SYMBOL(pp_btc64);
EXPORT_SYMBOL(pp_btr64);
EXPORT_SYMBOL(pp_bts64);
EXPORT_SYMBOL(pp_bsr64);
EXPORT_SYMBOL(pp_bsf64);
EXPORT_SYMBOL(pp_lock_btc64);
EXPORT_SYMBOL(pp_lock_btr64);
EXPORT_SYMBOL(pp_lock_bts64);

#endif