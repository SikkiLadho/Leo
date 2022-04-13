#ifndef _TYPES_H
#define _TYPES_H


#include <stdint.h>
#include <stddef.h>

//constants
#define NUM_GP_REGS 31




//typedefs
typedef unsigned long int __uint64_t;
typedef __uint64_t uint64_t;
typedef uint64_t uintreg_t;


//globals
extern uintreg_t default_cpu1_entry;
extern uintreg_t default_cpu2_entry;
extern uintreg_t default_cpu3_entry;

//data structures
struct regs {
	/* General purpose registers. */
	uintreg_t r[NUM_GP_REGS];
	uintreg_t pc;
	uintreg_t spsr;
	uintreg_t hcr_el2;
};

//arguments for smc forwarding
struct smc_arg_regs {
	uint64_t func;
	uint64_t arg1;
	uint64_t arg2;
	uint64_t arg3;
	uint64_t arg4;
	uint64_t arg5;
	uint64_t arg6;
	uint64_t arg7;
};


#endif