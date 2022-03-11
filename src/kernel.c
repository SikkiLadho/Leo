#include "printf.h"
#include "mini_uart.h"
#include "utils.h"

int fdt_check_header(const void *fdt);
int fdt_delprop(void *fdt, int nodeoffset, const char *name);
int fdt_subnode_offset(const void *fdt, int parentoffset, const char *name);

void kernel_main( void * dtb_addr)
{
	
	uart_init();

	printf("Leo Hypervisor Running...\n");

	int el = get_el();
	printf("Exception level: %d \r\n", el);
	printf("DTB Address: %x \r\n", dtb_addr);

	/*

	Kernel is being loaded into memory by using the initramfs configuration in /boot/config.txt. 
	Initramfs config is usually used to load initrd/initramfs file[1]. When firmware reads the 
	initramsconfig, it believes that an initrd image is being loaded, therefore firmware adds 
	start and end address of the loaded image in chosen node of DTB[2].
	The Linux kerenl in Raspbian does not use initrd images by default. However, after kernel sees the initrd 
	addresses in the DTB, it expects the initrd image. In order to solve this, we need to remove the 
	initrd properties from DTB before loading the kernel. We use libfdt library to remove these properties.

	[1] https://www.raspberrypi.com/documentation/computers/config_txt.html#initramfs
	[2] https://elinux.org/Device_Tree_Usage#chosen_Node
	
	*/

	int chosen;

	//sanity check for DTB.
	if (fdt_check_header((const void*)dtb_addr) == 0) {

		printf("DTB is a valid DTB. \n");

		//getting the offset to chosen node
		chosen = fdt_subnode_offset((const void*)dtb_addr, 0, "chosen"); 

		//deleting the "linux,initrd-end" and  "linux,initrd-start"
		if (fdt_delprop(dtb_addr, chosen, "linux,initrd-end") == 0 && fdt_delprop(dtb_addr, chosen, "linux,initrd-start") == 0) {
			printf("Deleted \"linux,initrd-end\" and  \"linux,initrd-start\" from DTB.\n");
			printf("Jumping into Linux kernel...\n");
		}
		else {
			printf("Could not delete delete \"linux,initrd-end\" and \"linux,initrd-start\" from DTB.\n");
			printf("Virtual Machine might not work properly.\n");
		}
	}
	else {
		printf("DTB is not a valid DTB. Virtual Machine might not work properly.\n");
	}
	
	//jumping to linux kernel image at EL1 with DTB address in the X0 register.
	jump(dtb_addr);
}


