#include"pch.h"

#if 0
void SSSort(vector<int>&vec)
{
	int i, j, min;
	for (i = 0; i < vec.size()-2; i++)
	{
		min = i;	//将当前下标定义为最小值下标
		for (j = i + 1; j <= vec.size()-1; j++)		//循环i之后的数据 
		{
			if (vec[min] > vec[j])		//如果有小于当前最小值的关键字
				min = j;				//将此关键字的下标赋值给min
		}

		if (i != min)					//若min不等于i,说明找到最小值，交换vec[i]与vec[min]的值
		{
			swap(vec[i], vec[min]);		//交换vec[i]与vec[min]的值
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
	SSSort(vec);
	cout << "排序后：";
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;
	return 0;
}

#endif