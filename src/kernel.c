#include "printf.h"
#include "mini_uart.h"
#include "utils.h"

int fdt_check_header(const void *fdt);
int fdt_delprop(void *fdt, int nodeoffset, const char *name);
int fdt_subnode_offset(const void *fdt, int parentoffset, const char *name);
int fdt_setprop(void *fdt, int nodeoffset, const char *name, const void *val, int len);

//change enable-method for given cpu node from spin-table to psci
void spin_tbl_to_psci(void * dtb_addr, int cpu);
void kernel_main( void * dtb_addr)
{
	
	uart_init();

	printf("Leo Hypervisor Running...\r\n");
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

		printf("DTB is a valid DTB. \r\n");

		//getting the offset to chosen node
		chosen = fdt_subnode_offset((const void*)dtb_addr, 0, "chosen"); 

		//deleting the "linux,initrd-end" and  "linux,initrd-start"
		if (fdt_delprop(dtb_addr, chosen, "linux,initrd-end") == 0 && fdt_delprop(dtb_addr, chosen, "linux,initrd-start") == 0) {
			printf("Deleted \"linux,initrd-end\" and  \"linux,initrd-start\" from DTB.\r\n");
			int cpus_node;
			cpus_node = fdt_subnode_offset((const void*)dtb_addr, 0, "cpus");
			if(cpus_node >= 0)
			{
				int cpu;
				
				cpu  = fdt_subnode_offset((const void*)dtb_addr, cpus_node, "cpu@0");
				spin_tbl_to_psci(dtb_addr,cpu);

				cpu  = fdt_subnode_offset((const void*)dtb_addr, cpus_node, "cpu@1");
				spin_tbl_to_psci(dtb_addr,cpu);

				cpu  = fdt_subnode_offset((const void*)dtb_addr, cpus_node, "cpu@2");
				spin_tbl_to_psci(dtb_addr,cpu);
				
				cpu  = fdt_subnode_offset((const void*)dtb_addr, cpus_node, "cpu@3");
				spin_tbl_to_psci(dtb_addr,cpu);	
			}
			else
			{
				printf("OOPS. Not Found.\r\n");
			}
			printf("Jumping into Linux kernel...\r\n");

		}
		else {
			printf("Could not delete delete \"linux,initrd-end\" and \"linux,initrd-start\" from DTB.\r\n");
			printf("Virtual Machine might not work properly.\r\n");
		}
	}
	else {
		printf("DTB is not a valid DTB. Virtual Machine might not work properly.\r\n");
	}
	
	//jumping to linux kernel image at EL1 with DTB address in the X0 register.
	jump(dtb_addr);
}


void spin_tbl_to_psci(void * dtb_addr, int cpu)
{
		if(cpu>=0)
				{
					int changed  = fdt_setprop(dtb_addr, cpu,"enable-method",
		"psci", 5);		
					int deleted = fdt_delprop(dtb_addr, cpu, "cpu-release-addr");

					if(changed==0 && deleted == 0)
					{
						printf("CHANGED THE ENABLE METHOD TO PSCI.\r\n");
					}
					else
					{
						printf("Could not change enable method from to psci.\r\n");
					}

				}
				else
				printf("oops, not found.\r\n");
}