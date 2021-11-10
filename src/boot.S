#include "mm.h"
.section ".text.boot"

.globl _start
_start:

	b actual_start
	
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
	mrs	x4, mpidr_el1		
	and	x4, x4,#0xFF		// Check processor id
	cbz	x4, master		// Hang for all non-primary CPU
	b	proc_hang

proc_hang: 
	b 	proc_hang

master:
	adr	x4, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x4
	bl 	memzero //try to remove this function, might cause problem with x0

	mov	sp, #LOW_MEMORY 
	bl	kernel_main
	b 	proc_hang		// should never come here
