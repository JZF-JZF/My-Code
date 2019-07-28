// 简单工厂设计模式.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#if 0
enum TYPES //商品类型
{
	TYPEA,TYPEB
};

class BASE //抽象商品类
{
public:
	virtual void show() = 0;
};

class A:public BASE
{
public:
	void show()
	{
		cout << "A show!" << endl;
	}
};

class B:public BASE
{
public:
	void show()
	{
		cout << "B show!" << endl;
	}
};

class Factory
{
public:
	BASE* CREATEBASE(enum TYPES c)
	{
		if (c == TYPEA)
		{
			cout << "Create A！" << endl;
			return new A;
		}
		else if(c == TYPEB)
		{
			cout << "Create B！" << endl;
			return new B;
		}
	}
};

int main()
{
	Factory m;
	BASE *p = m.CREATEBASE(TYPEA);
	p->show();
	p = m.CREATEBASE(TYPEB);
	p->show();
    return 0;
}
#endif