#include "mm.h"
.section ".text.boot"

.globl _start
_start:

	b actual_start

	// kernel image header
	.word   0
	.quad   0			/* Image load offset from start of RAM */
	.quad   64000			/* Effective size of kernel image, little-endian */
	.quad   0			/* Informative flags, little-endian */
	.quad   0			/* reserved */
	.quad   0			/* reserved */
	.quad   0			/* reserved */
	.word   0x644d5241		/* Magic number, "ARM\x64" */
	.word   0	

actual_start:
	mrs x26, mpidr_el1
	// Check processor id
	and x26, x26,#0xFF
	// Hang for all non-primary CPU	
	cbz x26, master
	b proc_hang

proc_hang: 
	b proc_hang

master:
	adr x26, bss_begin
	adr x25, bss_end
	sub x25, x25, x26
	bl memzero 

	mov sp, #LOW_MEMORY 
	bl hyp_main
	// should never come here
	b proc_hang

