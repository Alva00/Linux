/* 环形序列 */
#include <stdio.h>
#include <string.h>
#define maxn 105

int main()
{
    char s[maxn];
    scanf("%s", s);
    int slen = strlen(s);
    for(int i = 0; i < slen; i++)
    {
        for(int j = 0; j < slen; j++)
        {
            printf("%c", s[(i + j) % slen]);
        }
        printf("\n");
    } 
    return 0;
}