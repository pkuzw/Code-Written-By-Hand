///@file 病毒感染者
///@author zhaowei
///@date 2014.12.08
///@version 1.0
/* @note
   描述
   一个学校有n个社团，一个学生能同时加入不同的社团。由于社团内部同学们交往频繁，如果一个学生感染了病毒，该社团的所有学生都会感染病毒。
   现在0号学生感染了病毒，问一共有多少人感染了病毒。

   输入
   输入包含多组测试用力。每个测试用例，第一行包含两个整数n, m。n表示学生个数，m表示社团个数。假设0 < n <= 30000，0 <= m <= 500.每个
   学生从0到n-1编号。接下来是m行，每行开头是一个整数k，表示该社团的学生个数，接着是k个整数表示该社团的学生编号。最后一个测试用例，
   n = 0, m = 0，表示输入结束。

   输出
   对每个测试用例，输出感染了病毒的学生数目。

   样例输入
   100 4
   2 1 2
   5 10 13 11 12 14
   2 0 1
   2 99 1
   200 2
   1 5
   5 1 2 3 4 5
   1 0
   0 0

   样例输出
   4
   1
   1
*/

#include <iostream>
using namespace std;

#define MAXN 30000
int s[MAXN];

///@brief 初始化并查集
///@param[in] s 存储并查集的数组
///@param[in] n 数组元素数目
///@return 无
void ufs_init(int s[], int n)
{
	for (int i = 0; i < n; i++)
	{
		s[i] = -1;	//初始时每一个元素为一个集合，其值为该集合的元素数目的负数
	}
}

///@brief Find操作，朴素版
///@param[in] s 并查集
///@param[in] x 待查找的元素
///@return 返回待查找的元素所在树的根节点下标
int ufs_find_naive(const int s[], int x)
{
	while (s[x] >= 0)
	{
		x = s[x];
	}
	return x;
}

///@brief Find操作，带路径压缩的迭代版
///@param[in] s 并查集
///@param[in] x 待查找的元素
///@return 返回待查找的元素所在树的根节点下标
///@note 路径压缩，就是从根节点到待查找元素路径上所有深度超过1的节点直接连接到根节点上
int ufs_find_iter(int s[], int x)
{
	int oldx = x;	//记录原始x

	//找到x元素所在树的根节点
	while (s[x] >= 0)
	{
		x = s[x];
	}

	//将路径上所有没有直接指向根节点的元素全部改为指向根节点
	while (oldx != x)
	{
		int tmp = s[oldx];	//用于保存当前元素的父节点下标
		s[oldx] = x;		//将当前节点的父节点改为根节点
		oldx = tmp;			//将当前节点改为原先的父节点，继续下一次迭代
	}
	return x;
}

///@brief Find操作，带路径压缩的递归版
///@param[in] s 并查集
///@param[in] x 待查找的元素
///@return 返回待查找的元素所在树的根节点下标
int ufs_find_recur(int s[], int x)
{
	if (s[x] < 0)	//递归的退出条件
	{
		return x;
	}

	s[x] = ufs_find_recur(s, s[x]);	//!!妙！在回溯的时候压缩路径，将路径上的每个元素都指向根节点
	return s[x];
}

///@brief Union操作，将root2并入到root1
///@param[in] s 并查集数组
///@param[in] root1 一棵树的树根
///@param[in] root2 另一颗树的树根
///@return 如果二者已经在同一集合，则Union操作失败，返回0；否则返回1
int ufs_union(int s[], int root1, int root2)
{
	if (root1 == root2)
	{
		return 0;
	}

	s[root1] += s[root2];	//调整合并后集合元素的总数
	s[root2] = root1;		//将root2集合并入root1集合
	return 1;
}

int main()
{
	int n = 0;	//学生人数
	int m = 0;	//社团数目
	
	
	while (cin >> n >> m && n > 0)	//输入学生人数和社团数目
	{
		ufs_init(s, MAXN);	//初始化并查集数组
		
		while (m--) //输入每个社团的人数和学生编号
		{
			int k = 0;	//社团内的学生数目
			int x = 0, y = 0;	//两个学生的编号
			int root_x = 0, root_y = 0;	//学生x和y所在树的树根
			cin >> k;

			cin >> x;	//输入社团中的第一个学生ID
			root_x = ufs_find_recur(s, x);	//找到该学生的树根
			while (--k > 0)	//输入剩下k-1个学生的ID
			{
				cin >> y;	
				root_y = ufs_find_recur(s, y);	//找到他们所属的树根
				ufs_union(s, root_x, root_y);	//将新输入的学生所在树合并到第一个学生所在树
			}			
		}
		//输出0号学生所在数的根节点的相反值，即该树所包含的节点数目，即被感染的学生数目
		cout << -s[ufs_find_recur(s, 0)] << endl;
	}
	return 0;
}