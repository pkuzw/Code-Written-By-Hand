///@file 利用线段树解决给定N个数，在任意区间求最大数和最小数之间的差
///@author zhaowei
///@date 2014.12.13
///@version 1.0
/* @note 
   描述
   给定N（1 <= N <= 50,000）个数，A1，A2，A3，...，AN，求任意区间中最大数和最小数的差

   输入
   第一行包含两个整数，N和Q，Q表示查询次数
   第二行到第N+1行，每行包含一个整数A
   第N+2行到第N+Q+1行，每行包含两个整数a和b（1 <= a <= b <= N），表示区间A[a, b]

   输出
   对每个查询进行回应，输出该区间内最大数和最小数的差

   样例输入
   6 3
   1
   7
   3
   4
   2
   5
   1 5
   4 6
   2 2

   样例输出
   6
   3
   0

   线段树相关概念
   Segment Trees，又名区间树（Interval Trees），它在各个节点保存一条线段（即子数组）。设数列A包含N个元素，
   则线段树的各节点表示整个区间A[1, N]，左孩子表示区间A[1, (1 + N)/2]，右孩子表示区间A[(1 + N)/2 + 1, N]，不断递归，直到叶子节点，
   叶节点只包含一个元素。

   线段树有如下特征：
   1. 它是一棵完全二叉树
   2. 深度不超过logL，L是区间的长度
   3. 线段树把一个长度为L的区间分成不超过2L条线段

   线段树的基本操作有构造线段树，区间查询和区间修改
   线段树通常由于解决和区间统计有关的题目。比如某些数据可以按区间进行划分，按区间动态进行修改，而且还需要按区间多次进行查询，
   那么使用线段树可以达到较快的查询速度。

   用线段树解题，关键是要想清楚每个节点要存哪些信息，以及这些信息如何高效查询和更新。不要一更新就更新到叶子节点，
   那样更新的效率最坏有可能是O(N)。

   本题类似于POJ 3264，能够正确输出，但是TLE。
*/

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAXN 50001	//包含的最多元素数目
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define left_child(a) ((a) << 1)		//计算完全二叉树中某一节点的左孩子
#define right_child(a) (((a) << 1) + 1)	//计算完全二叉树中某一节点的右孩子

typedef struct node_t
{
	int left, right; //区间的左右边界
	int max, min;	//区间内的最大值和最小值
}node_t;

int A[MAXN];	//保存输入的原始数据数组


node_t node[MAXN * 4];	//线段树，一棵完全二叉树，节点编号从1开始，层次从1开始，用一维数组存储，看空间约为4N

int minx, maxx;	//查询结果

///@brief 初始化线段树
///@return 无
void init()
{
	memset(node, 0, sizeof(node));
}

///@brief 建立线段树
///@param[in] t 根节点
///@param[in] l 区间的左边界
///@param[in] r 区间的右边界
///@return 无
void build(int t, int l, int r)
{
	node[t].left = l;
	node[t].right = r;

	if (l == r)	//如果区间内只有一个元素
	{
		node[t].max = A[l];
		node[t].min = A[l];
		return;
	}
	//否则，递归的构建线段树
	int mid = (l + r) / 2;
	build(left_child(t), l, mid);	//构建左子树
	build(right_child(t), mid + 1, r);//构建右子树
	node[t].max = max(node[left_child(t)].max, node[right_child(t)].max);
	node[t].min = min(node[left_child(t)].min, node[right_child(t)].min);
}

///@brief 查询根节点为t，区间为A[l, r]的最大值和最小值
///@param[in] t 线段树的根节点
///@param[in] l 查询区间的左边界
///@param[in] r 查询区间的右边界
///@return 无
void query(int t, int l, int r)
{
	//如果查询区间正好与线段树该根节点所代表的区间重合，则直接用线段树该节点的最大值和最小值进行比较后决定是否赋值
	if (node[t].left == l && node[t].right == r)
	{
		if (maxx < node[t].max)
			maxx = node[t].max;
		if (minx > node[t].min)
			minx = node[t].min;
		return;
	}

	//否则，应该将问题递归的分成三种情况，查询区间在左孩子所代表的区间；查询区间在右孩子所代表的区间以及横跨两个孩子的区间
	int mid = (node[t].left + node[t].right) / 2;
	if (l > mid)
	{
		query(right_child(t), l, r);
	}
	else if (r <= mid)
	{
		query(left_child(t), l, r);
	} 
	else
	{
		query(left_child(t), l, mid);
		query(right_child(t), mid + 1, r);
	}
}

int main()
{
	int n = 0;	//元素数目
	int q = 0;  //查询次数

	//输入数据
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
	{
		cin >> A[i];
	}

	init();	//初始化线段树

	//建立以node[1]为根节点，区间为A[1, n]的线段树
	build(1, 1, n);

	while (q--)
	{
		int a = 0, b = 0;	//查询区间
		cin >> a  >> b;
		maxx = 0;
		minx = 1000010;
		query(1, a, b);		//查询最大值和最小值，保存在全局变量maxx和minx中
		cout << maxx - minx << endl;
	}
	return 0;
}


