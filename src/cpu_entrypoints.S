#include "mm.h" //#LOW_MEMORY
#include "exception_macros.S" //save_registers, restore_registers, eret_with_sb

/* 
    All CPUs have separate entrypoints to avoid race conditions.
    Init stack with each core its own section.
    First core starts at #LOW_MEMORY and other core at #LOW_MEMORY + (core_id * #SECTION_SIZE).
*/


.globl cpu_entry_point_1
cpu_entry_point_1:
    mrs x0, mpidr_el1 
    and x0, x0, #0xFF
    mov x1, #LOW_MEMORY
    mov x2, #SECTION_SIZE
    mul x2, x2, x0
    mov sp, x2


    save_registers
    bl cpu_setup_1
    restore_registers
    eret_with_sb

.globl cpu_entry_point_2
cpu_entry_point_2:
    mrs x0, mpidr_el1
    and x0, x0, #0xFF
    mov x1, #LOW_MEMORY
    mov x2, #SECTION_SIZE
    mul x2, x2, x0
    mov sp, x2

    save_registers
    bl cpu_setup_1
    restore_registers
    eret_with_sb


.globl cpu_entry_point_3
cpu_entry_point_3:
    mrs x0, mpidr_el1
    and x0, x0, #0xFF
    mov x1, #LOW_MEMORY
    mov x2, #SECTION_SIZE
    mul x2, x2, x0
    mov sp, x2

    save_registers
    bl cpu_setup_2
    restore_registers
    eret_with_sb