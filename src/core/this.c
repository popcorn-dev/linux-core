#include <core.h>

#include <linux/module.h>
#include <linux/ktime.h>
#include <linux/sched.h>

void
    pp_yield
        (void)        {
            schedule();
}

any_t
    pp_await_until
        (pp_fut* fut, u32_t until)                         {
            if (pp_trait_of(fut) != pp_fut_t) return null_t;
            until += jiffies;

            for ( ; time_before(jiffies, until) ; pp_yield())
                if (pp_fut_poll(fut) != pp_fut_pend) {
                    any_t  ret = pp_fut_ret(fut);
                    pp_del(fut);
                    return ret;
                }

            return null_t;
}

any_t
    pp_await
        (pp_fut* fut)                                      {
            if (pp_trait_of(fut) != pp_fut_t) return null_t;

            for ( ; pp_fut_poll(fut) == pp_fut_pend ; pp_yield());
            any_t  ret = pp_fut_ret(fut);
            pp_del(fut);
            return ret;
}

MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_yield)      ;
EXPORT_SYMBOL(pp_await_until);
EXPORT_SYMBOL(pp_await)      ;