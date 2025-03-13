#include <stdlib.h>
void *my_memset(void *s, int c, size_t n)
{
    size_t K = sizeof(unsigned long);
    size_t cnt = 0;
    unsigned char *schar = s;
    
    //开始时直到目的地址是K的倍数时，使用字节级的写
    while ((size_t)schar % K != 0 && cnt < n) {
        *schar++ = (unsigned char) c;
        cnt++;
    }
    
    //使用数据类型为 unsigned long 的字来装下4个（对于IA32)或者8个（对于 x86-64) c,
    unsigned long longc;
    unsigned char* tmp = (unsigned char*)&longc;
    size_t i = 0;
    while (i < K) {
        *tmp++ = (unsigned char)c;
        i++;
    }
    
    //然后进行字级的写
    unsigned long *slong = (unsigned long*)schar;
    while (cnt + K < n) {
        *slong++ = longc;
        cnt += K;
    }
    
    //最后未成字部分采用用字节级的写
    while (cnt < n) {
        *schar++ = (unsigned char) c;
        cnt++;
    }
    
    return s;
}
