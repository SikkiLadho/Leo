
.macro eret_with_sb
	eret
	dsb	nsh
	isb
.endm

.macro save_registers
	/* save registers x0-x30. */
	str x18, [sp, #-16]!
	mrs x18, tpidr_el2
	stp x0, x1, [x18, #8 * 0]
	stp x2, x3, [x18, #8 * 2]
	stp x4, x5, [x18, #8 * 4]
	stp x6, x7, [x18, #8 * 6]
	stp x8, x9, [x18, #8 * 8]
	stp x10, x11, [x18, #8 * 10]
	stp x12, x13, [x18, #8 * 12]
	stp x14, x15, [x18, #8 * 14]
	stp x16, x17, [x18, #8 * 16]
	stp x29, x30, [x18, #8 * 29]
	
	ldr x0, [sp], #16
	str x0, [x18, #8 * 18]

	/*
	 * Save elr_elx, spsr_elx & spsr_el2. This such that we can take nested exception
	 * and still be able to unwind.
	 */

	/* Save return address & mode. */
	mrs x1, elr_el2
	mrs x2, spsr_el2
	stp x1, x2, [x18, #8 * 31]
	mrs x1, hcr_el2
	str x1, [x18, #8 * 33]

.endm


.macro restore_registers
	/* Restore registers x2-x18, x29 & x30. */
	mrs x0, tpidr_el2
	ldp x4, x5, [x0, #8 * 4]
	ldp x6, x7, [x0, #8 * 6]
	ldp x8, x9, [x0, #8 * 8]
	ldp x10, x11, [x0, #8 * 10]
	ldp x12, x13, [x0, #8 * 12]
	ldp x14, x15, [x0, #8 * 14]
	ldp x16, x17, [x0, #8 * 16]
	ldr x18, [x0, #8 * 18]
	ldp x29, x30, [x0, #8 * 29]

	/* Restore return address & mode. */
	ldp x1, x2, [x0, #8 * 31]
	msr elr_el2, x1
	msr spsr_el2, x2

	ldr x1, [x0, 8 * 33]
	msr hcr_el2, x1
	isb

	/* Restore x0..x3, which we have used as scratch before. */
	ldp x2, x3, [x0, #8 * 2]
	ldp x0, x1, [x0, #8 * 0]
	
.endm


.macro lower_sync_exception
	save_registers
	adr x0,cpu_entry_point_1 //entry_points defined in src/cpu_entrpoints.S
	adr x1,cpu_entry_point_2
	adr x2,cpu_entry_point_3
	bl handle_lower_aarch64 //defined in src/handler.c
	restore_registers
	eret_with_sb
.endm


