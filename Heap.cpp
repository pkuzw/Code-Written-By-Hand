///@file 最小堆的实现
///@author zhaowei
///@date 2014.11.27
///@version 1.0
/*@note 相当于C++中的priority_queue
		priority_queue使用时需要包含头文件<queue>，它能够提供类似最大堆的功能，其队首元素就是队列中的最大元素。
		priority_queue的主要方法有：
		empty()	Test whether container is empty

		size()	Return size 
		top()	Access top element 
		push()	Insert element 
		emplace() Construct and insert element
		pop()	Remove top element
		swap ()	Swap contents

*/


#include <cstdlib>	//for malloc() & free()
#include <cstring>	//for memcpy()


using namespace std;

typedef int heap_elem_t;	//元素类型

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
int cmp_int(const int *x, const int *y)
{
	const int sub = *x - *y;
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

int main()
{
	return 0;
}
