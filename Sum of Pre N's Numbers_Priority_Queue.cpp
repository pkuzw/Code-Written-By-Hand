///@file 有两个长度为N的序列A和B，在A和B中各取一个数可以得到N^2个和，求这N^2个和中最小的N个
///@author zhaowei
///@date 2014.11.30
///@version 1.0
/* @note 
输入
第一行输入一个正整数N；第二行N 个整数Ai 且Ai  109；第三行N 个整数Bi，且Bi  109。

输出
输出仅一行，包含N 个整数，从小到大输出这N 个最小的和，相邻数字之间用空格
隔开。

样例输入
51
3 2 4 5
6 3 4 1 7

样例输出
2 3 4 4 5
*/
#include <cstdlib>	//for qsort(); malloc()
#include <cstring>	//for memcpy()
#include <queue>
#include <iostream>	

using namespace std;


#define MAXN 100000
int N;
int a[MAXN], b[MAXN];

typedef struct node_t
{
	int sum;	//sum = a[i] + b[b]
	int b;		//表示当前sum使用的b数组的下标
}node_t;

///@brief 整型的比较函数
///@param[in] x 待比较变量x
///@param[in] y 待比较变量y
///@return 如果两个变量相等，返回0；如果x较大；返回1，如果y较大，返回-1
int cmp_int(const void *x, const void *y)
{
	const int sub = *(int*)x - *(int*)y;
	if (sub > 0)
	{
		return 1;
	}
	else if (sub < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

///@brief 重载运算符>
///@param[in] a 待比较的自定义类型形参a
///@param[in] b 待比较的自定义类型形参b
///@return 如果a.sum > b.sum，则返回true；否则返回false
bool operator>(node_t a, node_t b)
{
	if (a.sum > b.sum ) 
		return true;
	else
		return false;
}

///@brief 找出前N小的和
///@return 无
///@note C++中的priority_queue默认是最大堆，如果要使用最小堆的话需要写全三个参数，第一个参数是队列元素类型；第二个是用于保存队列
//		 元素的容器，可以是vector或者deque，但不能是list；第三个就是元素的比较函数，这里需要重载运算符>
void k_merge()
{
	
	priority_queue< node_t, vector<node_t>, greater<node_t> > min_heap;
	node_t tmp;

	qsort(a, N, sizeof(int), cmp_int);	//先对子序列排序
	qsort(b, N, sizeof(int), cmp_int);

	//将最初的N个和入队
	for (int i = 0; i < N; i++)
	{
		tmp.sum = a[i] + b[0];
		tmp.b = 0;
		min_heap.push(tmp);	//从队尾入队
	}

	//选出最小的前N个和
	for (int i = 0; i < N; i++)
	{
		tmp = min_heap.top();
		min_heap.pop();		//从队首出队
		cout << tmp.sum << " ";

		tmp.sum = tmp.sum - b[tmp.b] + b[tmp.b + 1];	//得到a[i] + b[j+1]的另一种方式。否则就需要使用更多的空间来存储每一个和的下一个a[i] + b[j+1]
		tmp.b++;
		min_heap.push(tmp);
	}
}

int main()
{
	//测试
	cout << "Input N: " << endl;
	cin >> N;
	cout << endl;

	cout << "Input array A: " << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> a[i];
	}
	cout << endl;

	cout << "Input array B: " << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> b[i];
	}
	cout << endl;

	cout << "Output pre N's sum: " << endl;
	k_merge();
	cout << endl;
	return 0;
}