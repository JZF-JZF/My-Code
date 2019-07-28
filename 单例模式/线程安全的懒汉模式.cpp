#include"stdafx.h"

class Singleton
{
private:
	static Singleton *singleton;
	Singleton()
	{
		cout << "Singleton()" << endl;
	}
public:
	static pthread_mutex_t mutex;
	static Singleton* Get_Instance()
	{
		if (singleton == NULL)
		{
			pthread_mutex_lock(&mutex);
			cout << "ADDLOCK()" << endl;

			if (singleton == NULL)
			{
				singleton = new Singleton();
			}

			pthread_mutex_unlock(&mutex);
			cout << "UNLOCK()" << endl;
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
pthread_mutex_t Singleton::mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
	cout << "start!" << endl;
	Singleton* s1 = Singleton::Get_Instance();
	Singleton* s2 = Singleton::Get_Instance();
	cout << s1 << endl;
	cout << s2 << endl;
}