#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>     // init and exit macros


static int __init demo_init_module(void)
{
  printk(KERN_INFO "Hello world.\n");

  return 0;   // successfully loaded kernel module
}


static void __exit demo_cleanup_module(void)
{
  printk(KERN_INFO "Goodbye world.\n");
}


module_init(demo_init_module);
module_exit(demo_cleanup_module);
