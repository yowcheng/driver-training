#
# Makefile for Platform driver test 
#

KVERSION := $(shell uname -r)

ifneq ($(KERNELRELEASE),)

obj-m := device.o driver.o

else

KDIR := /lib/modules/$(KVERSION)/build
all:
	 make -C $(KDIR) M=$(PWD) modules
clean:
	 rm -f *.ko *.o *.mod.o *.mod.c *.symvers

endif
