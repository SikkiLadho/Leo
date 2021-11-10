#include "mm.h"
.section ".text.boot"

.globl _start
_start:

	b actual_start
/**	Adding the kernel header to make the rpi firmware
	believe that this the linux and thus make the suitable 
	conditions as defined in linux kernel Documentation/arm64/booting.rst
**/
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
	and	x4, x4,#0xFF		// Check processor id
	cbz	x4, master		// Hang for all non-primary CPU
	mrs	x4, mpidr_el1		
	b	proc_hang

proc_hang: 
	b 	proc_hang

master:
	adr	x4, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x4
	bl 	memzero 

	mov	sp, #LOW_MEMORY 
	bl	kernel_main
	b 	proc_hang		// should never come here
