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
  mrs x4, CurrentEL

    cmp x4, #(0b01 << 2)
    bne .notEL1
    /* Already in EL1 */
    ret 

.notEL1:
    cmp x4, #(0b10 << 2)
    beq .inEL2


    /* set EL2 to 64bit */
    mrs x4, scr_el3
    orr x4, x4, #(1<<10)
    msr scr_el3, x4


	mov x4, #0x400000
    msr elr_el3, x4

    mov x4, #((0b1111 << 6) | (0b0101)) /* EL1h runlevel */
    msr spsr_el3, x4
    b   .confEL1

.inEL2:
    mov x4, #0x400000
	msr elr_el2, x4
    mov x4, #((0b1111 << 6) | (0b0101)) /* EL1h runlevel */
    msr spsr_el2, x4



.confEL1:
    /* disable EL2 coprocessor traps */
    mov x5, #0x33ff
    msr cptr_el2, x5

    /* set EL1 to 64bit */
    mov x5, #(1<<31)
    msr hcr_el2, x5

    /* disable EL1 FPU traps */
    mov x5, #(0b11<<20)
    msr cpacr_el1, x5

    /* set up the EL1 bounce interrupt */
    mov x5, sp
    msr sp_el1, x5
    
    isb
    eret


.Ltarget:
    ret
