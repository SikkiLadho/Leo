#include "handler.h" 

uintreg_t default_cpu1_entry = 0;
uintreg_t default_cpu2_entry = 0;
uintreg_t default_cpu3_entry = 0;
void print_regs(struct regs *regs)
{
	printf("---------- Leo Hypervisor SMC Debug Info Start ---------- \r\n");
	printf("print_regs called:\r\n");
	printf("X0-X18:\r\n");
	for(int i=0;i<=29;i++)
	{
		printf("X%d:%x\r\n", i, regs->r[i]);
	}	
	printf("---------- Leo Hypervisor SMC Debug Info End ---------- \r\n");
}


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


// static struct smc_arg_regs smc_internal(uint32_t func, uint64_t arg0,
// 				     uint64_t arg1, uint64_t arg2,
// 				     uint64_t arg3, uint64_t arg4,
// 				     uint64_t arg5, uint64_t arg6)
// {
// }


struct smc_arg_regs smc_forward(uint32_t func, uint64_t arg0, uint64_t arg1,
			     uint64_t arg2, uint64_t arg3, uint64_t arg4,
			     uint64_t arg5, uint32_t caller_id)
{
	register uint64_t r0 __asm__("x0") = func;
	register uint64_t r1 __asm__("x1") = arg0;
	register uint64_t r2 __asm__("x2") = arg1;
	register uint64_t r3 __asm__("x3") = arg2;
	register uint64_t r4 __asm__("x4") = arg3;
	register uint64_t r5 __asm__("x5") = arg4;
	register uint64_t r6 __asm__("x6") = arg5;
	register uint64_t r7 __asm__("x7") = caller_id;

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




void cpu_setup_1(void)
{
	printf("LEO: Bringing up CPU 1\r\n");
	struct regs *regs = get_struct();
	regs->pc = default_cpu1_entry;
	return;

}


void cpu_setup_2(void)
{
	printf("LEO: Bringing up CPU 2\r\n");
	struct regs *regs = get_struct();
	regs->pc = default_cpu2_entry;
	return;
}



void cpu_setup_3(void)
{
	printf("LEO: Bringing up CPU 3\r\n");
	struct regs *regs = get_struct();
	regs->pc = default_cpu3_entry;
	return;
}




void handle_lower_aarch64( uint64_t cpu_entry_1, uint64_t cpu_entry_2,  uint64_t cpu_entry_3)
{
		struct regs *regs = get_struct();
        uintreg_t smc_pc = regs->pc;
		uintreg_t esr = read_msr(esr_el2);
		//printf("Nomral SMC ID:%lx\r\n",regs->r[0]);
		//change entrypoint address if smc is PSCI_CPU_ON_AARCH64

		if(regs->r[0]== PSCI_DEBUG_LEO){

				printf("EL2: Trapped the SMC with ID:%lx\r\n", regs->r[0]);
				printf("EL2: X1:%lx\r\n",regs->r[1]);
				printf("EL2: X2:%lx\r\n",regs->r[2]);
				printf("EL2: X3:%lx\r\n",regs->r[3]);
				printf("EL2: X4:%lx\r\n",regs->r[4]);
				printf("EL2: Forwarding SMC to EL3(Trusted Firmware-A).\r\n");

				smc_handler(regs);

				/* Skip the SMC instruction. */
        		regs->pc = smc_pc + GET_NEXT_PC_INC(esr);
				
				printf("EL2: SMC returned from El3(Trusted Firmware-A).\r\n");
				printf("EL2: X0:%lx\r\n",regs->r[0]);
				printf("EL2: X1:%lx\r\n",regs->r[1]);
				printf("EL2: X2:%lx\r\n",regs->r[2]);
				printf("EL2: X3:%lx\r\n",regs->r[3]);
				printf("EL2: X4:%lx\r\n",regs->r[4]);
				printf("EL2: Returning to EL1(Linux Kernel).\r\n");

				return;

			
		}

		 if(regs->r[0] == PSCI_CPU_ON_AARCH64)
		  {
		printf("**********************************************8\r\n");
		printf("PSCI_ON SMC ID:%lx\r\n",regs->r[0]);

		printf("**********************************************8\r\n");
			switch(regs->r[1])
			{
				//if the smc call is to wake CPU1
				case 1:
				{
					//store the original entrypoint address in a global variable
					default_cpu1_entry = regs->r[2];

					//set the entrypoint to cpu_entry_1 defined in src/cpu_entrypoints.S
					regs->r[2] = cpu_entry_1;
					break;
				}
				case 2:
				{
					default_cpu2_entry = regs->r[2];
					regs->r[2] = cpu_entry_2;
					break;
				}
				case 3:
				{
					default_cpu3_entry = regs->r[2];
					regs->r[2] = cpu_entry_3;
					break;
				}
			}		
		  }
		
		 smc_handler(regs);
		
		/* Skip the SMC instruction. */
        regs->pc = smc_pc + GET_NEXT_PC_INC(esr);

		return;
}



