#include"stdafx.h"


//八皇后问题
#if 0
//八皇后问题
const int N = 8;
int ar[] = { 1,2,3,4,5,6,7,8 }; // 数组的index，代表行数
int mycount = 0;

void swap(int i, int j)
{
	int tmp = ar[i];
	ar[i] = ar[j];
	ar[j] = tmp;
}
bool line(int i) // i表示行数
{
	for (int j = 0; j < i; ++j)
	{
		if (i - j == abs(ar[i] - ar[j]))
		{
			return false;
		}
	}
	return true;
}
void func(int i)
{
	if (i == N)
	{
		mycount++;
		for (int k = 0; k < N; ++k)
		{
			cout << ar[k] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int j = i; j < N; ++j)
		{
			swap(i, j);
			if (line(i)) // i表示当前处理的是数组的哪一个位置的元素，i代表行数
			{
				func(i + 1);
			}
			swap(i, j);
		}
	}
}
int main()
{
	func(0);
	cout << mycount << endl;
	return 0;
}

//八皇后示例
/*
static int gEightQueen[8] = { 0 }, gCount = 0;
void print()//输出每一种情况下棋盘中皇后的摆放情况
{
	for (int i = 0; i < 8; i++)
	{
		int inner;
		for (inner = 0; inner < gEightQueen[i]; inner++)
			cout << "0 ";
		cout << "# ";
		for (inner = gEightQueen[i] + 1; inner < 8; inner++)
			cout << "0 ";
		cout << endl;
	}
	cout << "==========================\n";
}
int check_pos_valid(int loop, int value)//检查是否存在有多个皇后在同一行/列/对角线的情况
{
	int index;
	int data;
	for (index = 0; index < loop; index++)
	{
		data = gEightQueen[index];
		if (value == data)
			return 0;
		if ((index + data) == (loop + value))
			return 0;
		if ((index - data) == (loop - value))
			return 0;
	}
	return 1;
}
void eight_queen(int index)
{
	int loop;
	for (loop = 0; loop < 8; loop++)
	{
		if (check_pos_valid(index, loop))
		{
			gEightQueen[index] = loop;
			if (7 == index)
			{
				gCount++, print();
				gEightQueen[index] = 0;
				return;
			}
			eight_queen(index + 1);
			gEightQueen[index] = 0;
		}
	}
}
int main(int argc, char*argv[])
{
	eight_queen(0);
	cout << "total=" << gCount << endl;
	return 0;
}
*/

#endif

//排列树
#if 0
//排列树
//排列树的时间复杂度为O(n!) 4x3x2x1; 
int ar[] = { 1,2,3 };
const int N = 3;

void swap(int i, int j)
{
	int tmp = ar[i];
	ar[i] = ar[j];
	ar[j] = tmp;
}

void func(int i)
{
	if (i == N)		//找到叶子节点了
	{
		for (int k = 0; k < N; ++k)
		{
			cout << ar[k] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int j = i; j < N; ++j)
		{
			swap(i, j);
			func(i + 1);
			swap(i, j);
		}
	}
}
int main()
{
	func(0);
	return 0;
}
#endif

//轮船装载问题
#if 0
/*
装载问题：两个轮船的容量分别是c1和c2，怎么装载物品，
能够使物品都装入轮船当中
*/
const int N = 7;
int w[] = { 7,8,5,9,4,6,3 };
int c1 = 22;
int c2 = 20;

int x[N];
int cw;
int bestw;
int bestx[N];
int r;
void func(int i)
{
	if (i == N)
	{
		if (cw > bestw)
		{
			bestw = cw;
			for (int j = 0; j < N; ++j)
			{
				bestx[j] = x[j];
			}
		}
	}
	else
	{
		r -= w[i];
		if (cw + w[i] <= c1) // i节点左子树的剪枝操作
		{
			cw += w[i];
			x[i] = 1;
			func(i + 1);
			cw -= w[i];
		}

		if (cw + r > bestw)  // i节点右子树的剪枝操作
		{
			x[i] = 0;
			func(i + 1);
		}
		r += w[i];
	}
}
int main()
{
	for (int w1 : w)
	{
		r += w1;
	}
	func(0);
	cout << "轮船c1:" << c1 << "装入的物品是:";
	for (int i = 0; i < N; ++i)
	{
		if (bestx[i] == 1)
		{
			cout << w[i] << " ";
		}
	}
	cout << endl;
	cout << "轮船c2:" << c2 << "装入的物品是:";
	for (int i = 0; i < N; ++i)
	{
		if (bestx[i] == 0)
		{
			cout << w[i] << " ";
		}
	}
	cout << endl;
	return 0;
}
#endif

