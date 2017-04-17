/**
 * Kernel module that overwrites the open() system call.
 */
#include <linux/module.h>   /* core header for kernel modules */
#include <linux/kernel.h>   /* kernel-specific types, macros and functions */
#include <linux/init.h>     /* init and exit macros */
#include <linux/unistd.h>


/**
 * These macros provide information to modinfo.
 */
MODULE_LICENSE("MIT License");
MODULE_AUTHOR("Ariana Hong");
MODULE_DESCRIPTION("Example kernel module that hooks the open() system call.");
MODULE_VERSION("0.1");


/**
 * Set this to the address of your system call table. You can find it by
 * running the following command:
 *
 *    # cat /boot/System.map-$(uname -r) | grep sys_call_table
 *    ffffffff816a0820 R sys_call_table
 */
unsigned long* sys_call_table = (unsigned long*) 0xffffffff816a0820;

/**
 * Use this to keep track of the original system call function. This is
 * especially important to restore the original functionality of the kernel if
 * and when this custom kernel module is unloaded.
 */
asmlinkage int (*original_open) (const char *, int, mode_t);

/**
 * Custom open system call that detects when files with a prefix of "awesome"
 * are opened. Then calls the original open call to not break anything.
 */
asmlinkage int demo_open(const char *pathname, int flags, mode_t mode)
{
  if (strncmp(pathname, "awesome", 7) == 0)
  {
    printk(KERN_INFO "You opened an awesome file.\n");
  }

  return original_open(pathname, flags, mode);
}


/**
 * The initialization function registers the custom function to the system call
 * table by overwriting the original function. The original function is saved
 * to preserve the original functionality in the custom function and to restore
 * the original functionality when the module is unloaded.
 */
static int __init demo_init_module(void)
{
  printk(KERN_INFO "I'm watching you.\n");
  original_open = sys_call_table[__NR_open];
  sys_call_table[__NR_open] = demo_open;
  return 0;   /* 0 means the kernel module was successfully loaded */
}


/**
 * The original functionality of the kernel is restored by writing the original
 * function back to the system call table.
 */
static void __exit demo_cleanup_module(void)
{
  printk(KERN_INFO "O_O\n");
  sys_call_table[__NR_open] = original_open;
}


module_init(demo_init_module);      /* attach init module function */
module_exit(demo_cleanup_module);   /* attach exit module function */
