#ifndef DTB_UTILS_H
#define DTB_UTILS_H




    /*
    declaring libfdt functions, which is statically linked with hypervisor binary(kernel8.img), 
    which will be used to edit the Device Tree Blob 
    */

int fdt_check_header(const void *fdt); 
int fdt_delprop(void *fdt, int nodeoffset, const char *name);
int fdt_subnode_offset(const void *fdt, int parentoffset, const char *name);
int fdt_setprop(void *fdt, int nodeoffset, const char *name, const void *val, int len);


	/*		
	The function modifies the device tree blob to use psci, 
    instead of spin-table as enable-method[1] for cpus, because we 
    would like to trap the PSCI smcs and bring up secondary cpus in El1 
    instead of El2. See github issue[2]
	
	[1] https://www.kernel.org/doc/Documentation/devicetree/bindings/arm/cpus.txt
    [2] https://github.com/SikkiLadho/Leo/issues/6
	*/ 

void spin_table_psci_all(void * dtb_addr);
void spin_tbl_to_psci(void * dtb_addr, int cpu, int cpu_num);


    /* 
	Following removes initramfs property because it was added as a
	side effect of loading the linux kernel by using initramfs[1] 
    config in config.txt. See github Issue[2]
    
    [1] https://www.raspberrypi.com/documentation/computers/config_txt.html#initramfs
    [2] https://github.com/SikkiLadho/Leo/issues/2
    */
void removeInitRamfs(void * dtb_addr);

#endif