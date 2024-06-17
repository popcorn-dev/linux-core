#include "core.h"

static bool_t
    do_new
        (struct core* self, u32_t count, va_list arg) {
            po_str* name = po_make (po_str) from (0);

            if (po_trait_of(name) != po_str_t) return false_t;
            po_str_push_back_cstr(name, "popcorn", 7);

            if (!po_make_at (&self->class, po_class) from ())
}