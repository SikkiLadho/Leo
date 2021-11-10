#ifndef	_BOOT_H
#define	_BOOT_H

extern void delay ( unsigned long);
extern void put32 ( unsigned long, unsigned int );
extern unsigned int get32 ( unsigned long );
extern void arm64_elX_to_el1(unsigned long dt_address);
#endif  /*_BOOT_H */
