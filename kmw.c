#include <linux/module.h>
#include <linux/platform_device.h>

#include "kmw.h"

// defines for device infrastructure
#define		KMWNAME			"kmw"
#define		KMWDRIVERNAME		KMWNAME "driver"
#define		KMWATTRGROUPNAME	KMWNAME "attrs"

// variables for driver
static struct attribute * kmw_drv_attrs[] = {
	NULL
};

static struct attribute_group kmw_drv_attrs_grp = {
	.name = KMWATTRGROUPNAME,
	.attrs = kmw_drv_attrs,
};

static const struct attribute_group * kmw_drv_attrs_grps[] = {
	&kmw_drv_attrs_grp,
	NULL,
};

static struct platform_driver kmw_driver = {
	.driver = {
		.name = KMWDRIVERNAME,
		.owner = THIS_MODULE,
		.groups = kmw_drv_attrs_grps,
	},
};

static int kmw_init(void)
{
	int err;
	PDEBUG("init\n");
	// register our driver:
	err = platform_driver_register(&kmw_driver);
	if (err < 0)
		goto err1;
	return 0;
err1:
	return err;
}

static void kmw_exit(void)
{
	// unregister our driver
	platform_driver_unregister(&kmw_driver);
	PDEBUG("exit\n");
}

module_init(kmw_init);
module_exit(kmw_exit);

MODULE_LICENSE("GPL");
