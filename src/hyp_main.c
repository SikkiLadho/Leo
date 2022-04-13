#include "printf.h" //printf
#include "mini_uart.h" //uart_init
#include "utils.h" //eret_to_el2
#include "dtb_utils.h" //spin_tbl_to_psci, removeInitRamfs
#include "mm.h"
#include "config.h" //LOAD_ADDRESS, MAX_CPUS


/* Hypervisor main function */
void hyp_main( void * dtb_addr)
{
	
	/* Initialize UART. */
	uart_init();

	printf("Leo Hypervisor Running...\r\n");
	int current_el = get_el(); //get current exception level
	printf("Current Exception level: %d \r\n", current_el);
	printf("DTB Address: %x \r\n", dtb_addr);

	// change enable-method for MAX_CPUS cpus to psci
	for(int cpu=0;cpu<MAX_CPUS; cpu++)
    {
        spin_tbl_to_psci(dtb_addr,cpu);
    }

	removeInitRamfs(dtb_addr);

	/* ASM function, which erets to EL2 at position #0x400000, where linux kernel is loaded. */
	eret_to_el2(dtb_addr,LOAD_ADDRESS);
}

