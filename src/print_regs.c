#include "printf.h"
#include "reg_macros.h"
void print_registers(void){

    printf("x0 -> %d \r\n",read_reg(x0));
    printf("x1 -> %d \r\n",read_reg(x1));
    printf("x2 -> %d \r\n",read_reg(x2));
    printf("x3 -> %d \r\n",read_reg(x3));
    printf("x4 -> %d \r\n",read_reg(x4));
    printf("x5 -> %d \r\n",read_reg(x5));  
    printf("x6 -> %d \r\n",read_reg(x6));
    printf("x7 -> %d \r\n",read_reg(x7));
    printf("x8 -> %d \r\n",read_reg(x8));
    printf("x9 -> %d \r\n",read_reg(x9));
    printf("x10 -> %d \r\n",read_reg(x10));
    printf("x11 -> %d \r\n",read_reg(x11));
    printf("x12 -> %d \r\n",read_reg(x12));
    printf("x13 -> %d \r\n",read_reg(x13));
    printf("x14 -> %d \r\n",read_reg(x14));
    printf("x15 -> %d \r\n",read_reg(x15));
    printf("x16 -> %d \r\n",read_reg(x16));
    printf("x17 -> %d \r\n",read_reg(x17));
    printf("x18 -> %d \r\n",read_reg(x18));
    printf("x19 -> %d \r\n",read_reg(x19));
    printf("x20 -> %d \r\n",read_reg(x20));
    printf("x21 -> %d \r\n",read_reg(x21));
    printf("x22 -> %d \r\n",read_reg(x22));
    printf("x23 -> %d \r\n",read_reg(x23));
    printf("x24 -> %d \r\n",read_reg(x24));
    printf("x25 -> %d \r\n",read_reg(x25));
    printf("x26 -> %d \r\n",read_reg(x26));
    printf("x27 -> %d \r\n",read_reg(x27));
    printf("x28 -> %d \r\n",read_reg(x28));
    printf("x29 -> %d \r\n",read_reg(x29));
    printf("x30 -> %d \r\n",read_reg(x30));
    printf("SPSR -> %d \r\n",read_msr(spsr_el2));
    printf("ELR -> %d \r\n",read_msr(elr_el2));
    printf("ESR -> %d \r\n",read_msr(esr_el2));
  
}