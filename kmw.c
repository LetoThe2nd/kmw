#include <linux/module.h>

#include "kmw.h"

// defines for device infrastructure
#define		KMWNAME			"kmw"

static int kmw_init(void)
{
	PDEBUG("init\n");
	return 0;
}

static void kmw_exit(void)
{
	PDEBUG("exit\n");
}

module_init(kmw_init);
module_exit(kmw_exit);

MODULE_LICENSE("GPL");
