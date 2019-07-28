#include"stdafx.h"
//#include <iostream>
//#include <vector>
//using namespace std;
//
//typedef vector<int> Vec;
//typedef vector<int>::iterator VecIt;
//
//void print(Vec &v)
//{
//	VecIt it;
//	for (it = v.begin(); it != v.end(); it++)
//	{
//		cout << *it << " ";
//	}
//
//	cout << endl;
//}
//
//void deleteValueFromVector(Vec &v, int n = 5)
//{
//	VecIt it;
//	for (it = v.begin(); it != v.end();/*不能再自增了*/)
//	{
//		if (0 == *it % n)
//		{
//			it=v.erase(it);// vector元素自动向前挪动了(关联的map容器元素不会自动挪动)， 所以不能再把it进行++了
//		}
//		else
//		{
//			it++;
//		}
//	}
//}
//
//int main()
//{
//	Vec v;
//	int i = 0;
//	for (i = 0; i < 21; i++)
//	{
//		v.push_back(i); // 不能再傻傻地用下标了
//	}
//
//	print(v);
//
//	deleteValueFromVector(v); // 程序ok
//	print(v);
//
//	return 0;
//}