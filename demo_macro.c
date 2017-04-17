/**
 * Simple kernel module that does still nothing.
 */
#include <linux/module.h>   /* core header for kernel modules */
#include <linux/kernel.h>   /* kernel-specific types, macros and functions */
#include <linux/init.h>     /* init and exit macros */


/**
 * These macros provide information to modinfo.
 */
MODULE_LICENSE("MIT License");
MODULE_AUTHOR("Ariana Hong");
MODULE_DESCRIPTION("Hello world kernel module with init and exit macros.");
MODULE_VERSION("0.1");


/**
 * Kernel modules are not applications, and hence do not have a main()
 * function. Instead they register themselves to handle certain events. This
 * init_module() function runs and then exits. The kernel module then behavior
 * like an event-driven program.
 */
static int __init demo_init_module(void)
{
  /**
   * Kernel module cannot access printf() function or other user space
   * libraries. It has its own memory address space. printk() is a kernel space
   * function that writes to the kernel ring buffer, or dmesg.
   */
  printk(KERN_INFO "I am slowly going crazy.\n");
  return 0;   /* 0 means the kernel module was successfully loaded */
}


/**
 * Kernel modules also do not cleanup after themselves. This cleanup_module()
 * is run when a kernel module is unloaded. The cleanup must be manually coded
 * in this function to safely unload a kernel. For example, if your kernel
 * module loaded a device driver, you would unload it here.
 */
static void __exit demo_cleanup_module(void)
{
  printk(KERN_INFO "One 2 11 IV cinco 六 switch.\n");
}


/**
 * The module_init() and module_exit() methods take static __init and __exit
 * functions to overwrite the default init_module() and exit_module()
 * functions. These are the initialization and cleanup functions for a kernel
 * module.
 */
module_init(demo_init_module);      /* attach init module function */
module_exit(demo_cleanup_module);   /* attach exit module function */
