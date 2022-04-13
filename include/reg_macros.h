#ifndef _REG_MACROS
#define _REG_MACROS

#include "types.h"


#define GET_ESR_IL(esr) ((esr) & (1 << 25))
#define GET_NEXT_PC_INC(esr) (GET_ESR_IL(esr) ? 4 : 2)
#define str_(s) #s
#define str(s) str_(s)



#define read_adr(name)                                              \
	__extension__({                                             \
		uintreg_t __v;                                      \
		__asm__ volatile("adr %0, " str(name) : "=r"(__v)); \
		__v;                                                \
	})


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