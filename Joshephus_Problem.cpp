///@file 约瑟夫问题
///@author zhaowei
///@date 2014.12.20
///@version 1.0
/* @note
   描述
   有编号从1到N的N个小朋友在玩一种出圈的游戏。开始时N个小朋友围成一圈，编号为
   i+1的小朋友站在编号为i小朋友左边。编号为1的小朋友站在编号为N的小朋友左边。首先编号
   为1的小朋友开始报数，接着站在左边的小朋友顺序报数，直到数到某个数字M时就出圈。直到
   只剩下1个小朋友，则游戏完毕。现在给定N，M，求N个小朋友的出圈顺序。

   输入
   唯一的一行包含两个整数N，M(1 <= N，M <= 30000)。

   输出
   唯一的一行包含N个整数，每两个整数中间用空格隔开，第i个整数表示第i个出圈的小朋友的编号。
   
   样例输入
   5 3

   样例输出
   3 1 5 2 4

   分析
   约瑟夫问题的难点在于，每一轮都不能通过简单的运算得出下一轮谁淘汰，因为中间有人已经
   退出了。因此一般只能模拟，效率很低。
   现在考虑，每一轮都令所有剩下的人从左到右重新编号，例如3 退出后，场上还剩下1、2、4、
   5，则给1 新编号1，2 新编号2，4 新编号3，5 新编号4。不妨称这个编号为“剩余队列编号”。如下所示，
   括号内为原始编号：
   1(1) 2(2) 3(3) 4(4) 5(5) --> 剩余队列编号3 淘汰，对应原编号3
   1(1) 2(2) 3(4) 4(5) --> 剩余队列编号1 淘汰，对应原编号1
   1(2) 2(4) 3(5) --> 剩余队列编号3 淘汰，对应原编号5
   1(2) 2(4) --> 剩余队列编号1 淘汰，对应原编号2
   1(4) --> 剩余队列编号1 淘汰，对应原编号4
   一个人在当前剩余队列中编号为i，则说明他是从左到右数第i 个人，这启发我们可以用线段树
   来解决问题。用线段树维护原编号[i..j] 内还有多少人没有被淘汰，这样每次选出被淘汰者后，在当
   前线段树中查找位置就可以了。
   例如我们有5个原编号，当前淘汰者在剩余队列中编号为3，先看左子树，即原编号[1..3] 区间
   内，如果剩下的人不足3个，则说明当前剩余编号为3的这个人原编号只能是在[4..5] 区间内，继续
   在[4..5]上搜索；如果[1..3] 内剩下的人大于等于3 个，则说明就在[1..3] 内，也继续缩小范围查找，
   这样即可在O(logN) 时间内完成对应。问题得到圆满的解决。

   本题目来自wikioi 1282 约瑟夫问题
*/

#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 30001
#define LCHILD(a) (a << 1)
#define RCHILD(a) ((a << 1) + 1)

typedef struct node_t
{
	int left, right;	//区间的左右边界
	int count;			//区间内元素的个数
}node_t;

node_t seg_tree[MAXN * 4];

///@brief 初始化线段树
///@return 无
void init()
{
	memset(seg_tree, 0, sizeof(seg_tree));
}

///@brief 以t为根节点，构造线段树
///@param[in] t 线段树根节点
///@param[in] l 线段树左边界
///@param[in] r 线段树右边界
///@return 无
void build(int t, int l, int r)
{
	seg_tree[t].left = l;
	seg_tree[t].right = r;
	seg_tree[t].count = r - l + 1;
	if (l == r) 
		return;

	int mid = (l + r) / 2;
	build(LCHILD(t), l, mid);
	build(RCHILD(t), mid + 1, r);
	return;
}

///@brief 输出每一轮被淘汰的元素编号
///@param[in] t 线段树根节点
///@param[in] i 要被淘汰的元素在剩余队列中的编号
///@return 被淘汰的元素的编号
int kick_out(int t, int i)
{
	seg_tree[t].count--;	//先将线段树中元素数目自减1
	if (seg_tree[t].left == seg_tree[t].right)
	{
		cout << seg_tree[t].left << ' ';
		return seg_tree[t].left;
	}
	if (seg_tree[LCHILD(t)].count >= i)
	{
		return kick_out(LCHILD(t), i);
	} 
	else
	{
		return kick_out(RCHILD(t), i - seg_tree[LCHILD(t)].count);
	}
}

///@brief 计算1到i内活着的人数
///@param[in] t 根节点
///@param[in] i 原始队列的数字
///@return 1到i内活的人数
int get_count(int t, int i)
{
	if (seg_tree[t].right <= i)
	{
		return seg_tree[t].count;
	}

	int mid = (seg_tree[t].left + seg_tree[t].right) / 2;
	int s = 0;
	if (i > mid)
	{
		s += seg_tree[LCHILD(t)].count;
		s += get_count(RCHILD(t), i);
	} 
	else
	{
		s += get_count(LCHILD(t), i);
	}
	return s;
}

int main()
{
	int n = 0;	//总人数
	int m = 0;	//每一轮淘汰的编号

	cin >> n >> m;
	init();
	build(1, 1, n);

	int virtual_index = 0;	//每一轮的虚拟编号
	for (int i = 1; i <= n; i++)
	{
		virtual_index += m;
		if (virtual_index > seg_tree[1].count)
		{
			virtual_index %= seg_tree[1].count;
		}
		if (virtual_index == 0)
		{
			virtual_index = seg_tree[1].count;
		}

		//每一轮淘汰掉一个元素
		int k = kick_out(1, virtual_index);

		//获得下一轮要被淘汰掉的元素的虚拟编号的起始计算点
		virtual_index = get_count(1, k);
	}
	cout << endl;
	return 0;
}



