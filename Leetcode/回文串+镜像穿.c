/* 如果不包含空白字符，可以使用scanf进行输入 */
// scanf使用方式:
//  while(scanf("%s"), s)
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char* recv = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";

// 非常巧妙！
const char* msg[] = {
    "not a palindrome",
    "a regular palindrome",
    "a mirrored string",
    "a mirrored palindrome"
};

// 从字符数组中找到对应的镜像字符
char reverse(char ch)
{
    if(isalpha(ch))
    {
        return recv[ch - 'A'];
    }
    else
    {
        return recv[ch - '0' + 25];
    }
}
int main()
{
    char s[100];
    int p = 1; // 判断是否是回文串
    int m = 1; // 判断是否是镜像串
    while((scanf("%s", s)) == 1)
    {
        // 注意：此处只能用strlen，而不能用size函数
        int len = strlen(s);
        for(int i = 0; i < (len + 1) / 2; i++)
        {
            if(s[i] != s[len - 1 - i]) p = 0;
            if(s[i] != reverse(s[len - 1 - i])) m = 0;
        }
        printf("%s -- is %s.\n\n", s, msg[2 * m + p]);
    }
    return 0;
}