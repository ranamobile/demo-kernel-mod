/**
 * Kernel module that overwrites the open() system call.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>     /* init and exit macros */
#include <linux/unistd.h>


/* IOCTL commands */
#define IOCTL_PATCH_TABLE 0x00000001
#define IOCTL_FIX_TABLE   0x00000004

/**
 * Set this to the address of your system call table. You can find it
 * by running the following command:
 *
 *    # cat /boot/System.map-$(uname -r) | grep sys_call_table
 *    ffffffff816a0820 R sys_call_table
 */
unsigned long* sys_call_table = (unsigned long*) 0xffffffff816a0820;

// Use this to keep track of the original system call function
asmlinkage int (*original_open) (const char *, int, mode_t);

/**
 * Custom open system call that detects when files with a prefix of "awesome"
 * are opened. Then calls the original open call to not break anything.
 */
asmlinkage int demo_open(const char *pathname, int flags, mode_t mode)
{
  if (strncmp(pathname, "awesome", 7) == 0)
  {
    printk(KERN_INFO "You opened an awesome file");
  }

  return original_open(pathname, flags, mode);
}


static int __init demo_init_module(void)
{
  printk(KERN_INFO "I'm watching you.\n");

  // Save the original system call and replace it with our custom one.
  original_open = sys_call_table[__NR_open];
  sys_call_table[__NR_open] = demo_open;

  return 0;   /* 0 means the kernel module was successfully loaded */
}


static void __exit demo_cleanup_module(void)
{
  printk(KERN_INFO "O_O\n");

  // Restore original system call before exiting
  sys_call_table[__NR_open] = original_open;
}


module_init(demo_init_module);      /* attach init module function */
module_exit(demo_cleanup_module);   /* attach exit module function */
