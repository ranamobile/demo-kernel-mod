/**
 * Simple kernel module that does nothing.
 */
#include <linux/module.h>
#include <linux/kernel.h>


int init_module(void)
{
  printk(KERN_INFO "Hello sweetie.\n");
  return 0;   /* 0 means the kernel module was successfully loaded */
}


void cleanup_module(void)
{
  printk(KERN_INFO "Geronimo.\n");
}
