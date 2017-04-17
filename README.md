# Introduction

A kernel module extends the functionality of the kernel on demand without rebuilding or rebooting the system, which is ideal for device drivers.


# Building the Kernel Modules

## Prerequisites

* make
* gcc
* kernel headers

On CentOS:

```
sudo yum install -y make gcc kernel-headers
```

## Makefile

```
obj-m += module_name.o

all:
  make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
  make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

`obj-m` specified object files which are built as loadable kernel modules.

`-C dir` changes the directory to the `dir` directory before reading makefiles. We need this to compile in the correct kernel module path to access the correct libraries.

`M=dir` specifies an external directory to build. Since we used `-C` to change directories, we need `M=` to indicate where the source directory is for the external module.

`modules` indicates to build (but not install) the kernel module.

## Building

```
make
```

WOW~!!!

This creates several files:

* `.o` - object files for kernel module
* `.mod.c` - generated source with data structures describing the kernel module
* `.mod.o` - object file for generated source
* `.ko` - resulting kernel module with linked object files
* `.cmd`
  - build system takes care of executing the command as necessary
  - these are loaded when make is run again to determine whether to rebuild a target
  - optimize the performance of build system

# Helpful Commands

* `modinfo` - Get info about a kernel module.
* `insmod` - Load a kernel module by its path.
* `rmmod` - Unload a kernel module by its name.
* `modprobe` - Load and unload kernel modules from the `/lib/modules/$(uname -r)/` directory.


# References

* http://www.tldp.org/LDP/lkmpg/2.6/html/index.html
* https://www.kernel.org/doc/Documentation/kbuild/makefiles.txt
* http://derekmolloy.ie/writing-a-linux-kernel-module-part-1-introduction/
