///@file 有两个长度为N的序列A和B，在A和B中各取一个数可以得到N^2个和，求这N^2个和中最小的N个
///@author zhaowei
///@date 2014.11.30
///@version 1.0
/*@note 
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

由于数据量是N^2，如果用朴素的先求和再排序的方法来解决，时间复杂度是O(n^2lgn)，会比较费时。采用堆来解决该问题。
首先将A，B两数组排序，我们可以建立如下的有序表：
A1 + B1 < A1 + B2 < A1 + B3 < ... < A1 + Bn
A2 + B1 < A2 + B2 < A2 + B3 < ... < A2 + Bn
... ...
An + B1 < An + B2 < An + B3 < ... < An + Bn
先将A[i] + B[0]压入堆中，设每次出堆的元素为sum = A[a] + B[b]，则将A[a] + B[b + 1]入堆，这样可以保证前n个出堆的元素为最小的前n项。
在实现的时候可以不用保存B数组的下标，通过sum - B[b] + B[b + 1]来替换A[a] + B[b + 1]，这样能够节省空间

*/

#include <cstdlib>	//for qsort(); malloc()
#include <iostream>	
#include <cstring>	//for memcpy()

using namespace std;


#define  MAXN 100000
int N;
int a[MAXN], b[MAXN];

typedef struct node_t
{
	int sum;	//sum = a[i] + b[b]
	int b;		//表示当前sum使用的b数组的下标
}node_t;

typedef node_t heap_elem_t;

//使用Heap.cpp中有关堆的定义和操作
///@struct
///@brief 堆的结构体
typedef struct heap_t
{
	int size;		//堆中实际元素个数
	int capacity;	//堆的容量
	heap_elem_t *elems;	//堆的数组
	int (*cmp)(const heap_elem_t*, const heap_elem_t*);	//元素的比较函数
}heap_t;

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

///@brief 堆的初始化
///@param[inout] h 堆对象的指针
///@param[in] capacity 初始容量
///@param[in] cmp 比较函数
///@return 如果初始化成功，返回0；否则返回错误码
int  heap_init(heap_t *h, const int capacity, int (*cmp)(const heap_elem_t*, const heap_elem_t*))
{
	h->size = 0;
	h->capacity = capacity;
	h->elems = (heap_elem_t *)malloc(capacity * sizeof(heap_elem_t));
	h->cmp = cmp;

	return 0;
}

///@brief 释放堆
///@param[inout] h 堆对象的指针
///@return 释放成功则返回0，否则返回错误码
int heap_uninit(heap_t *h)
{
	h->size = 0;
	h->capacity = 0;
	free(h->elems);
	h->elems = NULL;	//free()清除的是elems指向的堆空间，之后为了防止elems指向别的内存空间，应该将它置为空
	h->cmp = NULL;
	return 0;
}

