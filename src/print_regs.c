#include "printf.h"
#include "regs.h"
void print_registers(){

    
    printf("x6 -> %d \r\n",read_reg(x6));
    printf("x7 -> %d \r\n",read_reg(x7));
    printf("x8 -> %d \r\n",read_reg(x8));
    printf("x9 -> %d \r\n",read_reg(x9));
    printf("x10 -> %d \r\n",read_reg(x10));
    printf("x11 -> %d \r\n",read_reg(x11));

}