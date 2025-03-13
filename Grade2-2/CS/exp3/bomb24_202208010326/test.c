#include <stdio.h>
int func4 (int n, int sum)
{
   if (n == 0)
     return 0;
  else if (n == 1)
    return sum;
  else
    return func4(n - 1, sum) + func4(n - 2, sum) + sum;
} 
int main()
{
   int n, x;
   scanf ("%d %d", &n, &x);
   int re = func4(n, x);
   printf("%d\n", re);
   return 0;
}
