#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>     // init and exit macros
#include <linux/unistd.h>


/* IOCTL commands */
#define IOCTL_PATCH_TABLE 0x00000001
#define IOCTL_FIX_TABLE   0x00000004

/**
 *    # cat /boot/System.map-$(uname -r) | grep sys_call_table
 *    ffffffff816a0820 R sys_call_table
 */
unsigned long* sys_call_table = (unsigned long*) 0xffffffff816a0820;

asmlinkage int (*original_open) (const char *, int, mode_t);


asmlinkage int demo_open(const char *pathname, int flags, mode_t mode)
{
  if (strncmp(pathname, "awesome", 7) == 0)
  {
    printk(KERN_INFO "found awesome");
  }

  return original_open(pathname, flags, mode);
}


static int __init demo_init_module(void)
{
  printk(KERN_INFO "Hello world.\n");

  original_open = sys_call_table[__NR_open];
  sys_call_table[__NR_open] = demo_open;

  return 0;   // successfully loaded kernel module
}


static void __exit demo_cleanup_module(void)
{
  printk(KERN_INFO "Goodbye world.\n");
  sys_call_table[__NR_open] = original_open;
}


module_init(demo_init_module);
module_exit(demo_cleanup_module);
