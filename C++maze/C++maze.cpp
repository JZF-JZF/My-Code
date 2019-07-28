

// C++maze 20190319.cpp : 定义控制台应用程序的入口点。
//
#include"stdafx.h"
/*
用OOP解决一个迷宫路径的查找问题
软件运行如下：
输入迷宫的大小(行 列): 5 5
继续输入迷宫的路径信息(0表示可以走，1表示不能走)：
0 0 1 0 0
0 0 0 0 0
1 1 0 1 1
0 1 0 1 0
0 0 0 0 0
开始寻找迷宫路径信息中...

打印：迷宫不存在可通行的路径

* * 1 0 0
0 * * 0 0
1 1 * 1 1
0 1 * 1 0
0 0 * * *
*/

const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;
const int OK = 4;
const int ERR = 5;
/*
// 抽象迷宫路径节点
class MazeNode
{
public:
MazeNode() {}
MazeNode(int x, int y) :mx(x), my(y)
{
for (int i = 0; i < 4; ++i)
{
mway[i] = OK;
}
}


int getstate(int x) { return mway[x]; }
int getmval() { return mval; }
int getX() { return mx; }
int getY() { return my; }

void setWayState(int x, int state) { mway[x] = state; }
void setmval(int val) { mval = val; }
void setmx(int x) { mx = x; }
void setmy(int y) { my = y; }

private:
int mval;
int mx;
int my;
int mway[4];
};
// 抽象内存可增长的顺序栈
class CStack
{
public:
CStack(int size = 10) :msize(size), mtop(-1)
{
mpStack = new MazeNode[size];
}

~CStack()
{
delete[]mpStack;
mpStack = nullptr;     //NULL<=>0  指针空用nullptr
}

void push(MazeNode val)   //压栈
{
if (full())
{
if (!resize())
{
cout << "resize error" << endl;
return;
}
}
mpStack[++mtop] = val;
}
void pop()  //出栈
{
if (empty())
{
return;
}
--mtop;
}
MazeNode top()const
{
if (empty())
{
throw"stack empty!";
}
return mpStack[mtop];
}
bool full()const
{
return mtop + 1 == msize;
}
bool empty()const
{
return mtop == -1;
}
private:
MazeNode *mpStack;
int mtop;
int msize;
bool resize()  // 按原来2倍的大小扩展栈空间
{
MazeNode *newdata = new MazeNode[msize * 2];
if (NULL == newdata)
{
return false;
}
for (int i = 0; i < msize; i++)
{
newdata[i] = mpStack[i];
}
delete[]mpStack;
mpStack = newdata;
msize *= 2;
return true;
}
};
// ==========================================================抽象整个迷宫
class Maze
{
public:
Maze(int _mrow = 0, int _mcol = 0) :mrow(_mrow), mcol(_mcol)
{
mpcells = new MazeNode*[mrow];
for (int i = 0; i < mrow; ++i)
{
mpcells[i] = new MazeNode[mcol];
}
}
void setMazeNode(int val, int x, int y)//设置某个点的值
{
mpcells[x][y].setmval(val);
mpcells[x][y].setmx(x);
mpcells[x][y].setmy(y);
}
void setMazeNodeState()//设置某个点某个方向的方向状态
{
for (int i = 0; i < mrow; ++i)
{
for (int j = 0; j < mcol; ++j)
{
if (mpcells[i][j].getmval() == 1)
{
continue;
}
if (i == 0)
{
mpcells[i][j].setWayState(UP, ERR); //第一行
}
if (j == 0)
{
mpcells[i][j].setWayState(LEFT, ERR);//第一列
}
if (i == mrow - 1)
{
mpcells[i][j].setWayState(DOWN, ERR);//最后一行
}
if (j == mcol - 1)
{
mpcells[i][j].setWayState(RIGHT, ERR);//最后一列
}
if (i > 0 && mpcells[i - 1][j].getmval() == 1)
{
mpcells[i][j].setWayState(UP, ERR);//上边不可走
}
if (i < mrow - 1 && mpcells[i + 1][j].getmval() == 1)
{
mpcells[i][j].setWayState(DOWN, ERR);//下边不可走
}
if (j > 0 && mpcells[i][j - 1].getmval() == 1)
{
mpcells[i][j].setWayState(LEFT, ERR);//左边不可走
}
if (j < mcol - 1 && mpcells[i][j + 1].getmval() == 1)
{
mpcells[i][j].setWayState(RIGHT, ERR);//右边不可走
}
}
}
}
void findMazePath()
{
if (mpcells[0][0].getmval() == 1)
{
return;
}
mstack.push(mpcells[0][0]);
while (!mstack.empty())
{
MazeNode top = mstack.top();
int x = top.getX();
int y = top.getY();
if (x == mrow - 1 && y == mcol - 1)
{
return;
}
// 往右方向找
if (mpcells[x][y].getstate(RIGHT) == OK)
{
mpcells[x][y].setWayState(RIGHT, ERR);
mpcells[x][y + 1].setWayState(LEFT, ERR);
mstack.push(mpcells[x][y + 1]);
continue;
}
// 往下方向找
if (mpcells[x][y].getstate(DOWN) == OK)
{
mpcells[x][y].setWayState(DOWN, ERR);
mpcells[x + 1][y].setWayState(UP, ERR);
mstack.push(mpcells[x + 1][y]);
continue;
}
// 往左方向找
if (mpcells[x][y].getstate(LEFT) == OK)
{
mpcells[x][y].setWayState(LEFT, ERR);
mpcells[x][y - 1].setWayState(RIGHT, ERR);
mstack.push(mpcells[x][y - 1]);
continue;
}
// 往上方向找
if (mpcells[x][y].getstate(UP) == OK)
{
mpcells[x][y].setWayState(UP, ERR);
mpcells[x - 1][y].setWayState(DOWN, ERR);
mstack.push(mpcells[x - 1][y]);
continue;
}
mstack.pop();
}
}
void showResult()
{
if (mstack.empty())
{
cout << "该迷宫不存在可通行的路径" << endl;
return;
}
while (!mstack.empty())
{
MazeNode node = mstack.top();
mpcells[node.getX()][node.getY()].setmval('*');
mstack.pop();
}

for (int i = 0; i < mrow; i++)
{
for (int j = 0; j < mcol; j++)
{
if (mpcells[i][j].getmval() == '*')
{
cout << "*" << " ";
}

else
{
cout << mpcells[i][j].getmval() << " ";
}
}
cout << endl;
}
}

private:
int mcol;
int mrow;
MazeNode **mpcells;
CStack mstack;
};
*/
class MazeNode
{
public:
	MazeNode()
	{
		// 先初始化迷宫路径的四个方向为可行走状态
		for (int i = 0; i < 4; ++i)
		{
			mway[i] = OK;//初始化把结点的四个方向都设置为可状态
		}
	}
	int getVal() { return mval; }
	int getX() { return mx; }
	int getY() { return my; }
	int getWayState(int way) { return mway[way]; }

