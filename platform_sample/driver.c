#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/platform_device.h>

MODULE_AUTHOR("Yow-Cheng Yeh");
MODULE_LICENSE("Dual BSD/GPL");
static int my_probe(struct device* dev)
{
    printk("driver found device which my driver can handle!/n");
    return 0;
}

static int my_remove(struct device* dev)
{
    printk("drvier found device unpluged!/n");
}

static struct platform_driver my_driver = {
    .probe = my_probe,
    .remove = my_remove,
    .driver = {
    .owner = THIS_MODULE,
    .name = "my_dev",
    },
};

static int __init my_driver_init(void)
{
    return platform_driver_register(&my_driver);
}

static void my_driver_exit(void)
{
    platform_driver_unregister(&my_driver);
}

module_init(my_driver_init);
module_exit(my_driver_exit);
