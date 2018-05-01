// Roman To Int
// 将罗马数字转为整数

#include <string>
#include <iostream>
#include <string.h>

using namespace std;

int RomanToInt(string s);

int main()
{
    char charc[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    int values[] = {1, 5, 10, 50, 100, 500, 1000};
    string romanstr;
    cin >> romanstr;
    // 从第二个字符开始比较，判断该字符比左边的字符代表的数字大还是小，大的话，减去，小的话，加上
    int index = 0;
    int sum = 0;
    while(index < strlen(romanstr.c_str()))
    {
        // 自动变量
        char tmp = romanstr[index - 1];
        int tmp_a, tmp_b;
        for(int i = 0; i < sizeof(charc); i++)
        {
            if(romanstr[index] == charc[i])
            {
                tmp_a = values[i];
            }
            if(romanstr[index + 1] == charc[i])
            {
                tmp_b = values[i];
            }
        }
        if(index == strlen(romanstr.c_str()) - 1)
        {
            sum += tmp_a;
            break;
        }
        if(tmp_a < tmp_b)
        {
            sum += tmp_b - tmp_a;
            index += 2;
        }
        else
        {
            sum += tmp_a;
            index++;
        }
        
    }
    cout << sum << endl;
    return 0;
} 