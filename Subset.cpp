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

///@brief 增量构造法
///@param[in] S 输入集合
///@param[in] n 集合大小
///@param[inout] P 某个子集
///@param[in] cur P的当前位置
///@param[in] ed S的当前位置，前面的元素已经选过了
///@return 无
void print_subset1(vector<string> S, int n, vector<string> P, int cur, int ed)
{
	for (int i = ed; i < n; i++)
	{
		P[cur] = S[i];
		for (int j = 0; j <= cur; j++)
		{
			cout << P[j] << " ";
		}
		cout << endl;
		print_subset1(S, n, P, cur + 1, i + 1);
	}
}

int main()
{
	vector<string> svec, pvec;
	cout << "Input elements of the set, end as \"EOF\": " << endl;
	string str;
	int cnt = 0;
	while (cin >> str && str != "EOF")
	{
		svec.push_back(str);
		pvec.push_back("");
		cnt++;
	}
	cout << "---------------------------------------------------------\n";
	cout << "The entire set is: " << endl;
	for (int i = 0; i < cnt; i++)
	{
		cout << svec[i] << " ";
	}
	cout << endl;
	cout << "---------------------------------------------------------\n";
	cout << "The subsets are: " << endl;
	print_subset1(svec, cnt, pvec, 0, 0);
	return 0;
}