	void setWayState(int way, int state) { mway[way] = state; }//设置方向状态
	void setVal(int val) { mval = val; }
	void setX(int x) { mx = x; }
	void setY(int y) { my = y; }
private:
	int mval;
	int mx;
	int my;
	int mway[4];
};
// 抽象内存可增长的顺序栈
class Stack
{
public:
	// 成员方法，操作的就是成员变量
	Stack(int size = 10)
		:mtop(-1), msize(size)
	{
		mpStack = new MazeNode[msize];
	}
	~Stack()
	{
		delete[]mpStack;
		mpStack = nullptr;
	}
	void push(MazeNode &p)
	{
		if (this->full())
			this->resize();
		mpStack[++mtop] = p;
	}
	void pop()
	{
		if (this->empty())
			return;
		this->mtop--;
	}
	MazeNode top()const
	{
		if (empty())
			throw"";
		return this->mpStack[this->mtop];
	}
	bool full()const { return this->mtop == this->msize - 1; }
	bool empty()const { return this->mtop == -1; }
private:
	MazeNode *mpStack; // 存放栈的元素
	int mtop; // 栈顶指针
	int msize; // 栈的总长度
	void resize()
	{
		MazeNode* ptemp = new MazeNode[msize * 2];
		for (int i = mtop; i >= 0; i--)
		{
			ptemp[i] = mpStack[i];
		}
		delete[]mpStack;
		mpStack = ptemp;
		msize *= 2;
	}
};

