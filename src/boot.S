#include "mm.h"
.section ".text.boot"

.globl _start
_start:

	b actual_start
	/* using the linux kernel image header to 'sell' this hypervisor to botoloader as the Linux Kernel
		so that bootloader "hopefully" setups everything as it would do for the linux kernel. 

		Before jumping to kernel, there are few conditions which 
		should be met(i.e setting x0, with the address for dtb): 
		
		explained in linux Documentation/arm64/booting.rst

	 */
	.word   0
	.quad   0                    /* Image load offset from start of RAM */
	.quad   64000         		 /* Effective size of kernel image, little-endian */
    .quad   0			         /* Informative flags, little-endian */
    .quad   0                    /* reserved */
    .quad   0                    /* reserved */
    .quad   0                    /* reserved */
    .word   0x644d5241           /* Magic number, "ARM\x64" */
    .word   0	

actual_start:
	mrs	x26, mpidr_el1		
	and	x26, x26,#0xFF		// Check processor id
	cbz	x26, master		// Hang for all non-primary CPU
	b	proc_hang

proc_hang: 
	b 	proc_hang

master:
	adr	x26, bss_begin
	adr	x25, bss_end
	sub	x25, x25, x26
	bl 	memzero //try to remove this function, might cause problem with x0

	mov	sp, #LOW_MEMORY 
	bl	kernel_main
	b 	proc_hang		// should never come here
