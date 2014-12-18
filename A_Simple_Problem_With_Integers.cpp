///@file A simple problem with integers
///@author zhaowei
///@date 2014.12.18
///@version 1.0
/* @note
   描述
   给定N个整数（1 <= N <= 10,0000），其上有两种操作Q和C。
   操作"Q a b"表示查询A[a, b]之间的和；
   操作"C a b c"表示将区间A[a, b]上的所有数都加上c。

   输入
   第一行是整数N和Q，表示整数的数目和操作的次数。1 <= N, Q <= 10,0000
   第二行是N个整数，A[i]的范围是-1,000,000,000 <= A[i] <= 1,000,000,000
   接下来Q行是Q次操作；

   输出
   回答所有"Q"操作，每个回答是一行

   样例输入
   10 5
   1 2 3 4 5 6 7 8 9 10
   Q 4 4
   Q 1 10
   Q 2 4
   C 3 6 3
   Q 2 4

   样例输出
   4
   55
   9
   15

   提示
   区间之和有可能超过32位整数的表示范围

   本题来自于POJ 3239 & 3439，结果是WA。
*/

#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100001
#define L_CHILD(a) (a << 1)	//求线段树节点a的左孩子
#define R_CHILD(a) ((a << 1) + 1)	//求线段树节点a的右孩子

typedef long long int64_t;	//自定义类型时用typedef关键字，而不是#define，后者用来定义宏

///@brief 定义线段树节点
typedef struct node_t	//自定义节点的时候需要有struct关键字
{
	int left, right;	//区间的左边界
	int64_t sum;		//区间的和
	int64_t inc;		//区间的增量
}node_t;

int64_t input[MAXN];	//零位置未用

node_t seg_tree[MAXN * 4];

///@brief 初始化线段树
///@return 无
void init()
{
	memset(seg_tree, 0, sizeof(seg_tree));
}

///@brief 以t为根节点，以input[l, r]为区间构建线段树
///@param[in] t 根节点
///@param[in] l 数组的左边界
///@param[in] r 数组的右边界
///@return 无
void build(int t, int l, int r)
{
	seg_tree[t].left = l;
	seg_tree[t].right = r;
	if (l == r)
	{
		seg_tree[t].sum = input[l];
		return;
	}

	int mid = (l + r) / 2;
	build(L_CHILD(t), l, mid);
	build(R_CHILD(t), mid + 1, r);
	seg_tree[t].sum = seg_tree[L_CHILD(t)].sum + seg_tree[R_CHILD(t)].sum;
}

///@brief 给区间input[l, r]上的每一个元素加c
///@param[in] t 线段树的节点
///@param[in] l 区间的左边界
///@param[in] r 区间的右边界
///@param[in] inc 增加的值
///@return 无
void increase(int t, int l, int r, int64_t inc)
{
	if (seg_tree[t].left == l && seg_tree[t].right == r)
	{
		seg_tree[t].inc += inc;
		seg_tree[t].sum += inc * (r - l + 1);
		return;
	}

	//！！如果线段树在该节点出还有增量没有归零，应该将其加入子节点的增量并归零
	if (seg_tree[t].inc)
	{
		seg_tree[L_CHILD(t)].inc += inc;
		seg_tree[R_CHILD(t)].inc += inc;
		seg_tree[L_CHILD(t)].sum += inc * (seg_tree[L_CHILD(t)].right - seg_tree[L_CHILD(t)].left + 1);
		seg_tree[R_CHILD(t)].sum += inc * (seg_tree[R_CHILD(t)].right - seg_tree[R_CHILD(t)].left + 1);
		seg_tree[t].inc = 0;
	}

	int mid = (seg_tree[t].left + seg_tree[t].right) / 2;

	if (l > mid)
	{
		increase(R_CHILD(t), l, r, inc);
	}
	else if (r <= mid)
	{
		increase(L_CHILD(t), l, r, inc);
	}
	else
	{
		increase(L_CHILD(t), l, mid, inc);
		increase(R_CHILD(t), mid + 1, r, inc);
	}
	seg_tree[t].sum = seg_tree[L_CHILD(t)].sum + seg_tree[R_CHILD(t)].sum;
}

///@brief 查询线段树节点为t，区间为input[l, r]的和
///@param[in] t 线段树根节点
///@param[in] l 区间的左边界
///@param[in] r 区间的右边界
///@return 返回区间的和
int64_t query(int t, int l, int r)
{
	if (seg_tree[t].left == l && seg_tree[t].right == r)
	{
		return seg_tree[t].sum;
	}

	//！！如果线段树在该节点出还有增量没有归零，应该将其加入子节点的增量并归零
	if (seg_tree[t].inc)
	{
		seg_tree[L_CHILD(t)].inc += seg_tree[t].inc;
		seg_tree[R_CHILD(t)].inc += seg_tree[t].inc;
		seg_tree[L_CHILD(t)].sum += seg_tree[t].inc * (seg_tree[L_CHILD(t)].right - seg_tree[L_CHILD(t)].left + 1);
		seg_tree[R_CHILD(t)].sum += seg_tree[t].inc * (seg_tree[R_CHILD(t)].right - seg_tree[R_CHILD(t)].left + 1);
		seg_tree[t].inc = 0;
	}

	int mid = (seg_tree[t].left + seg_tree[t].right) / 2;
	if (l > mid)
	{
		return query(R_CHILD(t), l, r);
	}
	else if (r <= mid)
	{
		return query(L_CHILD(t), l, r);
	}
	else
	{
		return query(L_CHILD(t), l, mid) + query(R_CHILD(t), mid + 1, r);
	}
}
int main()
{
	int n = 0, q = 0;
	cin >> n >> q;

	for (int i = 1; i < n + 1; i++)
	{
		cin >> input[i];
	}
	init();
	build(1, 1, n);

	char op_type = '\0';
	int l = 0, r = 0;
	int64_t inc = 0;
	while (q--)
	{
		cin >> op_type;
		if (op_type == 'C')
		{
			cin >> l >> r >> inc;
			increase(1, l, r, inc);
		} 
		else
		{
			cin >> l >> r;
			cout << query(1, l, r) << endl;
		}
	}
	return 0;
	

}