// 抽象整个迷宫
class Maze
{
public:
	Maze(int r, int c)
		:mrow(r), mcol(c)
	{
		mpcells = new MazeNode*[mrow];
		for (int i = 0; i < mrow; ++i)
		{
			mpcells[i] = new MazeNode[mcol];
		}
	}
	~Maze()
	{
		for (int i = 0; i < mrow; ++i)
		{
			delete[]mpcells[i];
		}
		delete[]mpcells;
		mpcells = nullptr;
	}
	void setMazeNode(int val, int i, int j)
	{
		mpcells[i][j].setVal(val);
		mpcells[i][j].setX(i);
		mpcells[i][j].setY(j);
	}
	void setMazeNodeState()
	{
		for (int i = 0; i < mrow; ++i)
		{
			for (int j = 0; j < mcol; ++j)
			{
				if (mpcells[i][j].getVal() == 1)//如果值为1 说明不可走
				{
					continue;
				}
				if (i == 0)//说明是第一行则把他的上方向置为不可走
				{
					mpcells[i][j].setWayState(UP, ERR);
				}
				if (j == 0)//说明是第一列则把他的左方向置为不可走
				{
					mpcells[i][j].setWayState(LEFT, ERR);
				}
				if (i == mrow - 1)//说明是最后一行则把他的下方向置为不可走
				{
					mpcells[i][j].setWayState(DOWN, ERR);
				}
				if (j == mcol - 1)//说明是最后一列则把他的右方向置为不可走
				{
					mpcells[i][j].setWayState(RIGHT, ERR);
				}
				if (i>0 && mpcells[i - 1][j].getVal() == 1)
				//不是第一行且他的上方向[i - 1][j]的值为1，则把他的上方向置为不可走；
				{
					mpcells[i][j].setWayState(UP, ERR);
				}
				if (i<mrow - 1 && mpcells[i + 1][j].getVal() == 1)
				//不是最后一行且他的下方向[i + 1][j]的值为1，则把他的下方向置为不可走；
				{
					mpcells[i][j].setWayState(DOWN, ERR);
				}
				if (j>0 && mpcells[i][j - 1].getVal() == 1)
				//不是第一列且他的左方向[i][j - 1]的值为1，则把他的左方向置为不可走；
				{
					mpcells[i][j].setWayState(LEFT, ERR);
				}
				if (j<mcol - 1 && mpcells[i][j + 1].getVal() == 1)
				//不是最后一列且他的右方向[i][j + 1]的值为1，则把他的右方向置为不可走；
				{
					mpcells[i][j].setWayState(RIGHT, ERR);
				}
			}
		}
	}
	void findMazePath()
	{
		//若迷宫的起始结点的值为1，则肯定不存在迷宫路径；
		if (mpcells[0][0].getVal() == 1)
			return;

		//把正确的路径结点压入stack中；
		mstack.push(mpcells[0][0]);
		
		while (!mstack.empty())
		{
			MazeNode top = mstack.top();
			int x = top.getX();
			int y = top.getY();
			if (x == mrow - 1 && y == mcol - 1)//如果到达了迷宫的右下角则退出；
			{
				return;
			}
			//我们自己默认了一个结点的查询方向依次为右下左上
			//如果某一个结点的右边的的状态为可走
			if (mpcells[x][y].getWayState(RIGHT) == OK)
			{
				mpcells[x][y].setWayState(RIGHT, ERR);
				//把当前结点的右方向置为不可走 表示已经走过这条路径以后不能再走这条冤枉路了
				//以防止后来出栈后继续走这条路导致在这里死循环
				//详细下边会讲
				mpcells[x][y + 1].setWayState(LEFT, ERR);
				//同理把右边结点的左方向也置为不可走
				mstack.push(mpcells[x][y + 1]);
				//然后把右边的结点进行压栈 压入到迷宫的正确路径里边去
				continue;
			}
			//以下三个方向的调整思想都是同理的
			if (mpcells[x][y].getWayState(DOWN) == OK)
			{
				mpcells[x][y].setWayState(DOWN, ERR);
				mpcells[x + 1][y].setWayState(UP, ERR);
				mstack.push(mpcells[x + 1][y]);
				continue;
			}
			if (mpcells[x][y].getWayState(LEFT) == OK)
			{
				mpcells[x][y].setWayState(LEFT, ERR);
				mpcells[x][y - 1].setWayState(RIGHT, ERR);
				mstack.push(mpcells[x][y - 1]);
				continue;
			}
			if (mpcells[x][y].getWayState(UP) == OK)
			{
				mpcells[x][y].setWayState(UP, ERR);
				mpcells[x - 1][y].setWayState(DOWN, ERR);
				mstack.push(mpcells[x - 1][y]);
				continue;
			}
			//走到这一步说明该结点的四个方向都是不可走的 
			//所以我们要出栈试一试上个结点的其他方向是否可以通 
			//这时候回到上个结点就不能走这个结点的方向了 
			//而要走默认顺序的四个方向的下一个方向
			//因为我们当时已经把要走的下一个方向的状态置为不可走了
			//如果上个结点的四个方向也不通则一直出栈 
			//直到栈空 说明没有正确的通的迷宫路径
			mstack.pop();
		}
	}
	void showResult()
	{
		if (mstack.empty())//判断路径栈是否空
		{
			cout << "该迷宫不存在可通行的路径" << endl;
			return;
		}
		cout << "该迷宫存在可通行的路径为：" << endl;
		while (!mstack.empty())//把栈里边的正确路径信息的结点的值都设置为*；
		{
			MazeNode node = mstack.top();
			mpcells[node.getX()][node.getY()].setVal('*');
			mstack.pop();
		}
		//打印出迷宫
		for (int i = 0; i < mrow; ++i)
		{
			for (int j = 0; j < mcol; ++j)
			{
				if (mpcells[i][j].getVal() == '*')
				{
					cout << "*" << " ";
				}
				else
				{
					cout << mpcells[i][j].getVal() << " ";
				}
			}
			cout << endl;
		}
	}
private:
	int mcol;
	int mrow;
	MazeNode **mpcells;
	Stack mstack;
};
int main()
{
	cout << "输入迷宫的大小:";
	int row, col;
	cin >> row >> col;

	Maze maze(row, col);

	cout << "输入迷宫路径信息:" << endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			int data;
			cin >> data;  // data  [i, j]
			maze.setMazeNode(data, i, j);
		}
	}
	// 调整路径的行走状态信息
	maze.setMazeNodeState();

	// 开始寻找迷宫路径
	maze.findMazePath();

	// 打印迷宫路径信息
	maze.showResult();

	return 0;
}

