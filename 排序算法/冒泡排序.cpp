// 排序算法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

#if 0
void BubbleSort(vector<int>&vec)
{
	int i, j;
	//int length = vec.size() - 1;
	for (i = 0; i < vec.size(); i++)
	{
		for (j = vec.size() - 2; j >= i; j--)			//注意j是从后往前循环
		{
			if (vec[j] > vec[j + 1])
			{										//若前者大于后者 
				swap(vec[j], vec[j + 1]);			//交换L->r[j]与L->r[j+1]的值
			}
		}
	}
}
#endif

#if 0
//优化版本
void BubbleSort(vector<int>&vec)
{
	int i, j;

	//定义标志位 初始值为true
	bool flag = true;	

	for (i = 0; i < vec.size() && flag; i++)	//若flag为false说明数据已经有序直接退出循环
	{
		//进入外层循环将flag设置为false 如果这轮内层循环没有交换任何值
		//则flag不会改变 依然为false 下一轮就不会进入到循环了，因为数据已经有序了
		flag = false;	

		for (j = vec.size() - 2; j >= i; j--)		//注意j是从后往前循环
		{
			if (vec[j] > vec[j + 1])
			{										//若前者大于后者 
				swap(vec[j], vec[j + 1]);			//交换L->r[j]与L->r[j+1]的值
				//能进行到这一步说明有数据交换，即数据目前不是有序的
				//将flag置为true为了下一次循环能够继续进行
				flag = true;
			}
		}
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
	BubbleSort(vec);
	cout << "排序后：";
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;
	return 0;
}
#endif
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
