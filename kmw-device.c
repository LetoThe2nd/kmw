#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include "kmw.h"

#undef KMW_USE_GPIO
#ifdef CONFIG_ARCH_OMAP
#ifdef CONFIG_GPIOLIB
#define KMW_USE_GPIO
#endif
#endif

static unsigned int kmw_dev_led_red = 7;
static unsigned int kmw_dev_led_green = 50;
static unsigned int kmw_dev_led_blue = 51;

module_param(kmw_dev_led_red, uint, 0644);
module_param(kmw_dev_led_green, uint, 0644);
module_param(kmw_dev_led_blue, uint, 0644);

static unsigned int * const kmw_dev_leds[] = {
	&kmw_dev_led_red,
	&kmw_dev_led_green,
	&kmw_dev_led_blue,
};

#define KMW_DEV_LED_COUNT (sizeof(kmw_dev_leds)/sizeof(unsigned int *))

void    kmw_release(struct device *dev)
{
	PDEBUG("device release\n");
}

void	kmw_set_output(unsigned int value)
{
	int i;
	for (i = 0; i < KMW_DEV_LED_COUNT; ++i)
	{
		PDEBUG("device - set led%d @ gpio %u to %s\n", i, *kmw_dev_leds[i], ((value & (1L << i)) ? "high" : "low"));
#ifdef KMW_USE_GPIO
		gpio_direction_output(*kmw_dev_leds[i], (value & (1L << i)));
#endif
	}
}

static struct kmw_ops kmw_device_ops = {
	.set_output = kmw_set_output,
};

static struct platform_device kmw_device = {
	.name = KMWNAME,
	.dev = {
		.release = kmw_release,
		.platform_data = &kmw_device_ops,
	}
};

static int kmw_device_init(void)
{
	int err;

	PDEBUG("device_init\n");
#ifdef KMW_USE_GPIO
	err = gpio_request(kmw_dev_led_red, KMWNAME "_led_red");
	if (err < 0)
		goto err1;
	err = gpio_request(kmw_dev_led_green, KMWNAME "_led_green");
	if (err < 0)
		goto err2;
	err = gpio_request(kmw_dev_led_blue, KMWNAME "_led_blue");
	if (err < 0)
		goto err3;
#endif
	err = platform_device_register(&kmw_device);
	if (err < 0)
		goto err4;
	return 0;
err4:
#ifdef KMW_USE_GPIO
	gpio_free(kmw_dev_led_blue);
err3:
	gpio_free(kmw_dev_led_green);
err2:
	gpio_free(kmw_dev_led_red);
err1:
#endif
	return err;
}

static void kmw_device_exit(void)
{
	PDEBUG("device_exit\n");
#ifdef KMW_USE_GPIO
	gpio_free(kmw_dev_led_red);
	gpio_free(kmw_dev_led_green);
	gpio_free(kmw_dev_led_blue);
#endif
	platform_device_unregister(&kmw_device);
}

module_init(kmw_device_init);
module_exit(kmw_device_exit);

MODULE_LICENSE("GPL");
