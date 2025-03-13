#include <stdio.h>
void *my_memset(void *s, int c, size_t n);
int main ()
{
    char a[9];
    my_memset((void *)a, 1, sizeof(a));
    for (size_t i = 0; i < sizeof(a) / sizeof(char); i++)
    {
        printf("a[%d] = %d\n", (int)i, (int)a[i]);
    }
    return 0;
}
