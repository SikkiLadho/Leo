#include "mini_uart.h"

void kernel_main(void)
{
	uart_init();
	uart_send_string("Hello, world!\r\n");

	asm("movz x2, #0xF");
	asm("msr spsr_el2, x2");	
	int val = 0x80000;
	asm ("mov X2, %0":"=r"(val));
	asm("msr elr_el2, x2");
	asm("eret");

}
