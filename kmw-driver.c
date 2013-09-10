#include <linux/device.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include <linux/string.h>

#include "kmw.h"

// defines for device infrastructure
#define		KMWATTRGROUPNAME	KMWNAME "attrs"

// functionality for driver
static struct platform_device * kmw_device = NULL;

// functions for driver
static ssize_t kmw_attr_show(struct device_driver * driver, char * buf)
{
	PDEBUG("driver attr_show\n");
	return 0;
};

static ssize_t kmw_attr_store(struct device_driver * driver, const char * buf, size_t count)
{
	struct kmw_ops * ops = kmw_device->dev.platform_data;
	PDEBUG("driver attr_store\n");
	ops->set_output(buf[0]);
	return count;
};

static int kmw_driver_probe(struct platform_device * pdev)
{
	int err = 0;
	PDEBUG("driver probe target: %s...\n", pdev->name);
	if (strncmp(KMWNAME, pdev->name, 3) != 0)
	{
		PDEBUG("...name not matching\n");
		err = -1;
		goto err1;
	}
	if (kmw_device != NULL)
	{
		PDEBUG("... already bound\n");
		err = -2;
		goto err2;
	}
	kmw_device = pdev;

	PDEBUG("...probe successful\n");
	return 0;
err2:
err1:
	return err;
};

static int kmw_driver_remove(struct platform_device * pdev)
{
	PDEBUG("driver remove\n");
	if (kmw_device == pdev)
	{
		PDEBUG("...unbound\n");
		kmw_device = NULL;
	}
	return 0;
};

// variables for driver
static DRIVER_ATTR(kmw_attr, S_IRUGO | S_IWUSR, kmw_attr_show, kmw_attr_store);

static struct attribute * kmw_drv_attrs[] = {
	&driver_attr_kmw_attr.attr,
	NULL,
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
	.probe = kmw_driver_probe,
	.remove = kmw_driver_remove,
	.driver = {
		.name = KMWNAME,
		.owner = THIS_MODULE,
		.groups = kmw_drv_attrs_grps,
	},
};

module_platform_driver(kmw_driver);
MODULE_LICENSE("GPL");
