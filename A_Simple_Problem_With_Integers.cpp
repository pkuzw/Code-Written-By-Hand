///@file A simple problem with integers
///@author zhaowei
///@date 2014.12.18
///@version 1.0
/* @note
   ����
   ����N��������1 <= N <= 10,0000�������������ֲ���Q��C��
   ����"Q a b"��ʾ��ѯA[a, b]֮��ĺͣ�
   ����"C a b c"��ʾ������A[a, b]�ϵ�������������c��

   ����
   ��һ��������N��Q����ʾ��������Ŀ�Ͳ����Ĵ�����1 <= N, Q <= 10,0000
   �ڶ�����N��������A[i]�ķ�Χ��-1,000,000,000 <= A[i] <= 1,000,000,000
   ������Q����Q�β�����

   ���
   �ش�����"Q"������ÿ���ش���һ��

   ��������
   10 5
   1 2 3 4 5 6 7 8 9 10
   Q 4 4
   Q 1 10
   Q 2 4
   C 3 6 3
   Q 2 4

   �������
   4
   55
   9
   15

   ��ʾ
   ����֮���п��ܳ���32λ�����ı�ʾ��Χ

   ����������POJ 3239 & 3439�������WA��
*/

#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100001
#define L_CHILD(a) (a << 1)	//���߶����ڵ�a������
#define R_CHILD(a) ((a << 1) + 1)	//���߶����ڵ�a���Һ���

typedef long long int64_t;	//�Զ�������ʱ��typedef�ؼ��֣�������#define���������������

///@brief �����߶����ڵ�
typedef struct node_t	//�Զ���ڵ��ʱ����Ҫ��struct�ؼ���
{
	int left, right;	//�������߽�
	int64_t sum;		//����ĺ�
	int64_t inc;		//���������
}node_t;

int64_t input[MAXN];	//��λ��δ��

node_t seg_tree[MAXN * 4];

///@brief ��ʼ���߶���
///@return ��
void init()
{
	memset(seg_tree, 0, sizeof(seg_tree));
}

///@brief ��tΪ���ڵ㣬��input[l, r]Ϊ���乹���߶���
///@param[in] t ���ڵ�
///@param[in] l �������߽�
///@param[in] r ������ұ߽�
///@return ��
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

///@brief ������input[l, r]�ϵ�ÿһ��Ԫ�ؼ�c
///@param[in] t �߶����Ľڵ�
///@param[in] l �������߽�
///@param[in] r ������ұ߽�
///@param[in] inc ���ӵ�ֵ
///@return ��
void increase(int t, int l, int r, int64_t inc)
{
	if (seg_tree[t].left == l && seg_tree[t].right == r)
	{
		seg_tree[t].inc += inc;
		seg_tree[t].sum += inc * (r - l + 1);
		return;
	}

	//��������߶����ڸýڵ����������û�й��㣬Ӧ�ý�������ӽڵ������������
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

///@brief ��ѯ�߶����ڵ�Ϊt������Ϊinput[l, r]�ĺ�
///@param[in] t �߶������ڵ�
///@param[in] l �������߽�
///@param[in] r ������ұ߽�
///@return ��������ĺ�
int64_t query(int t, int l, int r)
{
	if (seg_tree[t].left == l && seg_tree[t].right == r)
	{
		return seg_tree[t].sum;
	}

	//��������߶����ڸýڵ����������û�й��㣬Ӧ�ý�������ӽڵ������������
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