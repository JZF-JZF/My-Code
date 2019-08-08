#include"pch.h"

#if 0
int Partition(vector<int>&vec, int low, int high)
{
	//三数取中 得到枢纽
	int pivotkey;
	int m = low + (high - low) / 2;	//计算数组中间元素下标
	if (vec[low] > vec[high])	//high大
		swap(low, high);
	if (vec[m] > vec[high])		//high最大
		swap(m, high);
	if (vec[m] > vec[low])		//第二大即中间大
		swap(m, low);	//此时vec[low]已经为整个序列左中右三个关键字的中间值了

	pivotkey = vec[low];	//将中间值赋给枢纽
	
	int temp = pivotkey;
	while (low < high)	//只要high大于low即low和high的位置还没有重合或交换
	{
		//如果高位的数大于枢纽值则不做改变，高位下标往下减
		//否则小于的话将枢纽值和高位的小的数做交换
		while (low<high&&vec[high]>pivotkey)	
		{
			high--;
		}
		//swap(vec[low], vec[high]);
		vec[low] = vec[high];	//替换而不知交换
		//同理，如果低位的数小于枢纽值则不做改变，低位下标往上加
		//否则大于的话讲枢纽值和低位的大的数交换
		while (low < high&&vec[low] < pivotkey)	
		{
			low++;
		}
		//swap(vec[high], vec[low]);		
		vec[high] = vec[low];	//替换而不知交换
		//一直到某个时刻低位不小于高位，则说明已经交换完了
		//枢纽值的左边全部小于枢纽值，枢纽值的右边全部大于枢纽值
	}
	vec[low] = temp;
	return low;	//返回此时枢纽值的位置下标
}

void QuickSort(vector<int>&vec,int low,int high)
{
	int pivot;	//枢纽位置
	if (low < high)
	{
		pivot = Partition(vec, low, high);	//找到枢纽位置
		QuickSort(vec, low, pivot - 1);		//递归小于枢纽值的部分
		low = pivot + 1;
		//QuickSort(vec, pivot + 1, high);	//递归大于枢纽值的部分
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
	QuickSort(vec,0,vec.size()-1);
	cout << "排序后：";
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;
	return 0;
}

#endif