///@file 线段树练习2
///@author zhaowei
///@date 2014.12.17
///@version 1.0
/* @note 
   题目描述
   给定N个数，有两种操作：
   1. 给区间[a, b]的所有数都增加X；
   2. 询问第i个数是什么。

   输入
   第一行一个正整数n，接下来n行n个整数，再接下来一个正整数Q，表示操作的个数. 接下来Q行每行若干个整数。如果第一个数是1，
   后接3个正整数a,b,X，表示在区间[a,b]内每个数增加X,如果是2，后面跟1个整数i, 表示询问第i个位置的数是多少。

   输出
   对于每个询问输出一个答案

   样例输入
   3
   1
   2
   3
   2
   1 2 3 2
   2 3

   样例输出
   5

   数据范围
   1<=n<=100000
   1<=q<=100000

   本题来自于http://codevs.cn/problem/1081/
   线段树和直接用数组来访问在效率上有什么区别呢？
   假设查询区间的大小为m，数据量大小为n
   如果使用数组的话，这道题更新操作的时间复杂度为O(m)，查询时间复杂度为O(1)，空间复杂度为O(n)；
   如果使用线段树的话，更新操作的时间复杂度为O(?)，查询时间复杂度为O(?)，空间复杂度为O(n).
   这道题只是用来练习线段树，并不能体现线段树的高效。
*/

#include <iostream>
using namespace std;

#define MAXN 100001
int input[MAXN];

int main()
{
	int n = 0;
	int q = 0;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> input[i + 1];
	}

	cin >> q;
	while (q--)
	{
		int op_type = 0;
		cin >> op_type;

		if (op_type == 1)
		{
			int l = 0, r = 0;
			cin >> l >> r;
			int delta = 0;
			cin >> delta;

			for (int i = l; i <= r; i++)
			{
				input[i] += delta;
			}
		}
		else if (op_type == 2)
		{
			int index = 0;
			cin >> index;
			cout << input[index] << endl;;
		}
	}
	return 0;
}