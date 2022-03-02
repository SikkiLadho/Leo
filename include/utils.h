#ifndef	_BOOT_H
#define	_BOOT_H

extern void delay ( unsigned long);
extern void put32 ( unsigned long, unsigned int );
extern unsigned int get32 ( unsigned long );
<<<<<<< HEAD
extern void jump(const void * dt_address);
=======
extern void jump(const void *dt_address);
>>>>>>> 701aa7d0566bfc657d9967f66ea66325ddcd8022
extern int get_el ( void );

#endif  /*_BOOT_H */
