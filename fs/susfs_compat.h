/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _SUSFS_LEGACY_COMPAT_H
#define _SUSFS_LEGACY_COMPAT_H

/* Compatibility for SUSFS sources injected by the external build workflow. */
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

#ifdef SUSFS_NEEDS_LEGACY_READ
static inline int zc_susfs_kernel_read(struct file *file, void *buf,
				     size_t count, loff_t *pos)
{
	int ret = kernel_read(file, *pos, buf, count);

	if (ret > 0)
		*pos += ret;
	return ret;
}
#define kernel_read(file, buf, count, pos) \
	zc_susfs_kernel_read(file, buf, count, pos)
#endif

#ifdef SUSFS_NEEDS_KVMALLOC
static inline void *zc_susfs_kvmalloc(size_t size, gfp_t flags)
{
	void *ptr = kmalloc(size, flags);

	/* vmalloc may sleep; only use the fallback for GFP_KERNEL requests. */
	if (!ptr && (flags & GFP_KERNEL) == GFP_KERNEL)
		ptr = __vmalloc(size, flags);
	return ptr;
}
#define susfs_kvmalloc(size, flags) zc_susfs_kvmalloc(size, flags)
#endif

#endif
