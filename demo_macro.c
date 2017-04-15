/**
 * Simple kernel module that does still nothing.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>     /* init and exit macros */


static int __init demo_init_module(void)
{
  printk(KERN_INFO "I am slowly going crazy.\n");
  return 0;   /* 0 means the kernel module was successfully loaded */
}


static void __exit demo_cleanup_module(void)
{
  printk(KERN_INFO "One 2 11 IV cinco 六 switch.\n");
}


module_init(demo_init_module);      /* attach init module function */
module_exit(demo_cleanup_module);   /* attach exit module function */
