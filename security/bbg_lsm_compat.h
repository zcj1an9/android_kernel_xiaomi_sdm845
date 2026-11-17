/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _BBG_LSM_COMPAT_H
#define _BBG_LSM_COMPAT_H

#include <linux/lsm_hooks.h>

/*
 * This 4.9 tree backports the three-argument LSM registration API. BBG's
 * version-based compatibility wrapper still selects the two-argument form.
 * Included only while compiling baseband_guard.o; preserve named callers.
 */
#define __bbg_add_hooks_2(hooks, count) \
	security_add_hooks(hooks, count, "baseband_guard")
#define __bbg_add_hooks_3(hooks, count, name) \
	security_add_hooks(hooks, count, name)
#define __bbg_add_hooks_select(_1, _2, _3, fn, ...) fn
#define security_add_hooks(...) \
	__bbg_add_hooks_select(__VA_ARGS__, __bbg_add_hooks_3, \
			       __bbg_add_hooks_2)(__VA_ARGS__)

#endif
