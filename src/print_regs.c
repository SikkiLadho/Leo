#include "printf.h"
#include "regs.h"
void print_registers(){

    
    printf("x6 -> %d \n",read_reg(x6));
    printf("x7 -> %d \n",read_reg(x7));
    printf("x8 -> %d \n",read_reg(x8));
    printf("x9 -> %d \n",read_reg(x9));
    printf("x10 -> %d \n",read_reg(x10));
    printf("x11 -> %d \n",read_reg(x11));

}