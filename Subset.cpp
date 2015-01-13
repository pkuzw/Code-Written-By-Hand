///@file 给定一个集合，求出其所有子集，假设集合中没有重复元素
///@author zhaowei
///@date 2015.01.10
///@version 1.0
///@note 
/* 增量构造法	一次选出一个元素，放或者不放入到集合中
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	vector<string> svec;
	cout << "Input elements of the set, end as \"EOF\": ";
	string str;
	int cnt = 0;
	while (cin >> str && str != "EOF")
	{
		svec.push_back(str);
		cnt++;
	}

	for (int i = 0; i < cnt; i++)
	{
		cout << svec[i] << " ";
	}
	cout << endl;
	return 0;
}
