#ifndef	_BOOT_H
#define	_BOOT_H

extern void delay ( unsigned long);
extern void put32 ( unsigned long, unsigned int );
extern unsigned int get32 ( unsigned long );
<<<<<<< HEAD
extern void jump(const void * dt_address);
=======
extern void jump(const void *dt_address);
>>>>>>> 44866fb86ddfd4d30093d7948ba0a1d804ea5946
extern int get_el ( void );
#endif  /*_BOOT_H */
