#ifndef _HANDLER_H
#define _HANDLER_H

#include "printf.h" //printf
#include "types.h" 
#include "reg_macros.h"
# define   U(_x)	(_x)
#define PSCI_CPU_ON_AARCH64		U(0xc4000003)
#define PSCI_DEBUG_LEO		U(0xc400000A)

/**
 * The Client ID field within X7 for an SMC64 call.
 */
#define CLIENT_ID_MASK UINT64_C(0xffff)
uintreg_t entry_point_address;


/* prints register values in the struct */
void print_regs(struct regs *r);


extern void cpu_setup_1(void);
extern void cpu_setup_2(void);
extern void cpu_setup_3(void);

/* 

    comments 

*/
/* 

    comments 

*/

struct regs *get_struct(void);

/* 

    comments 

*/
void arch_regs_set_retval(struct regs *r, struct smc_arg_regs v);


/* 

    comments 

*/
struct smc_arg_regs smc_forward(uint32_t func, uint64_t arg0, uint64_t arg1,
			     uint64_t arg2, uint64_t arg3, uint64_t arg4,
			     uint64_t arg5, uint32_t caller_id);

/* 

    comments 

*/
void smc_handler(struct regs * smc_regs);

/* 

    comments 

*/
extern void handle_lower_aarch64( uint64_t cpu_entry_1, uint64_t cpu_entry_2,  uint64_t cpu_entry_3);


#endif