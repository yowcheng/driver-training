/*
* A Virtual Mouse Driver to send fake events from userspace.
*
* Written by Fred Chien <fred@ullab.org>
*
*/
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/pci.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/io.h>

struct input_dev *virmouse_input_dev;
static struct platform_device *virmouse_dev; /* Device structure */

/* Sysfs method to input simulated coordinates */
static ssize_t write_virmouse(struct device *dev,
	struct device_attribute *attr,
	const char *buffer, size_t count)
{
    int x, y, key;

    /* parsing input data */
    sscanf(buffer, "%d%d%d", &x, &y, &key);

    input_report_abs(virmouse_input_dev, ABS_X,x);
    input_report_abs(virmouse_input_dev, ABS_Y,y);

    if(key>0){
	input_report_key(virmouse_input_dev, BTN_LEFT,   0x40);
    }else{
	input_report_key(virmouse_input_dev, BTN_LEFT,   0x00);
    }

    input_sync(virmouse_input_dev);

    return count;

}

/* Attach the sysfs write method */
DEVICE_ATTR(vmevent, 0644, NULL, write_virmouse);

/* Attribute Descriptor */
static struct attribute *virmouse_attrs[] = {
    &dev_attr_vmevent.attr,
    NULL
};

/* Attribute group */
static struct attribute_group virmouse_attr_group = {
    .attrs = virmouse_attrs,
};

/* Driver Initializing */
int __init virmouse_init(void)
{
    int err;
    /* Register a platform device */
    virmouse_dev = platform_device_register_simple("virmouse", -1, NULL, 0);
    if (IS_ERR(virmouse_dev)){
	printk ("virmouse_init: error\n");
	return PTR_ERR(virmouse_dev);
    }

    /* Create a sysfs node to read simulated coordinates */
    sysfs_create_group(&virmouse_dev->dev.kobj, &virmouse_attr_group);


    virmouse_input_dev = input_allocate_device();
    if (!virmouse_input_dev) {
	printk("Bad input_allocate_device()\n");
	return -ENOMEM;
    }

    virmouse_input_dev->name = "Acorn RiscPC Mouse";
    virmouse_input_dev->phys = "rpcmouse/input0";
    virmouse_input_dev->id.bustype = BUS_HOST;
    virmouse_input_dev->id.vendor  = 0x0005;
    virmouse_input_dev->id.product = 0x0001;
    virmouse_input_dev->id.version = 0x0100;

    virmouse_input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
    virmouse_input_dev->keybit[BIT_WORD(BTN_LEFT)] = BIT_MASK(BTN_LEFT) |
	BIT_MASK(BTN_MIDDLE) | BIT_MASK(BTN_RIGHT);
    input_set_abs_params(virmouse_input_dev, ABS_X, 0, 2000, 0, 0);
    input_set_abs_params(virmouse_input_dev, ABS_Y, 0, 2000, 0, 0);

    err = input_register_device(virmouse_input_dev);
    return err;
}

/* Driver Uninitializing */
void virmouse_uninit(void)
{
    /* Unregister from the input subsystem */
    input_unregister_device(virmouse_input_dev);

    /* Remove sysfs node */
    sysfs_remove_group(&virmouse_dev->dev.kobj, &virmouse_attr_group);

    /* Unregister driver */
    platform_device_unregister(virmouse_dev);

    return;
}

module_init(virmouse_init);
module_exit(virmouse_uninit);

MODULE_AUTHOR("Fred Chien <fred@ullab.org>");
MODULE_DESCRIPTION("Virtual Mouse Driver");
MODULE_LICENSE("GPL");

