#include <linux/string.h>
#include <linux/module.h>

#include <core.h>

void
    pp_mem_set
        (void* des, u8_t set, u64_t len) {
            if (!len) return;
            if (!des) return;

            memset(des, set, len);
}

void
    pp_mem_copy
        (void* des, void* src, u64_t len) {
            if (!des) return;
            if (!src) return;
            if (!len) return;

            memcpy(des, src, len);
}

void
    pp_mem_move
        (void* des, void* src, u64_t len) {
            if (!des) return;
            if (!src) return;
            if (!len) return;

            memmove(des, src, len);
}

u64_t
    pp_mem_find
        (void* des, void* src, u64_t dlen, u64_t slen) {
            if (dlen > slen) return -1;
            return (u64_t) strstr     (
                des,
                src
            );
}

pp_ord_t
    pp_mem_ord
        (void* des, void* ord, u64_t len) {
            if (!des) return pp_ord_err;
            if (!ord) return pp_ord_err;
            if (!len) return pp_ord_err;

            int ret = memcmp (des, ord, len);
            if (ret < 0) return pp_ord_lt;
            if (ret > 0) return pp_ord_gt;
            return pp_ord_eq;
}

bool_t pp_mem_eq(void* des, void* ord, u64_t len) { return pp_mem_ord(des, ord,len) == pp_ord_eq; }
bool_t pp_mem_gt(void* des, void* ord, u64_t len) { return pp_mem_ord(des, ord,len) == pp_ord_gt; }
bool_t pp_mem_lt(void* des, void* ord, u64_t len) { return pp_mem_ord(des, ord,len) == pp_ord_lt; }

static pp_mem *mem;

pp_mem*
    pp_get_mem()  {
        return mem;
}

pp_mem*
    pp_set_mem
        (pp_mem* set)                                      {
            if (pp_trait_of(set) != pp_mem_t) return null_t;
            pp_mem* ret = mem;
            mem   = set;
            return  ret;
}

EXPORT_SYMBOL(pp_mem_eq);
EXPORT_SYMBOL(pp_mem_gt);
EXPORT_SYMBOL(pp_mem_lt);

EXPORT_SYMBOL(pp_mem_set);
EXPORT_SYMBOL(pp_mem_copy);
EXPORT_SYMBOL(pp_mem_move);
EXPORT_SYMBOL(pp_mem_find);

EXPORT_SYMBOL(pp_get_mem);
EXPORT_SYMBOL(pp_set_mem);