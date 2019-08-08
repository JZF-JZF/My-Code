#include"pch.h"

#if 0
void adjust(vector<int>&vec, int len, int index)	//调整函数
{
	int left = 2 * index + 1;	//左孩子
	int right = 2 * index + 2;	//右孩子
	int maxidx = index;
	if (left < len && vec[left] > vec[maxidx])	//如果左孩子大于父结点，将左孩子放在父结点
		maxidx = left;
	if (right < len && vec[right] > vec[maxidx])//如果右孩子大于父结点，将右孩子放在根节点
		maxidx = right;
	if (maxidx != index)	//做完如上两步后，如果父结点变了，则说明有孩子大于父结点
	{
		swap(vec[maxidx], vec[index]);	//交换父结点和较大孩子的值
		adjust(vec, len, maxidx);	//递归调整以较大孩子结点为父结点的其他子树
	}
}
void HeapSort(vector<int>&vec)
{
	for (int i = vec.size() / 2 - 1; i >= 0; i--) // 对每一个非叶结点进行堆调整
		adjust(vec, vec.size(), i);
	for (int i = vec.size() - 1; i >= 1; i--)
	{
		swap(vec[0], vec[i]); //将当前最大的位置放到数组末尾
		adjust(vec, i, 0); //将未完成排序的部分继续进行堆排
	}
}
#endif


#if 0
void adjust(vector<int>&vec, int len)
{
	for (int start = len / 2 - 1; start >= 0; start--) //遍历调整每个非叶子节点
	{
		int tmp = vec[start];	//要调整的结点
		int i = 0;
		for (i = 2 * start + 1; i < len; i = 2 * i + 1)//其根与孩子的关系
		{
			if (i + 1 < len && vec[i] < vec[i + 1]) //如果左孩子小于右孩子
				i++;		//i++后 i就是较大的右孩子
			if (vec[i] < tmp) //较大的孩子都小于tmp则不用交换
				break;
			else  if (vec[i] > tmp) //这时较大的孩子大于父结点则将较大的孩子赋给根结点
				vec[start] = vec[i];
			else	//如果较大的孩子的值等于父结点则不做任何操作
				;
			//下一次循环则从start移动到i处 因为父结点数值改变了
			//需要从改变的孩子节点的下标继续循环调整	
			start = i;
		}
		vec[start] = tmp;//循环结束则找到了被调整结点的最终位置，将tmp放到合适的根上
	}
}




void HeapSort(vector<int>&vec)
{
	for (int i = vec.size() / 2 - 1; i >= 0; i--) // 对每一个非叶结点进行堆调整
		adjust(vec, vec.size());
	for (int i = vec.size() - 1; i >= 1; i--)
	{
		swap(vec[0], vec[i]); //将当前最大的位置放到数组末尾
		adjust(vec, i); //将未完成排序的部分继续进行堆排
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
	HeapSort(vec);
	cout << "排序后：";
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;
	return 0;
}

#endif

