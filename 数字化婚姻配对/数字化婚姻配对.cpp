#include"stdafx.h"


using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
const int MALE = 1;
const int FEMALE = 0;

class MyTimer
{
public:
	MyTimer()
	{
		QueryPerformanceFrequency(&_freq);
		costTime = 0.0;
	}
	void Start()
	{
		for (int i = 0; i < EN_NUMER; ++i)
		{
			QueryPerformanceCounter(&_array[i]._begin);
		}
	}
	void Stop()
	{
		for (int i = 0; i < EN_NUMER; ++i)
		{
			QueryPerformanceCounter(&_array[i]._end);
		}
	}
	void Reset()
	{
		costTime = 0.0;
	}
	void showTime()
	{
		double allTime = 0.0;
		for (int i = 0; i < EN_NUMER; ++i)
		{
			allTime += (((double)_array[i]._end.QuadPart - (double)_array[i]._begin.QuadPart) / (double)_freq.QuadPart);
		}
		costTime = allTime / EN_NUMER;
		costTime *= 1000000;

		if ((((int)costTime) / 1000000) > 0)
		{
			cout << costTime / 1000000 << " s" << endl;
		}
		else if (((int)costTime) / 1000 > 0)
		{
			cout << costTime / 1000 << " ms" << endl;
		}
		else
		{
			cout << costTime << " us" << endl;
		}
	}
private:
	class Array
	{
	public:
		LARGE_INTEGER _begin;
		LARGE_INTEGER _end;
	};
	enum { EN_NUMER = 5 };
	LARGE_INTEGER _freq;
	double costTime;
	Array _array[EN_NUMER];
};
//=====================================================================================================
/* 人员属性信息 */
class Person
{
public:
	Person() {}
	Person(int gender, int id, int look, int character, int treasure,
		int olook, int ocharacter, int otreasure)
		:mgender(gender), mid(id), mlook(look), mcharacter(character),
		mtreasure(treasure), molook(olook), mocharacter(ocharacter), motreasure(otreasure) {}

	int getId() { return mid; }
	int getLook() { return mlook; }
	int getCharacter() { return mcharacter; }
	int getTreasure() { return mtreasure; }

	int getOlook() { return molook; }
	int getOcharacter() { return mocharacter; }
	int getOtreasure() { return motreasure; }
	int getGender() { return mgender; }

	bool operator==(const Person& rhs)
	{
		return mid == rhs.mid;
	}

	bool operator<(const Person& rhs)const
	{
		return mid < rhs.mid;
	}
private:
	int mid; // 本人id
	int mlook; // 本人样貌
	int mcharacter; // 本人品质
	int mtreasure; // 本人财富

	int molook; // 期望样貌
	int mocharacter; // 期望品质
	int motreasure; // 期望财富
	int mgender; // 本人性别
};

//=====================================================================================================
/* 从文件获取男性女性信息，传入参数为性别 */
vector<Person>getData(string file, int gender)
{
	vector<Person> vec;
	vec.reserve(100);
	int id, look, character, treasure, olook, ocharacter, otreasure;

	FILE* fp;
	fopen_s(&fp, file.c_str(), "r");
	assert(fp != 0);

	for (int i = 0; i < 100; ++i)
	{
		fscanf_s(fp, "%d,%d,%d,%d,%d,%d,%d", &id, &look, &character
			, &treasure, &olook, &ocharacter, &otreasure);
		Person per(gender, id, look, character, treasure, olook,
			ocharacter, otreasure);

		vec.emplace_back(per);
	}
	fclose(fp);
	return vec;
}

//=====================================================================================================
/* 从文件获取主角的信息，传入参数id，置为-1 */
vector<Person>getPlayerData(string file, int id)
{
	vector<Person> vec;
	vec.reserve(100);
	int gender, look, character, treasure, olook, ocharacter, otreasure;
	FILE* fp;
	fopen_s(&fp, file.c_str(), "r");
	assert(fp != 0);

	for (int i = 0; i < 100; ++i)
	{
		fscanf_s(fp, "%d,%d,%d,%d,%d,%d,%d", &gender, &look
			, &character, &treasure, &olook, &ocharacter, &otreasure);

		//每轮循环构造一个person对象
		Person per(gender, id, look, character, treasure,
			olook, ocharacter, otreasure);

		vec.emplace_back(per);
	}
	fclose(fp);
	return vec;
}

