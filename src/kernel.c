#include "mini_uart.h"
#include "utils.h"
void kernel_main(void)
{
	uart_init();
	uart_send_string("Hello, world Hi!\r\n");


	jump();
}
