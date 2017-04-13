#include <linux/module.h>
#include <linux/version.h>
#include <asm/unistd.h>


/* IOCTL commands */
#define IOCTL_PATCH_TABLE 0x00000001
#define IOCTL_FIX_TABLE   0x00000004

/**
 *    # cat /boot/System.map-$(uname -r) | grep sys_call_table
 *    ffffffff816a0820 R sys_call_table
 */
unsigned long* sys_call_table = (unsigned long*) 0xffffffff816a0820;

asmlinkage int (*original_open) (const char *, int, mode_t);
asmlinkage ssize_t (*original_read) (int, void *, size_t);

int demo_fd = -1;


asmlinkage int demo_open(const char *pathname, int flags, mode_t mode)
{
  return original_open(pathname, flags, mode);
}


asmlinkage ssize_t demo_read(int fd, void *buf, size_t count)
{
  return original_read(fd, buf, count);
}


static int __init demo_init_module(void)
{
  printk(KERN_INFO "Hello world.\n");

  original_open = sys_call_table[__NR_open];
  sys_call_table[__NR_open] = demo_open;

  original_read = sys_call_table[__NR_read];
  sys_call_table[__NR_read] = demo_read;

  return 0;   // successfully loaded kernel module
}


static void __exit demo_cleanup_module(void)
{
  printk(KERN_INFO "Goodbye world.\n");
  sys_call_table[__NR_read] = original_read;
  sys_call_table[__NR_open] = original_open;
}


module_init(demo_init_module);
module_exit(demo_cleanup_module);
