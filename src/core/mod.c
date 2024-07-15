#include <linux/module.h>
#include <core.h>

extern pp_obj_trait *pp_t;
extern struct pp     pp;

static int
    pp_init(void)                                             {
        if (!pp_make_at((pp_obj*) &pp, pp) from (0)) return -1;
        pp_info("[Popcorn] POPCORN subsystem Initialized");
        return 0;
}

static void
    pp_exit(void)                                        {
        pp_info("[Popcorn] POPCORN subsystem Terminated");
        pp_del (&pp);
}

module_init(pp_init);
module_exit(pp_exit);

MODULE_LICENSE("GPL");