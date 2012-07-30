#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
      printk (KERN_ALERT "Hello, we are in the module!\n");
        return 0;
}

static void hello_exit(void)
{
      printk(KERN_ALERT "Goodbye, out of module!\n");
}

MODULE_LICENSE("Dual BSD/GPL");
module_init(hello_init);
module_exit(hello_exit);
