// 单例懒汉模式.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#if 0
class Singleton
{
private:
	static Singleton *singleton;
	Singleton()
	{
		cout << "Singleton()" << endl;
	}
public:
	static Singleton* Get_Instance()
	{
		if (singleton == NULL)
		{
			singleton = new Singleton();
		}
		return singleton;
	}
	class Destroy
	{
	public:
		~Destroy()
		{
			if (Singleton::singleton)
			{
				delete Singleton::singleton;
				cout << "~CSingleton()" << endl;
			}
		}
	};
	static Destroy destroy;
};
Singleton* Singleton::singleton = NULL;
Singleton::Destroy destroy;

int main()
{
	cout << "process start!" << endl;
	Singleton* s1 = Singleton::Get_Instance();
	Singleton* s2 = Singleton::Get_Instance();
	cout << s1 << endl;
	cout << s2 << endl;
}
#endif

