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
	{ 0xef0eea15, "module_layout" },
	{ 0xea147363, "printk" },
	{ 0x991b3a49, "__register_chrdev" },
	{ 0x9edbecae, "snprintf" },
	{ 0xbb64fac0, "module_put" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xacdeb154, "__tracepoint_module_get" },
	{ 0x5ecfeec6, "__per_cpu_offset" },
	{ 0x9629486a, "per_cpu__cpu_number" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

