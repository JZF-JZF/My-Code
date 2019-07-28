//工厂方法设计模式.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#if 0

enum TYPES
{
	TYPEA, TYPEB
};

class BASE	//抽象产品类
{
public:
	virtual void show() = 0;
};

class A :public BASE	//具体产品类
{
public:
	void show()
	{
		cout << "A show!" << endl;
	}
};

class B :public BASE	//具体产品类
{
public:
	void show()
	{
		cout << "B show!" << endl;
	}
};

class Factory	//抽象工厂类
{
	virtual BASE* CREATEBASE(enum TYPES c) = 0;
};

class FactoryA:public Factory	//具体工厂类
{
public:
	BASE* CREATEBASE(enum TYPES c)
	{
		cout << "Create A！" << endl;
		return new A;
	}
};

class FactoryB:public Factory
{
public:
	BASE* CREATEBASE(enum TYPES c)
	{
		cout << "Create B！" << endl;
		return new B;
	}
};

int main()
{
	FactoryA m;
	BASE *p = m.CREATEBASE(TYPEA);
	p->show();
	FactoryB n;
	p = n.CREATEBASE(TYPEB);
	p->show();
	return 0;
}
#endif
