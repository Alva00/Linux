// 三整数排序
// 只用if语句就可以实现，两两之间穷举出三种排列方式

#include <stdio.h>
#include <iostream>

using namespace std;

void swap(int &a, int &b);

int main()
{
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	if(a > b)
	{
		swap(a, b);
	}
	if(a > c)
	{
		swap(a, c);
	}
	if(b > c)
	{
		swap(b, c);
	}
	printf("sorted %d, %d, %d\n", a, b, c);
	return 0;
}

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}