/* 素数判定 */
#include <stdio.h>
#include <string.h>
#include <math.h>

int is_prime(int n);

int main()
{
    int n;
    scanf("%d", &n);
    if(is_prime(n))
    {
        printf("%d is a prime", n);
    }
    else
    {
        printf("%d is not a prime", n);
    }
    return 0;
}

int is_prime(int n)
{
    if(n < 1) return 0;
    int m = round(sqrt(n));
    for(int i = 1; i < m; i++)
    {
        if(n % i == 0) return 0;
    }
    return 1;
}
