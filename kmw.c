#include <linux/module.h>

#include "kmw.h"

static int kmw_demo_param = 0;
module_param(kmw_demo_param, int, 0644);

// defines for device infrastructure
#define		KMWNAME			"kmw"

static int kmw_init(void)
{
	PDEBUG("init - demo param: %d\n", kmw_demo_param);
	return 0;
}

static void kmw_exit(void)
{
	PDEBUG("exit - demo param: %d\n", kmw_demo_param);
}

module_init(kmw_init);
module_exit(kmw_exit);

MODULE_LICENSE("GPL");