///@brief 判断堆是否为空
///@param[in] h 堆指针
///@return 如果堆为空，返回true；否则返回false
bool heap_empty(const heap_t *h)
{
	if (h->size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

///@brief 获取堆的元素数目
///@param[in] h 堆指针
///@return 返回堆的元素数目
int heap_size(heap_t *h)
{
	return h->size;
}

///@brief 最小堆的自上向下筛选算法
///@param[in] h 堆对象的指针
///@param[in] start 开始筛选的节点
///@return 无
/* @note 堆可以看做是完全二叉树，即每片叶子节点具有相同的深度，每个内部节点的度均为2.
		 最大堆满足性质：A[parent(i)] >= A[i]；
		 最小堆满足性质：A[parent(i)] <= A[i]；其中i为存放堆节点的下标

*/
void heap_sift_down(const heap_t *h, const int start)
{
	int i = start;
	int j = 0;
	const heap_elem_t tmp = h->elems[start];

	//j = 2 * i + 1适用于根节点标号为0而非1的情形，j表示i的左孩子，j + 1表示右孩子
	for (j = 2 * i + 1; j < h->size; j = 2 * j + 1)
	{
		if (j < (h->size - 1) && 
			h->cmp(&(h->elems[j]), &(h->elems[j + 1])) > 0) 
		{
			j++;	//j指向两子女中较小者
		}
		if (h->cmp(&tmp, &(h->elems[j])) <= 0)//如果当前节点比其孩子节点小
		{
			break;	//那么就算找到了当前节点应该放置的位置，跳出循环
		}
		else		//如果当前节点比其孩子节点中较小的节点大
		{
			h->elems[i] = h->elems[j];	//将较小的孩子节点值赋给当前节点
			i = j;						//并将当前节点更新为较小的孩子节点
		}
	}
	h->elems[i] = tmp;//当循环完毕后，将当前节点的值改为开始的节点值
}

///@brief 最小堆自下向上筛选算法
///@param[in] h 堆对象指针
///@param[in] start 开始节点
///@return 无
void heap_sift_up(const heap_t *h, const int start)
{
	int j = start;			//起始节点下标
	int i = (j - 1) / 2;	//起始节点的父节点下标
	const heap_elem_t tmp = h->elems[start];
	while (j > 0)
	{
		if (h->cmp(&(h->elems[i]), &tmp) <= 0)	//如果起始节点值不超过父节点值，则说明已满足最小堆性质，跳出循环
		{
			break;
		} 
		else	//如果起始节点值大于父节点值
		{
			//则将父节点赋给其子节点
			h->elems[j] = h->elems[i];
			j = i;
			i = (i - 1) / 2;	//同时将i更新为父节点的父节点
		}
		h->elems[j] = tmp;	//将原先的子节点值赋给父节点
	}
}

///@brief 添加一个元素
///@param[in] h 堆对象的指针
///@param[in] x 要添加的元素
///@return 无
void heap_push(heap_t *h, const heap_elem_t x)
{
	if (h->size == h->capacity)	//如果已分配的内存空间已满，则重新分配内存空间
	{
		heap_elem_t *tmp = (heap_elem_t*)realloc(h->elems, h->capacity * 2 * sizeof(heap_elem_t));
		h->elems = tmp;
		h->capacity *= 2; 
	}

	h->elems[h->size] = x;	//插入新元素
	h->size++;				//调整当前元素数目

	heap_sift_up(h, h->size - 1);	//将新元素sift_up
}

///@brief 弹出堆顶元素
///@param[in] h 堆对象指针
///@return 无
void heap_pop(heap_t *h)
{
	h->elems[0] = h->elems[h->size - 1];	//将最后一个元素放入堆顶
	h->size--;								//更新堆中当前元素数目
	heap_sift_down(h, 0);					//维护最小堆
}

///@brief 获取堆顶元素
///@param[in] h 堆对象指针
///@return 堆顶元素
heap_elem_t heap_top(heap_t *h)
{
	return h->elems[0];
}

///@brief 堆节点的比较函数
///@param[in] a 待比较节点A
///@param[in] b 待比较节点B
///@return 如果两节点值相同，返回0；如果A较大，返回1；如果B较大，返回-1
int cmp_node(const heap_elem_t *a, const heap_elem_t *b)
{
	const int sub = a->sum - b->sum;
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

///@brief 找出前N个小的和
///@return 无
/* @note 如果使用比较朴素的方法，先算出所有的和，一共有N^2个，然后排序，则时间复杂度是O(N^2logN)；空间复杂度是O(N^2)
		 采用堆的办法的话，先对两个子序列进行排序，时间复杂度是O(NlogN)，因为排序后A1 + B1肯定是最小的和，这时候先将A[i] + B[0]都放入堆中，
		 占用O(N)的空间复杂度。最小对顶元素应该是A[0] + B[0]，弹出堆顶元素(heap_sift_down调整)，然后将A[0] + B[1]入堆，经过heap_sift_up调整，
		 得到的堆顶元素A[i] + B[j]应该是第二小的和，继续弹出堆顶，并加入A[i] + B[j + 1]，这样经过N次出堆和入堆操作，就能够得到前N小的和，时间
		 复杂度为O(NlogN)，空间复杂度为O(N)
*/
void k_merge()
{
	heap_t h;
	node_t tmp;

	qsort(a, N, sizeof(int), cmp_int);	//先对子序列排序
	qsort(b, N, sizeof(int), cmp_int);
	heap_init(&h, N, cmp_node);

	//将最初的N个和入堆
	for (int i = 0; i < N; i++)
	{
		tmp.sum = a[i] + b[0];
		tmp.b = 0;
		heap_push(&h, tmp);
	}

	//选出最小的前N个和
	for (int i = 0; i < N; i++)
	{
		tmp = heap_top(&h);
		heap_pop(&h);	
		cout << tmp.sum << " ";

		tmp.sum = tmp.sum - b[tmp.b] + b[tmp.b + 1];	//得到a[i] + b[j+1]的另一种方式。否则就需要使用更多的空间来存储每一个和的下一个a[i] + b[j+1]
		tmp.b++;
		heap_push(&h, tmp);
	}

	heap_uninit(&h);
	return;
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





