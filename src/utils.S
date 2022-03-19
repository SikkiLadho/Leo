
.macro save_registers
	/* Reserve stack space and save registers x0-x18, x29 & x30. */
	stp x0, x1, [sp, #-(8 * 24)]!
	stp x2, x3, [sp, #8 * 2]
	stp x4, x5, [sp, #8 * 4]
	stp x6, x7, [sp, #8 * 6]
	stp x8, x9, [sp, #8 * 8]
	stp x10, x11, [sp, #8 * 10]
	stp x12, x13, [sp, #8 * 12]
	stp x14, x15, [sp, #8 * 14]
	stp x16, x17, [sp, #8 * 16]
	str x18, [sp, #8 * 18]
	stp x29, x30, [sp, #8 * 20]

	/*
	 * Save elr_elx & spsr_elx. This such that we can take nested exception
	 * and still be able to unwind.
	 */

	mrs x0, elr_el2
	mrs x1, spsr_el2
	stp x0, x1, [sp, #8 * 22]
	mrs x3, esr_el2
	str x3, [sp,#8 * 24]

.endm


.macro restore_registers
	/* Restore registers x2-x18, x29 & x30. */
	ldp x2, x3, [sp, #8 * 2]
	ldp x4, x5, [sp, #8 * 4]
	ldp x6, x7, [sp, #8 * 6]
	ldp x8, x9, [sp, #8 * 8]
	ldp x10, x11, [sp, #8 * 10]
	ldp x12, x13, [sp, #8 * 12]
	ldp x14, x15, [sp, #8 * 14]
	ldp x16, x17, [sp, #8 * 16]
	ldr x18, [sp, #8 * 18]
	ldp x29, x30, [sp, #8 * 20]


	/* Restore registers elr_elx & spsr_elx, using x0 & x1 as scratch. */
	ldp x0, x1, [sp, #8 * 22]
	msr elr_el2, x0
	msr spsr_el2, x1
	ldr x3,[sp,#8 * 24]
	msr esr_el2,x3
	/* Restore x0 & x1, and release stack space. */
	ldp x0, x1, [sp], #8 * 26
.endm



.macro lower_sync_exception
	
	save_registers
	bl print_registers
	restore_registers
	smc 0
	save_registers
	bl print_registers
	restore_registers
	bl get_next_pc
	eret

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



