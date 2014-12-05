///@file 用数组表示并查集的相关操作
///@author zhaowei
///@date 2014.12.05
///@version 1.0
/* @note 并查集经常用森林来表示，每一个元素就是一个节点，初始时一个元素就是一个集合，然后符合同一条件的集合之间可以进行Union操作，为了找到
		 符合同一条件的集合，需要在集合之间进行Find操作。
		 在用数组作为并查集的数据存储结构时，每一个数组元素的下标代表元素名称，每个集合的根节点的元素值为负数，其绝对值表示该集合（树）上的
		 节点数目；非根节点的元素值表示其父节点的下标。
*/
#include <iostream>
using namespace std;

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
	return 0;
}


