#include "mm.h" //#LOW_MEMORY


/* 
    All CPUs have separate entrypoints to avoid race conditions.
*/


/*

All CPUs should point to different and valid memory locations

*/

.globl cpu_entry_point_1
cpu_entry_point_1:
mov    sp, #LOW_MEMORY //initialize stack
bl cpu_entry_confirm_1
b cpu_entry_point_1


.globl cpu_entry_point_2
cpu_entry_point_2:
mov    sp, #LOW_MEMORY
bl cpu_entry_confirm_2
b cpu_entry_point_2


.globl cpu_entry_point_3
cpu_entry_point_3:
mov    sp, #LOW_MEMORY
bl cpu_entry_confirm_3
b cpu_entry_point_3

