#ifndef _LINUX_KMW_H
#define _LINUX_KMW_H

// kmw-global defines
#define		KMWNAME			"kmw"

// defines for debugging
#define DEBUG

#undef PDEBUG
#ifdef DEBUG
#define PDEBUG(fmt, args...) printk( KERN_DEBUG KMWNAME ": " fmt, ## args)
#else
#define PDEBUG(fmt, args...)
#endif

#endif // _LINUX_KMW_H
