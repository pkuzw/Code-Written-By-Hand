///@file 两个黑帮
///@author zhaowei
///@date 2014.12.09
///@version 1.0
/* @note
   描述
   Tadu城有两个黑帮帮派，已知有N个黑帮份子，从1到N编号，每人至少属于一个帮派。每个帮派至少有一个人。给你M条信息，有两类信息：
   1. D a b，明确告诉你，a和b属于不同帮派
   2. A a b，问你，a和b是否属于不同的帮派

   输入
   第一行是一个整数T，表示有T组测试用例。每组测试用例的第一行是两个整数N和M，接下来是M行，每行包含一条消息。

   输出
   对每条消息"A a b"，基于当前获得的信息，输出判断。答案是"In the same gang."或"In different gangs."或"Not sure yet."。

   样例输入
   1
   5 5
   A 1 2
   D 1 2
   A 1 2
   D 2 4
   A 1 4

   样例输出
   Not sure yet.
   In different gangs.
   In the same gang.

   解题思路
   把不在同一个帮派的节点用并查集合并在一起。这样的话，如果询问的两个黑帮分子在同一个并查集中，那么他们之间的关系就是确定的，否则无法
   确定他们的关系。比如说A和B不在同一个帮派，C和D不在同一个帮派，但是A和C，A与D之间的关系是否在一个帮派并不确定。可以通过给每个节点设
   额外附加信息，记录其距离集合根节点的距离。如果询问的两个节点距离其根节点的距离都是奇数或者都是偶数，那么这两个节点在同一个帮派，否
   则，就在不同帮派。因为要用到节点到根节点的距离，所以在实现Find操作时，没有采用压缩路径的算法。

   本题来自于POJ 1703，按照该代码提交后提示Time Limit Exceeded
*/

#include <iostream>
using namespace std;

#define  MAXN 100001	
int s[MAXN];	//并查集数组
int dist[MAXN];	//到根节点的距离的奇偶性

///@brief 初始化并查集
///@param[in] s 并查集数组
///@param[in] n 并查集的元素个数
///@return 无
void ufs_init(int s[], int n)
{
	for (int i = 0; i < n; i++)
	{
		s[i] = -1;
		dist[i] = 0;
	}
}

///@brief Find操作
///@param[in] s 并查集数组
///@param[in] x 待查找元素
///@return 返回该元素所在树的树根
int ufs_find_naive(const int s[], int x)
{
	while (s[x] >= 0)
	{
		x = s[x];
		dist[x] = (dist[x] + dist[s[x]]) % 2;	//??
	}
	return x;
}

///@brief Union操作，将root2集合并入root1集合
///@param[in] s 并查集数组
///@param[in] root1 一棵树的树根
///@param[in] root2 另一棵树的树根
///@return 如果二者已经在同一个集合，返回0；否则返回1
int ufs_union(int s[], int root1, int root2)
{
	if (root1 == root2)
	{
		return 0;
	}
	s[root1] += s[root2];
	s[root2] = root1;
	return 1;
}

int main()
{
	int test_num = 0;	//测试样例数目
	cin >> test_num;
	while (test_num--)
	{
		int n = 0, m = 0;	//黑帮分子数目n；消息数目m
		char msg_type = '\0';	//消息种类：A或者D

		//并查集元素x, y及其根节点
		int x = 0, y = 0, root_x = 0, root_y = 0;

		cin >> n >> m;
		ufs_init(s, MAXN);

		while (m--)	//输入m条信息
		{
			cin >> msg_type >> x >> y;
			root_x = ufs_find_naive(s, x);
			root_y = ufs_find_naive(s, y);

			if (msg_type == 'A')
			{
				if (root_x == root_y)	//如果在同一个集合，则可以对两者的关系进行判断
				{
					if (dist[x] != dist[y])	//如果两元素到根节点的距离不同时为奇数或偶数，则不在同一个帮派
					{
						cout << "In different gang." << endl;
					} 
					else	//否则就在同一个帮派
					{
						cout << "In the same gang." << endl;
					}					
				}
				else
					cout << "Not sure yet." << endl;			
			} 
			else if (msg_type == 'D')	//如果两元素不在同一个帮派，则进行合并操作
			{
				ufs_union(s, root_x, root_y);
				dist[root_y] = (dist[x] + dist[y] + 1) % 2;	//??
			}
		}
	}
	return 0;
}