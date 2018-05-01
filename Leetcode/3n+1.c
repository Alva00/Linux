/* 注意：这题的难点在于，虽然10的9次方并不超出int范围，但是3×n+1会超出范围 */
/* 解决方法是使用long long，并且注意，在输入和输出 long long变量时，需要输出 %lld */
#include <stdio.h>
#include <limits.h>

int main()
{
    printf("%d\n", INT_MAX);
    printf("%d\n", INT_MIN);
    int count = 0;
    long long  n;
    scanf("%lld", &n);
    while(n > 1)
    {
        if(n % 2)
        {
            n = 3 * n + 1;
        }
        else
        {
            n = n / 2;
        }
        count++;
    }
    printf("%d\n", count);
    return 0;
}