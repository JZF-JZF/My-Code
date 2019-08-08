#include"pch.h"
#if 0
void SISort(vector<int>&vec)
{
	int i, j;		//循环变量
	int temp;		//临时量
	for (i = 1; i < vec.size(); ++i)	//每轮循环插入一个数vec[i]
	{
		j = i;
		temp = vec[i];	//临时量存放待插入的数据 后边数字后移会覆盖掉vec[i]的位置
		//j必须大于0 不能一直减 最多只能减到1 也就是待插入的数字是目前最小的数 插入到第一位最小的位置
		while (j > 0 && temp< vec[j - 1])	
		{
			//循环找到第一个数字小于待插入的数字，该位置就是插入位置
			vec[j] = vec[j - 1];
			j--;
		}
		//将temp临时量插进去
		vec[j] = temp;
	}
}

int main()
{
	vector<int>vec;

	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(rand() % 100);
	}
	cout << "排序前：";
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;
	SISort(vec);
	cout << "排序后：";
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;
	return 0;
}
#endif