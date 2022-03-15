#include "regs.h"

typedef unsigned long int __uint64_t;
typedef __uint64_t uint64_t;
typedef uint64_t uintreg_t;


struct regs
{
    /* data */
    uintreg_t x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15;
    uintreg_t x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30;

}sregs;
void save_regs(){

    //struct regs sregs;
    sregs.x0=read_reg(x0);
    sregs.x1=read_reg(x1);
    sregs.x2=read_reg(x2);
    sregs.x3=read_reg(x3);
    sregs.x4=read_reg(x4);
    sregs.x5=read_reg(x5);
    sregs.x6=read_reg(x6);
    sregs.x7=read_reg(x7);
    sregs.x8=read_reg(x8);
    sregs.x9=read_reg(x9);
    sregs.x10=read_reg(x10);
    sregs.x11=read_reg(x11);
    sregs.x12=read_reg(x12);
    sregs.x13=read_reg(x13);
    sregs.x14=read_reg(x14);
    sregs.x15=read_reg(x15);
    sregs.x16=read_reg(x16);
    sregs.x17=read_reg(x17);
    sregs.x18=read_reg(x18);
    sregs.x19=read_reg(x19);
    sregs.x20=read_reg(x20);
    sregs.x21=read_reg(x21);
    sregs.x22=read_reg(x22);
    sregs.x23=read_reg(x23);
    sregs.x24=read_reg(x24);
    sregs.x25=read_reg(x25);
    sregs.x26=read_reg(x26);
    sregs.x27=read_reg(x27);
    sregs.x28=read_reg(x28);
    sregs.x29=read_reg(x29);
    sregs.x30=read_reg(x30);

}
