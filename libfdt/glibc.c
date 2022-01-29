#include "glibc.h"

size_t strlen(const char *str)
{
        const char *s;
        for (s = str; *s; ++s);
        return (s - str);
}

void *memmove(void *dest, const void *src, unsigned int n)
{
   // unsigned char isCopyRequire = 0;  //flag bit
    char *pcSource =(char *)src;
    char *pcDstn =(char *)dest;
    // return if pcDstn and pcSource is NULL
    if ((pcSource == NULL) &&(pcDstn == NULL))
    {
        return NULL;
    }
    // overlap buffer
    if((pcSource < pcDstn) && (pcDstn < pcSource + n))
    {
        for (pcDstn += n, pcSource += n; n--;)
        {
            *--pcDstn = *--pcSource;
        }
    }
    else
    {
        while(n--)
        {
            *pcDstn++ = *pcSource++;
        }
    }
    return dest;
}

void * memcpy(void* dst, const void* src, unsigned int cnt)
{
    char *pszDest = (char *)dst;
    const char *pszSource =( const char*)src;
    if((pszDest!= NULL) && (pszSource!= NULL))
    {
        while(cnt) //till cnt
        {
            //Copy byte by byte
            *(pszDest++)= *(pszSource++);
            --cnt;
        }
    }
    return dst;
}


void * memset(void *s, int c,  unsigned int len)
{
    unsigned char* p=s;
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}


int memcmp(const void* s1, const void* s2,size_t n)
{
    const unsigned char *p1 = s1, *p2 = s2;
    while(n--)
        if( *p1 != *p2 )
            return *p1 - *p2;
        else
            p1++,p2++;
    return 0;
}

void * memchr(const void *s, int c, unsigned n)
{
    unsigned char *p = (unsigned char*)s;
    unsigned char *isCharFind = NULL;
    while((s!= NULL) && (n--))
    {
        if( *p != (unsigned char)c )
        {
            p++;
        }
        else
        {
            isCharFind = p;
            break;
        }
    }
    return isCharFind;
}


char *strchr(const char *s, int c)
{
    while (*s != (char)c)
        if (!*s++)
            return 0;
    return (char *)s;
}