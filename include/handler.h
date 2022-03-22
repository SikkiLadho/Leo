#ifndef _HANDLER_H
#define _HANDLER_H

#include "printf.h"
#include "types.h"
#include "reg_macros.h"
# define   U(_x)	(_x)
#define PSCI_CPU_ON_AARCH64		U(0xc4000003)

/**
 * The Client ID field within X7 for an SMC64 call.
 */
#define CLIENT_ID_MASK UINT64_C(0xffff)


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
static struct smc_arg_regs smc_internal(uint32_t func, uint64_t arg0,
				     uint64_t arg1, uint64_t arg2,
				     uint64_t arg3, uint64_t arg4,
				     uint64_t arg5, uint64_t arg6);

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
extern void handle_lower_aarch64();


#endif