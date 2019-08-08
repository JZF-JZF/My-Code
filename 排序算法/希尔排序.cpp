#include"pch.h"

#if 0

void HillSort(vector<int>&vec)
{
	for (int gap = vec.size() / 2; gap >= 1; gap = gap / 2)		//增量控制
	{	
		//内部进行直接插入排序，只不过插入排序不是一个挨着一个的插入排序，而是相差gap个元素的插入
		for (int i = gap; i < vec.size(); ++i)	
		{
			for (int j = i-gap; j >= 0 && vec[j] > vec[j + gap]; j -= gap)
			{
				swap(vec[j], vec[j + gap]);
			}
		}
	}
}

/*
//有问题
void HillSort(vector<int>&vec)
{
	int i, j;
	int temp;
	for (int gap = vec.size() / 2; gap >= 1; gap = gap / 2)
	{
		for (i = gap; i < vec.size(); ++i)
		{
			temp = vec[i];
			j = i;
			while (j >= 0 && temp < vec[j - gap])
			{
				vec[j] = vec[j - gap];
				j -= gap;
			}
			vec[j] = temp;
			
		}
	}
}
*/
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
	HillSort(vec);
	cout << "排序后：";
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;
	return 0;
}

#endif