#include "printf.h"
 #include "mini_uart.h"
 #include "utils.h"

// register int _X0 __asm("x0");
// register int _X1 __asm("x1");
// register int _X2 __asm("x2");
// register int _X3 __asm("x3");
// register int _X4 __asm("x4");
// register int _X5 __asm("x5");
// register int _X6 __asm("x6");
// register int _X7 __asm("x7");
// register int _X8 __asm("x8");
// register int _X9 __asm("x9");
// register int _X10 __asm("x10");
// register int _X11 __asm("x11");
// register int _X12 __asm("x12");


void kernel_main(const void * dt_address)
{
	if(fdt_check_header(dt_address) == 0)
	{
		printf("DTB is a valid DTB. \n");
	}
	else
	{
		printf("DTB is not a valid DTB. \n");
	}
	uart_init();
	//uart_send_string("Hello\r\n");
	int el = get_el();
	printf("Exception level: %d \r\n", el);

	//printf("X0: %x \r\n", _X0);
	printf("DTB Address: %x \r\n", dt_address);
	

	jump(dt_address);
}


