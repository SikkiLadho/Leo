#ifndef _G_LIB_C
#define _G_LIB_C

#include <stddef.h>
#include <stdint.h>
size_t strlen(const char *str);
void * memmove(void *dest, const void *src, unsigned int n);
void * memcpy(void* dst, const void* src, unsigned int cnt);
void * memset(void *s, int c,  unsigned int len);
int memcmp(const void* s1, const void* s2,size_t n);
void * memchr(const void *s, int c, unsigned n);
char *strchr(const char *s, int c);

#endif