//0 - 1背包问题
#if 0
/*
0-1背包问题
描述：有一组物品，他们的重量和价值分别是
w={w1,w2,w3,w4,w5...}
v={v1,v2,v3,v4,v5...}
现在有一个背包，其容量为c,请问如何装入物品，能够使背包价值最大化？
*/
const int N = 5;
int w[] = { 8,4,9,6,7 };
int v[] = { 7,9,6,12,3 };
int c = 18;

int x[N]; // 辅助数组
int bestx[N]; // 记录最优子集的数组
int cw; // 记录选择的物品的重量
int cv; // 记录选择物品的价值
int r; // 记录节点右子树中剩余能够选择的物品的总价值
int bestv = 0; // 记录选择的物品的最优价值

// 输出最终选择的物品和最大价值
void func(int i)
{
	if (i == N)
	{
		if (cv > bestv)
		{
			bestv = cv;
			for (int j = 0; j < N; ++j)
			{
				bestx[j] = x[j];
			}
		}
	}
	else
	{
		r -= v[i];
		if (cw + w[i] <= c) // i节点左子树的剪枝操作
		{
			cw += w[i];
			cv += v[i];
			x[i] = 1;
			func(i + 1);
			cw -= w[i];
			cv -= v[i];
		}

		if (cv + r > bestv)  // i节点右子树的剪枝操作
		{
			x[i] = 0;
			func(i + 1);
		}
		r += v[i];

		/*if (cw + w[i] <= c)
		{
			cw += w[i];
			cv += v[i];
			x[i] = 1;
			func(i + 1);
			cw -= w[i];
			cv -= v[i];
		}
		x[i] = 0;
		func(i + 1);*/
	}
}
int main()
{
	for (int v1 : v)
	{
		r += v1;
	}
	func(0);
	cout << "best value:" << bestv << endl;
	for (int i = 0; i < N; ++i)
	{
		cout << bestx[i] << " ";
	}
	cout << endl;
	return 0;
}
#endif



//子集树
#if 0
/*
12 3 45 6 78 9 43 22 62 31
有一组整数，请选择一部分整数，使选择的整数的和，和剩下的整数的和的差最小
有一组2n个整数，请选择n个整数，使选择的整数的和，和剩下的整数的和的差最小
*/

int ar[] = { 12,3,45,6,78,9,43,22,62,31 };
const int N = 10;
int x[N]; // 子集树遍历的辅助数组
int bestx[N]; // 记录最优解的子集
int sum; // 记录所选子集数字的和
int r; // 记录未选择的数字的和
int cnt; // 记录选择的子集的个数
unsigned int Min = 0xFFFFFFFF;

int mycount = 0;

void func(int i)
{
	if (i == N)
	{
		mycount++;

		if (cnt != N / 2)
			return;

		int ret = abs(sum - r);
		if (Min > ret)
		{
			Min = ret;
			for (int j = 0; j < N; ++j)
			{
				bestx[j] = x[j];
			}
		}
	}
	else
	{
		if (cnt < N / 2)	//剪枝函数
		{
			r -= ar[i];
			sum += ar[i];
			cnt++;				//if(cnt < N/2)
			x[i] = 1;
			func(i + 1);
			cnt--;
			sum -= ar[i];
			r += ar[i];
			x[i] = 0;
			func(i + 1);
		}
	}
}
int main()
{
	for (int val : ar)
		r += val;
	func(0);

	cout << "min:" << Min << endl;
	for (int i = 0; i < N; ++i)
	{
		if (bestx[i] == 1)
		{
			cout << ar[i] << " ";
		}
	}
	cout << endl;
	cout << "mycount:" << mycount << endl;

	return 0;
}
#endif