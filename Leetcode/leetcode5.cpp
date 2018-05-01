// 找到能盛放最多水的容器
/* 本文介绍遍历c++ vector的n种方法 */
/* 
  方法1：
    int count = verctor_a.size();
    for(int i = 0; i < count; i++)
    {
        cout << vector_a[i] << endl;
    }
  方法2:
    int count = vector_a.size();
    for(int i = 0; i < count; i++)
    {
        cout << vector_a.at(i) << endl;
    }
  方法3：
    iter = vector<int>::const_iterator = vector_A.begin();
    for(iter = vector_a.begin(); iter != vector_a.end(); iter++)
    {
        cout << (*iter) << endl;
    }
*/

/* 解题思路
Start by evaluating the widest container, using the first and the last line. 
All other possible containers are less wide, so to hold more water, they need to be higher. 
Thus, after evaluating that widest container, skip lines at both ends that don’t support a higher height. 
Then evaluate that new container we arrived at. Repeat until there are no more possible containers left.
*/

#include <string.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;
int maxArea(vector<int> &height);
int maxArea(int*height, int size);

int main()
{
    vector<int> a;
    int height[] = {2, 1};
    int res = maxArea(height, 2);
    cout << "res : " << res << endl;
    return 0;
}

/* 第一种方法 ： 双重循环以超时告终 */
/* 第二种方法： 双重循环，一层从前往后，一层从后往前, 也是以超时告终 */
/* 第三种方法： 首先选择宽度最大的，作为基准，为了找到最大容量的容器，高度必须大于现在的高度。可以去掉部分数据 */
int maxArea(vector<int> &height)
{
    int maxcontain = -1;
    int i = 0, j = height.size() - 1;
    while(i < j)
    {
        int h = min(height[i], height[j]);
        maxcontain = max(maxcontain, h * (j - i));
        while(height[i] <= h && i < j) i++;
        while(height[j] <= h && i < j) j--;   
    }
    return maxcontain;
}

int maxArea(int *height, int heightSize)
{
    int maxcohntain = -1;
    int *i = height, *j = i + heightSize -1;
    while(i < j)
    {
        int h = (*i) < (*j) ? (*i) : (*j);
        maxcohntain = maxcohntain > (j - i) * h ? maxcohntain : (j - i) * h;
        while((*i) <= h && i < j) i++;
        while((*j) <= h && i < j) j--;
    }
    return maxcohntain;
}