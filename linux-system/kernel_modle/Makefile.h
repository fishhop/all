ifneq ($(KERNELRELEASE),)
obj-m := hello.o
else
KERNELDR := E:\other code\linux-2.6.32.20\linux-2.6.32.20
PWD := $(shell pwd)  

modules:  
    $(MAKE) -C $(KERNELDR) M=$(PWD) modules  
moduels_install:  
    $(MAKE) -C $(KERNELDR) M=$(PWD) modules_install  
clean:
     rm -f *.ko *.o *.mod.o *.mod.c *.symvers modul*
endif