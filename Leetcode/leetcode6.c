// Interger to Roman
#define  LOCAL
#include <stdio.h>

int main()
{ 
    /* 文件重定向 */
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int a, b;
    int scanf_count = scanf("%d, %d", &a, &b);
    printf("%d\n", scanf_count);
    return 0;
}