

#include "mini_uart.h"
.macro save_volatile_to_vcpu
	/*
	 * Save x18 since we're about to clobber it. We subtract 16 instead of
	 * 8 from the stack pointer to keep it 16-byte aligned.
	 */
	str x18, [sp, #-16]!

	/* Get the current vCPU. */
	mrs x18, tpidr_el2
	stp x0, x1, [x18,  8 * 0]
	stp x2, x3, [x18,  8 * 2]
	stp x4, x5, [x18,  8 * 4]
	stp x6, x7, [x18,  8 * 6]
	stp x8, x9, [x18,  8 * 8]
	stp x10, x11, [x18, 8 * 10]
	stp x12, x13, [x18,  8 * 12]
	stp x14, x15, [x18,  8 * 14]
	stp x16, x17, [x18,  8 * 16]
	stp x29, x30, [x18,  8 * 29]

	/* x18 was saved on the stack, so we move it to vCPU regs buffer. */
	ldr x0, [sp], #16
	str x0, [x18,  8 * 18]

	/* Save return address & mode. */
	mrs x1, elr_el2
	mrs x2, spsr_el2
	stp x1, x2, [x18,  8 * 31]
	mrs x1, hcr_el2
	str x1, [x18,  8 * 33]


.endm


.macro lower_sync_exception
	save_volatile_to_vcpu
	
.endm



.globl vector_table_el2
.balign 0x800
vector_table_el2:
sync_cur_sp0:
	b .

.balign 0x80
irq_cur_sp0:
	b .

.balign 0x80
fiq_cur_sp0:
	b .

.balign 0x80
serr_cur_sp0:
	b .

.balign 0x80
sync_cur_spx:
	b .

.balign 0x80
irq_cur_spx:
	b .

.balign 0x80
fiq_cur_spx:
	b .

.balign 0x80
serr_cur_spx:
	b . 

.balign 0x80
sync_lower_64:
	lower_sync_exception

.balign 0x80
irq_lower_64:
	b .

.balign 0x80
fiq_lower_64:
	b .

.balign 0x80
serr_lower_64:
	b .

.balign 0x80
sync_lower_32:
	b .

.balign 0x80
irq_lower_32:
	b .

.balign 0x80
fiq_lower_32:
	b .

.balign 0x80
serr_lower_32:
	b .



.globl get_el
get_el:
	mrs x0, CurrentEL
	lsr x0, x0, #2
	ret
    
.globl put32
put32:
	str w1,[x0]
	ret

.globl get32
get32:
	ldr w0,[x0]
	ret

.globl delay
delay:
	subs x0, x0, #1
	bne delay
	ret




//jumps from any Exception Level to EL1
.globl jump
jump:  
	b arm64_elX_to_el1


arm64_elX_to_el1:
	mrs x26, CurrentEL
    cmp x26, #(0b01 << 2)
    bne .notEL1
    /* Already in EL1 */
    ret 

.notEL1:
    cmp x26, #(0b10 << 2)
    beq .inEL2


    /* set EL2 to 64bit */
    mrs x26, scr_el3
    orr x26, x26, #(1<<10)
    msr scr_el3, x26



	mov x26, #0x400000
	msr elr_el3, x26

	mov x26, #((0b1111 << 6) | (0b0101)) /* EL1h runlevel */
	msr spsr_el3, x26
	b .confEL1

.inEL2:
	mov x26, #0x400000
	msr elr_el2, x26
	mov x26, #((0b1111 << 6) | (0b0101)) /* EL1h runlevel */
	msr spsr_el2, x26

.confEL1:
	/* disable EL2 coprocessor traps */
	mov x27, #0x33ff
	msr cptr_el2, x27

	/* set EL1 to 64bit */
	mov x27, #(1<<31)
	msr hcr_el2, x27

	/* disable EL1 FPU traps */
	mov x27, #(0b11<<20)
	msr cpacr_el1, x27

	/* set up the EL1 bounce interrupt */
	mov x27, sp
	msr sp_el1, x27



	/* Configure exception handlers. */
	adr x2, vector_table_el2
	msr vbar_el2, x2
	
	mrs x1, hcr_el2
	orr x1, x1, #(0x1 << 19)	
	msr hcr_el2, x1

	mov x1, xzr
	mov x2, xzr
	mov x3,xzr
    
    


	isb
	eret


.Ltarget:
	ret



