#include <core.h>

#include <linux/module.h>
#include <linux/printk.h>

void pp_crit(const char* par) { pr_crit("%s\n", par); }
void pp_info(const char* par) { pr_info("%s\n", par); }
void pp_err (const char* par) { pr_err ("%s\n", par); }

EXPORT_SYMBOL(pp_crit);
EXPORT_SYMBOL(pp_info);
EXPORT_SYMBOL(pp_err);