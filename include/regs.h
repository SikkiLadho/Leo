#ifndef _LEO_REGS_H
#define _LEO_REGS_H

#include <stddef.h>
typedef unsigned long int __uint64_t;
typedef __uint64_t uint64_t;
typedef uint64_t uintreg_t;

#define str_(s) #s
#define str(s) str_(s)




#define read_msr(name)                                              \
	__extension__({                                             \
		uintreg_t __v;                                      \
		__asm__ volatile("mrs %0, " str(name) : "=r"(__v)); \
		__v;                                                \
	})


#define write_msr(name, value)                                \
	__extension__({                                       \
		__asm__ volatile("msr " str(name) ", %x0"     \
				 :                            \
				 : "rZ"((uintreg_t)(value))); \
	})


#define read_reg(name)                                              \
	__extension__({                                             \
		uintreg_t __v;                                      \
		__asm__ volatile("mov %0, " str(name) : "=r"(__v)); \
		__v;                                                \
	})


#define write_reg(name, value)                                \
	__extension__({                                       \
		__asm__ volatile("mov " str(name) ", %x0"     \
				 :                            \
				 : "rZ"((uintreg_t)(value))); \
	})




#endif