#include "dtb_utils.h"
#include "printf.h" //printf



//change enable method for a cpu given cpu node offset
void spin_tbl_to_psci(void * dtb_addr, int cpu, int cpu_num)
{
		if(cpu>=0) 
			{	
				int changed  = fdt_setprop(dtb_addr, cpu,"enable-method","psci", 5);
				int deleted = fdt_delprop(dtb_addr, cpu, "cpu-release-addr");

				if(changed==0 && deleted == 0)
				{
					printf("Changed the enable method to psci for CPU%d.\r\n", cpu_num);
				}
				else
				{
					printf("Could not change enable method from to psci for CPU%d.\r\n", cpu_num);
				}
			}
		else
		{
			printf("CPU%d not found in the device tree.\r\n", cpu_num);
		}
}


void spin_table_psci_all(void * dtb_addr)
{

	int cpus_node = fdt_subnode_offset((const void*)dtb_addr, 0, "cpus");
	int cpu;

	cpu  = fdt_subnode_offset((const void*)dtb_addr, cpus_node, "cpu@0");
    spin_tbl_to_psci(dtb_addr,cpu, 0);

	cpu  = fdt_subnode_offset((const void*)dtb_addr, cpus_node, "cpu@1");
    spin_tbl_to_psci(dtb_addr,cpu, 1);
	
	// cpu  = fdt_subnode_offset((const void*)dtb_addr, cpus_node, "cpu@2");
    // spin_tbl_to_psci(dtb_addr,cpu, 2);
	
	// cpu  = fdt_subnode_offset((const void*)dtb_addr, cpus_node, "cpu@3");
    // spin_tbl_to_psci(dtb_addr,cpu, 3);


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
			fdt_subnode_offset((const void*)dtb_addr, 0, "cpus");
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

