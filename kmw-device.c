#include <linux/module.h>
#include <linux/platform_device.h>

#include "kmw.h"

void    kmw_release(struct device *dev)
{
	PDEBUG("device release\n");
}

static struct platform_device kmw_device = {
	.name = KMWNAME,
	.dev = {
		.release = kmw_release,
	}
};

static int kmw_device_init(void)
{
	int err;

	PDEBUG("device_init\n");
	err = platform_device_register(&kmw_device);
	if (err < 0)
		goto err1;
	return 0;
err1:
	return err;
}

static void kmw_device_exit(void)
{
	PDEBUG("device_exit\n");
	platform_device_unregister(&kmw_device);
}

module_init(kmw_device_init);
module_exit(kmw_device_exit);

MODULE_LICENSE("GPL");
