obj-m += demo_hello.o
obj-m += demo_macro.o
obj-m += demo_hook.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
