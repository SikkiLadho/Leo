#include "exception_macros.S" //lower_sync_exception

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
	lower_sync_exception //defined in src/exception_macros.S

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

