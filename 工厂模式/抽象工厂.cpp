//抽象设计模式.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#if 0
class CPHONE	//抽象手机类
{
public:
	virtual void show() = 0;
};

class Cxiaomiphone :public CPHONE	//具体产品小米手机类
{
public:
	void show()
	{
		cout << "xiaomi phone produce!" << endl;
	}
};

class Chuaweiphone :public CPHONE	//具体产品华为手机类
{
public:
	void show()
	{
		cout << "huawei phone produce!" << endl;
	}
};

class CTV	//抽象电视类
{
public:
	virtual void show() = 0;
};

class Cxiaomitv :public CTV	//具体产品小米电视类
{
public:
	void show()
	{
		cout << "xiaomi TV produce!" << endl;
	}
};

class Chuaweitv :public CTV	//具体产品华为电视类
{
public:
	void show()
	{
		cout << "huawei TV produce!" << endl;
	}
};

class Factory	//抽象工厂类
{
public:
	virtual CPHONE* CREATEPHONE() = 0;
	virtual CTV* CREATETV() = 0;
};

class Factory_XIAOMI :public Factory	//具体小米工厂类
{
public:
	CPHONE* CREATEPHONE()
	{
		return new Cxiaomiphone();
	}
	CTV* CREATETV()
	{
		return  new Cxiaomitv();
	}
};

class Factory_HUAWEI :public Factory	//具体华为工厂类
{
public:
	CPHONE* CREATEPHONE()
	{
		return new Chuaweiphone();
	}
	CTV* CREATETV()
	{
		return  new Chuaweitv();
	}
};

int main()
{
	//小米
	Factory* factory = new Factory_XIAOMI();
	CPHONE* phone = factory->CREATEPHONE();
	CTV* tv = factory->CREATETV();
	phone->show();
	tv->show();

	//华为
	factory = new Factory_HUAWEI();
	phone = factory->CREATEPHONE();
	tv = factory->CREATETV();
	phone->show();
	tv->show();

	delete factory;
	delete phone;
	delete tv;
	return 0;
}

#endif
