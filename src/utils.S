#include "mm.h"

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
.globl eret_to_el1
eret_to_el1:  
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



	msr elr_el3, x1

	mov x26, #((0b1111 << 6) | (0b0101)) /* EL1h runlevel */
	msr spsr_el3, x26
	b .confEL1

.inEL2:
	msr elr_el2, x1
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


 
 	/* Configure exception handling. */

 	adr x2, vector_table_el2
	msr vbar_el2, x2
 
	mrs x1, hcr_el2
	orr x1, x1, #(0x1 << 19)	//hcr_el2.TSC=1
	msr hcr_el2, x1

	mov x1, xzr
	mov x2, xzr
	mov x3,xzr
    
    


	isb
	eret


.Ltarget:
	ret



