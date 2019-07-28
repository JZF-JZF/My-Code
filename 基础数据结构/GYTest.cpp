
#include"AfxStd.h"
#include"ListStack.h"

int main()
{
	LinkStack mys;
	InitStack(mys);
	int x;
	while (cin >> x, x != -1)
	{
		Push(mys, x);
	}
	while (Pop(mys, x))
	{
		cout << x << " ";
	}
	cout << endl;
	DestroyStack(mys);
}
