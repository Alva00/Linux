/* Tex中的引号 */
#include <stdio.h>
#include <string.h>


int main()
{
    int q = 1;
    char c;
    /* getchar 从标准输入读取一个字符，类似于fgetc(stdin) */
    // 使用方式：
    //  while((c = fgetc(stdin)) != EOF)
    //  while((c = getchar()) != EOF)
    // 不同操作系统对应的换行符是不一样的，windows系统是\r\n, linux是\n, Macos是\r
    #ifdef xixi
    while((c = getchar()) != EOF)
    {
        if(c == '"')
        {
            printf("%s",q ? "``" : "''");
            q = !q;
        }
        else
        {
            printf("%c", c);
        }
    }
    #else
    while((c = fgetc(stdin)) != EOF)
    {
        if(c == '"')
        {
            printf("%s",q ? "``" : "''");
            q = !q;
        }
        else
        {
            printf("%c", c);
        }   
    }
    #endif
    return 0;
}