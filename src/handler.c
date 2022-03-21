#include "handler.h"


extern void get_next_pc(void){
    long int esr = read_msr(esr_el2);
    uint64_t next_pc = GET_NEXT_PC_INC(esr) + read_msr(elr_el2);
    write_msr(elr_el2,next_pc);
    return ;
}

extern struct regs *get_struct(void)
{
	return (struct regs *)read_msr(tpidr_el2);
}


void arch_regs_set_retval(struct regs *r, struct smc_arg_regs v)
{
	r->r[0] = v.func;
	r->r[1] = v.arg1;
	r->r[2] = v.arg2;
	r->r[3] = v.arg3;
	r->r[4] = v.arg4;
	r->r[5] = v.arg5;
	r->r[6] = v.arg6;
	r->r[7] = v.arg7;
}


static struct smc_arg_regs smc_internal(uint32_t func, uint64_t arg0,
				     uint64_t arg1, uint64_t arg2,
				     uint64_t arg3, uint64_t arg4,
				     uint64_t arg5, uint64_t arg6)
{
	register uint64_t r0 __asm__("x0") = func;
	register uint64_t r1 __asm__("x1") = arg0;
	register uint64_t r2 __asm__("x2") = arg1;
	register uint64_t r3 __asm__("x3") = arg2;
	register uint64_t r4 __asm__("x4") = arg3;
	register uint64_t r5 __asm__("x5") = arg4;
	register uint64_t r6 __asm__("x6") = arg5;
	register uint64_t r7 __asm__("x7") = arg6;

	__asm__ volatile(
		"smc #0"
		: /* Output registers, also used as inputs ('+' constraint). */
		"+r"(r0), "+r"(r1), "+r"(r2), "+r"(r3), "+r"(r4), "+r"(r5),
		"+r"(r6), "+r"(r7));

	return (struct smc_arg_regs){.func = r0,
				  .arg1 = r1,
				  .arg2 = r2,
				  .arg3 = r3,
				  .arg4 = r4,
				  .arg5 = r5,
				  .arg6 = r6,
				  .arg7 = r7};
}


struct smc_arg_regs smc_forward(uint32_t func, uint64_t arg0, uint64_t arg1,
			     uint64_t arg2, uint64_t arg3, uint64_t arg4,
			     uint64_t arg5, uint32_t caller_id)
{
	return smc_internal(func, arg0, arg1, arg2, arg3, arg4, arg5,
			    caller_id);
}



void smc_handler(struct regs * smc_regs)
{
    uintreg_t arg7 = smc_regs->r[7];
    smc_regs->r[7] =  0 | (arg7 & ~CLIENT_ID_MASK);
    
	struct smc_arg_regs ret = smc_forward(smc_regs->r[0],smc_regs->r[1],smc_regs->r[2],smc_regs->r[3],
                                    smc_regs->r[4],smc_regs->r[5],smc_regs->r[6],smc_regs->r[7]);
    ret.arg7 = arg7;
	arch_regs_set_retval(smc_regs, ret);
	return;
}


void handle_lower_aarch64(uintreg_t x0)
{
    struct regs *regs = get_struct();
    if(x0 == PSCI_CPU_ON_AARCH64)
    {

    }
    else
    {
        uintreg_t smc_pc = regs->pc;
		smc_handler(regs);
       
		/* Skip the SMC instruction. */
		uintreg_t esr = read_msr(esr_el2);
        regs->pc = smc_pc + GET_NEXT_PC_INC(esr);

		return;
    }
}



