///@file 线段树练习
///@author zhaowei
///@date 2014.12.15
///@version 1.0
/* @note
描述
一行N(1  N < 100000) 个方格，开始每个格子里都有一个整数。现在动态地提出一些命令请求，有两种命令，查询和增加：求某一个特定的
子区间[a, b]中所有元素的和；指定某一个格子x，加上一个特定的值A。现在要求你能对每个请求作出正确的回答。

输入
输入文件第一行为一个整数N，接下来是n 行每行1 个整数，表示格子中原来的整数。接下来是一个正整数Q，再接下来有Q 行，表示Q 个询问，
第一个整数表示命令代号，命令代号1 表示增加，后面的两个数a 和x 表示给位置a 上的数值增加x，命令代号2 表示区间求和，后面两个整数
a 和b，表示要求[a,b] 之间的区间和。

输出
共Q 行，每个整数

样例输入
6
4
5
6
2
1
3
4
1
3 5
2 1 4
1 1 9
2 2 6

样例输出
22
22

本题来自 wikioi 1080 线段树练习
*/

#include <iostream>
#include <cstring>
using namespace std;

#define left_child(a) ((a) << 1)			//求线段树中节点a的左孩子
#define right_child(a) (((a) << 1) + 1)		//求线段树中节点a的右孩子
#define MAXN 100001


///@brief 线段树节点
typedef struct node_t
{
	int left, right;	//线段树节点所表示区间的左右边界
	int sum;		//区间内的和
}node_t;

int input[MAXN];	//输入数据，下标0处未使用

//线段树，完全二叉树，节点编号从1开始，层次从1开始，用一维数组存储，空间约为4 * MAXN
//参考：http://comzyh.com/blog/archives/479/
node_t interval_tree[MAXN * 4];	



///@brief 初始化线段树，将整个线段树数组置为0
///@return 
void init()
{
	memset(interval_tree, 0, sizeof(interval_tree));
}

///@brief 以t为根节点，为区间input[l, r]建立线段树
///@param[in] t 根节点所在的下标
///@param[in] l 区间的左边界
///@param[in] r 区间的右边界
///@return 
void build(int t, int l, int r)
{
	interval_tree[t].left = l;
	interval_tree[t].right = r;
	if(l == r)
	{
		interval_tree[t].sum = input[l];
		return;
	}
	int mid = (l + r) / 2;
	build(left_child(t), l, mid);
	build(right_child(t), mid + 1, r);
	interval_tree[t].sum = interval_tree[left_child(t)].sum + interval_tree[right_child(t)].sum;
	return;
}

///@brief 给区间input[l, r]里的pos位置添加delta
///@param[in] t 线段树的节点
///@param[in] l 区间的左边界
///@param[in] r 区间的右边界
///@param[in] pos 要添加的位置
///@param[in] delta 要添加的值
///@return 无
void add(int t, int l, int r, int pos, int delta)
{
	if (interval_tree[t].left > pos || interval_tree[t].right < pos)	
	{
		return;
	}
	if (interval_tree[t].left == interval_tree[t].right)
	{
		interval_tree[t].sum += delta;	//更新interval_tree[t]的和
		return;
	}

	//要更新的区间是否在左，是否在右，还是横跨两部分？
	int mid = (interval_tree[t].left + interval_tree[t].right) / 2;
	if (l > mid)
	{
		add(right_child(t), l, r, pos, delta);
	}
	else if (r <= mid)
	{
		add(left_child(t), l, r, pos, delta);
	}
	else
	{
		add(left_child(t), l, mid, pos, delta);
		add(right_child(t), mid + 1, r, pos, delta);
	}
	interval_tree[t].sum = interval_tree[left_child(t)].sum + interval_tree[right_child(t)].sum;
	return;
}

///@brief 查询根节点为t，区间为input[l, r]的和
///@param[in] t 线段树根节点
///@param[in] l 区间的左边界
///@param[in] r 区间的右边界
///@return
int query_sum(int t, int l, int r)
{
	if (interval_tree[t].left == l && interval_tree[t].right == r)
	{
		return interval_tree[t].sum;
	}
	int mid = (interval_tree[t].left + interval_tree[t].right) / 2;
	if (l > mid)
	{
		return query_sum(right_child(t), l, r);
	}
	else if (r <= mid)
	{
		return query_sum(left_child(t), l, r);
	}
	else
	{
		return query_sum(left_child(t), l, mid) + query_sum(right_child(t), mid + 1, r);
	}
}

int main()
{
	int n = 0;	//输入数据的规模
	int q = 0;	//查询次数
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> input[i];
	}

	init();
	build(1, 1, n);	//建立以interval_tree[1]为根节点的线段树

	cin >> q;
	while (q--)
	{
		int cmd_type = 0;
		cin >> cmd_type;
		if (cmd_type == 2)
		{
			int left = 0, right = 0;	//查询区间的边界
			cin >> left >> right;
			cout << query_sum(1, left, right);
			cout << endl;
		}
		else
		{
			int pos = 0;	//修改的值所在位置
			int delta = 0;	//新增加的值
			cin >> pos >> delta;
			if (delta != 0)
			{
				add(1, 1, n, pos, delta);
			}
		}
	}
	return 0;
}