//=====================================================================================================
/* 匹配计算 */
class Calculate
{
private:

	vector<Person> female; // 存储女性信息
	vector<Person> players; // 存储主角信息
	vector<Person> male; // 存储男性信息

	int msize; // 初始化容器空间大小
	bool isExist; // 标志位，标志一轮主角是否被选择
	int index; // 输出索引

public:

	/* 初始化 */
	Calculate(int size) :msize(size)
	{
		male = vector<Person>(size);
		female = vector<Person>(size);
		isExist = false; // 标志位置为false
		index = 0; // 输出索引初始为0
	}

	void start()
	{
		vector<Person> maleData(getData("male.txt", MALE));
		vector<Person> femaleData(getData("female.txt", FEMALE));
		players = getPlayerData("players.txt", -1); // 主角id为-1

													/* 将主角加入，开始匹配 */
		for (Person player : players)
		{
			/* 拿到男女生信息的副本 */
			male.assign(maleData.begin(), maleData.end());
			female.assign(femaleData.begin(), femaleData.end());

			/* 根据主角性别加入到相应的队列中 */
			if (player.getGender() == MALE)
			{
				male.emplace_back(player);
			}
			else
			{
				female.emplace_back(player);
			}
			choiceFemale();
		}
	}

	/* 全部男生开始选最合适的女生 */
	void choiceFemale()
	{
		/* map存储 <女生，男生列表> */
		map<Person, vector<Person>> hashMap;
		Person suit;



		for (Person per : male)
		{
			/* 拿到最合适的女生 */
			suit = satisfy(per, female);

			auto it = hashMap.find(suit);

			/* 女生已被选，直接加入其列表 */
			if (it != hashMap.end())
			{
				it->second.emplace_back(per);
			}
			/* 女生没被选过，直接创建map存储 */
			else
			{
				vector<Person> maleList;
				maleList.emplace_back(per);
				hashMap.insert(pair<Person,
					vector<Person>>(suit, maleList));
			}
		}

		for (int i = 0; i < msize; i++)
		{
			/* 拿到被选最多的女生 */
			Person mFemale(invFemale(hashMap));

			/* 女生选择最合适的男生 */
			vector<Person> maleList(choiceMale(mFemale, hashMap));

			/* 返回长度为0，表示主角已被选，本轮结束 */
			if (maleList.size() == 0)
			{
				break;
			}

			/* 否则，开始遍历受邀最多女生的男性列表 */
			vector<Person>::iterator it = maleList.begin();
			while (it != maleList.end())
			{
				Person per(*it);

				// 同上，男生继续选择新的最满意的女生
				Person max_best(satisfy(per, female));
				auto it1 = hashMap.find(max_best);
				/* 女生已被选，直接加入其队列 */
				if (it1 != hashMap.end())
				{
					it1->second.emplace_back(per);
				}
				/* 女生没被选过，直接创建map存储 */
				else
				{
					vector<Person> maleList;
					maleList.push_back(per);
					hashMap.insert(pair<Person,
						vector<Person>>(max_best, maleList));
				}
				++it;
			}
		}
		/* 如果主角本轮没有被选，那么player的选择id为默认值-2，不打印信息 */
		if (!isExist)
		{
			cout << "第" << ++index << "组player加入： " << endl;
		}
		/* 否则，主角本轮被选，将标志位置回 */
		else
		{
			isExist = false;
		}
	}

