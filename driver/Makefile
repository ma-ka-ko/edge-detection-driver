
obj-m += edge-detect-km.o


all:
	make -C /lib/modules/$(shell uname -r)/build  M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build  M=$(PWD) clean

install:
	echo -n "Module: insmod edge-detect-km.ko : "
	insmod edge-detect-km.ko 
#	chown root:root /dev/edge
	chmod 666 /dev/edge
	
uninstall:
	rmmod edge_detect_km
