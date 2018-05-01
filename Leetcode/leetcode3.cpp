// 实现atoi函数
// 处理字符串时可能会发生的情况：前、后有空格， 包含英文字母， 负数的处理, 超出范围返回INF和-INF
// link:https://leetcode.com/problems/string-to-integer-atoi/description/
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

using namespace std;

int StringTOInt(string s);
int MyAtoi(string s);

int main()
{
    string s;
    cin >> s;
    int res = MyAtoi(s);
    cout << res << endl;
    return 0;
}

int MyAtoi(string str)
{
    long result = 0;
    int indicator = 1;
    str. erase(0, str.find_first_not_of(' '));
    for(int i = 0; i < str.size();)
    {
        if(str[i] == '-' || str[i] == '+')
            indicator = (str[i++] == '-')? -1 : 1;
        while('0'<= str[i] && str[i] <= '9') 
        {
            result = result*10 + (str[i++]-'0');
            if(result*indicator >= INT_MAX) return INT_MAX;
            if(result*indicator <= INT_MIN) return INT_MIN;               
        }
        return result*indicator;
    }
}