	/* 女生选择最合适的男生 */
	vector<Person> choiceMale(Person & mFemale, map<Person, vector<Person>> & hashmap)
	{
		/* 拿到该女生的男生列表 */
		vector<Person> maleList(hashmap[mFemale]);
		/* 拿到该女生最满意的男生 */
		Person suit(satisfy(mFemale, maleList));

		/* 如果其中有主角，则匹配成功，直接打印 */
		if (mFemale.getId() == -1 || suit.getId() == -1)
		{
			/*cout << mFemale.getId() << " : ";
			auto it1 = maleList.begin();
			while (it1 != maleList.end())
			{
			cout << (*it1).getId() << "  ";
			++it1;
			}
			cout << endl;*/

			isExist = true; // 标志位置true

							/* 如果其中有主角，则匹配成功，直接打印 */
			if (mFemale.getId() == -1)
			{
				cout << "第" << ++index << "组player加入："
					<< suit.getId() << ":" << "-1" << endl;
			}
			else
			{
				cout << "第" << ++index << "组player加入："
					<< "-1" << ":" << mFemale.getId() << endl;
			}
			/* 返回空容器 */
			return vector<Person>();
		}

		/*
		** 若匹配成功的一对中没有主角，那么从male、
		** female副本、maleList列表中删除它们
		*/
		auto it = find(male.begin(), male.end(), suit);
		male.erase(it);

		it = find(female.begin(), female.end(), mFemale);
		female.erase(it);

		it = find(maleList.begin(), maleList.end(), suit);
		maleList.erase(it);

		return maleList;
	}
	/* 拿到受邀最多的女方 */
	Person invFemale(map<Person, vector<Person>> & hashmap)
	{
		unsigned int CurmaxNum = 0; /* 当前最大女生被选数目 */
		Person mostInvFemale;

		for (Person per : female)
		{
			vector<Person> maleList;

			auto it = hashmap.find(per);
			if (it != hashmap.end())
			{
				/* 得到女生的男性队列 */
				maleList = it->second;
			}

			if (!maleList.empty())
			{
				/* 出现女生被选数目相同的情况 */
				if (maleList.size() == CurmaxNum)
				{
					mostInvFemale = choice(per, mostInvFemale);
				}
				else if (maleList.size() > CurmaxNum)
				{
					mostInvFemale = per;
					CurmaxNum = maleList.size();
				}
			}
		}
		return mostInvFemale;
	}

	/* 得到最满意的对象 */
	Person satisfy(Person & choPer, vector<Person> & beChoPer)
	{
		Person suit;
		int maxValue = 0;

		/* 遍历被选对象 */
		for (Person per : beChoPer)
		{
			/* 计算参考值  */
			int val = choPer.getOlook() * per.getLook() +
				choPer.getOcharacter() * per.getCharacter() +
				choPer.getOtreasure() * per.getTreasure();

			if (val > maxValue)
			{
				suit = per;
				maxValue = val;
			}
			/* 出现参考值相同的情况 */
			else if (val == maxValue)
			{
				suit = choice(suit, per);
			}
		}
		return suit;
	}

	/* 出现相同参考值或被选数目相同情况时的处理 */
	Person choice(Person & cur, Person & suit)
	{
		int presentNum = cur.getLook()
			+ cur.getCharacter() + cur.getTreasure();

		int bestNum = suit.getLook()
			+ suit.getCharacter() + suit.getTreasure();

		/* 自身参考值也都相同比较id，主角id是-1，因此主角优先级最高 */
		if (presentNum == bestNum)
			return cur.getId() < suit.getId() ? cur : suit;

		return presentNum > bestNum ? cur : suit;
	}
};

//=====================================================================================================
int main()
{
	Calculate cal(100);

	MyTimer timer;
	timer.Start();

	cal.start();

	timer.Stop();
	timer.showTime();

	//static omp_lock_t lock;
	//omp_init_lock(&lock);
	//#pragma omp parallel for
	//	for (size_t i = 0; i < 5000; i++)
	//	{
	//		omp_set_lock(&lock);
	//		cout << i << endl;
	//		omp_unset_lock(&lock);
	//	}
	//	omp_destroy_lock(&lock);
	//	timer.Stop();
	//	timer.showTime();
	return 0;
}
