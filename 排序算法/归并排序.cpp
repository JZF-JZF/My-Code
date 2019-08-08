#include"pch.h"

#if 0

void Merge(int sourceArr[], int tempArr[], int startIndex, int midIndex, int endIndex)
{
	int i = startIndex, j = midIndex + 1, k = startIndex;
	//从中间分开 i++一直到midindex，j++一直到到endindex
	while (i != midIndex + 1 && j != endIndex + 1)
	{
		//分别比较两组数据对应位置的数字的大小，找出小的数字，放入辅助数组
		if (sourceArr[i] > sourceArr[j])
			tempArr[k++] = sourceArr[j++];
		else
			tempArr[k++] = sourceArr[i++];
	}
	//当把其中一个数组的数全部放入辅助数组后将剩余下的另外一个数组中的元素全部依次放入辅助数组
	while (i != midIndex + 1)	//判断是哪个部分还剩余数字
		tempArr[k++] = sourceArr[i++];
	while (j != endIndex + 1)
		tempArr[k++] = sourceArr[j++];
	//将辅助数组中的元素全部导入原数组中
	for (i = startIndex; i <= endIndex; i++)
		sourceArr[i] = tempArr[i];
}

//内部使用递归
void MergeSort(int sourceArr[], int tempArr[], int startIndex, int endIndex)
{
	int midIndex;
	if (startIndex < endIndex)	//分割到剩两个元素或者一个元素则再也不可分割，分组完成
	{
		//找到中间位置进行分治
		midIndex = startIndex + (endIndex - startIndex) / 2;	//避免溢出int
		//分别对分割开的部分进行递归分割
		MergeSort(sourceArr, tempArr, startIndex, midIndex);
		MergeSort(sourceArr, tempArr, midIndex + 1, endIndex);
		//将分割开的数组进行合并
		Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
	}
}

int main()
{
	int a[8] = { 50, 10, 20, 30, 70, 40, 80, 60 };
	int i, b[8];
	MergeSort(a, b, 0, 7);
	for (i = 0; i < 8; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}

#endif