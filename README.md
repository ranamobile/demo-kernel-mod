# Introduction

A kernel module extends the functionality of the kernel on demand without rebuilding or rebooting the system.


# Building the Kernel Modules

Prerequisites:
* make
* gcc
* kernel-headers
* kernel-devel

*Note* - This demo was written and tested on kernel 3.x. It probably won't work for 2.x or 4.x.

{{obj-m}} specified object files which are built as loadable kernel modules.


# Helpful Commands

```
insmod
rmmod
modprobe
modinfo
```


# References

* http://www.tldp.org/LDP/lkmpg/2.6/html/index.html
* https://www.kernel.org/doc/Documentation/kbuild/makefiles.txt
