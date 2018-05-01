// 字符串匹配
// 递归和动态规划两种形式

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <vector>

using namespace std;

bool isMatch(string s, string p);
bool isMatchDP(string s, string p);
bool DPReference(string s, string p);

int main()
{
    string s, p;
    cin >> s;
    cin >> p;
    bool match = isMatchDP(s, p);
    cout << match << endl;
    return 0;
}

// 递归方式 
bool isMatch(string s, string p)
{
    /* s :字符串 */
    /* p :模式 */ 
    if(p.empty()) return s.empty();
    if(p[1] == '*')
    {
        return isMatch(s, p.substr(2)) || !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p);
    }
    else
    { 
        return !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p.substr(1));
    }
}
// 动态规划

bool DPReference(string s, string p)
{
    int m = s.size(), n = p.size();
    vector<vector<bool> > f(m + 1, vector<bool>(n + 1, false));
    
    f[0][0] = true;
    for (int i = 1; i <= m; i++)
        f[i][0] = false;
    // p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
    for (int j = 1; j <= n; j++)
        f[0][j] = j > 1 && '*' == p[j - 1] && f[0][j - 2];
    
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (p[j - 1] != '*')
                f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
            else
                // p[0] cannot be '*' so no need to check "j > 1" here
                f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];
    
    return f[m][n];
}
bool isMatchDP(string s, string p)
{
    int n = s.size();
    int m = p.size();
    // 利用vector创建二维动态数组,括号中分别为行数和列数
    vector<vector<bool> > dp(n + 1, vector<bool> (m + 1, false));  //这句话表示（n+1）*(m+1)的二维数组，所有元素为false
    // s为空且p为空 则为true
    dp[0][0] = true;
    // s不为空且p为空，则输出结果一定为false
    for(int i = 1; i <= n; i++)
    {
        dp[i][0] = false;
    }
    // s为空但p不为空，当且仅当存在*前面的字符出现0次时，并且*前面的字符之前的字符串为空
    for(int j = 1; j <= m; j++)
    {
        dp[0][j] = j > 1 && '*' == p[j - 1] && dp[0][j - 2];
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(p[j - 1] == '*')
            {
                dp[i][j] = dp[i][j - 2] || (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j];
            }
            else
            {
                dp[i][j] =  dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.'); 
            }
        }
    }
    return dp[n][m];
}
