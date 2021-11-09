#include "mini_uart.h"
#include "utils.h"
void kernel_main(unsigned long dt_address)
{
	uart_init();
	uart_send_string("Hello, world Hi!\r\n");


	jump(dt_address);
}
