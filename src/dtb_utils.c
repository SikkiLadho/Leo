#include "dtb_utils.h"
#include "printf.h" //printf


void enable_psci_all(void * dtb_addr)
{
    
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



void removeInitRamfs(void * dtb_addr)
{
    int chosen;
	if (fdt_check_header((const void*)dtb_addr) == 0) {

		printf("DTB is a valid DTB. \r\n");

		//getting the offset to chosen node
		chosen = fdt_subnode_offset((const void*)dtb_addr, 0, "chosen"); 

		//deleting the "linux,initrd-end" and  "linux,initrd-start"
		if (fdt_delprop(dtb_addr, chosen, "linux,initrd-end") == 0 && fdt_delprop(dtb_addr, chosen, "linux,initrd-start") == 0) {
			printf("Deleted \"linux,initrd-end\" and  \"linux,initrd-start\" from DTB.\r\n");
			int cpus_node;
			cpus_node = fdt_subnode_offset((const void*)dtb_addr, 0, "cpus");
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
	
}