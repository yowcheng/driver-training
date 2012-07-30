#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x5eadf54a, "module_layout" },
	{ 0xb4b4ced3, "platform_device_unregister" },
	{ 0xbb3be524, "sysfs_remove_group" },
	{ 0x594f6650, "input_unregister_device" },
	{ 0x10671fe5, "input_register_device" },
	{ 0x60ff388b, "input_set_abs_params" },
	{ 0x7adf6613, "input_allocate_device" },
	{ 0x8904f20, "sysfs_create_group" },
	{ 0x50eedeb8, "printk" },
	{ 0xcd501367, "platform_device_register_full" },
	{ 0x3f637ff5, "input_event" },
	{ 0x42224298, "sscanf" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "2AF11329A13D77F68132099");
