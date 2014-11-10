///@file Queue.cpp
///@brief 队列，顺序存储，循环队列
///@author zhaowei
///@date 2014.11.10
///@version 1.0

#include <cstdlib>	//for malloc(), free()
#include <cstring>	//for memcpy()

#ifndef __cplusplus
typedef char bool;
#define false 0
#define true 1
#endif

typedef int queue_elem_t;	//元素的类型

///@struct
///@brief 队列的结构体定义
///@note 无
typedef struct queue_t
{
	int front;	//队头
	int rear;	//队尾
	int capacity;	//队列容量
	queue_elem_t* elems;	//存放数据的内存块
}queue_t;

///@brief 初始化队列
///@param[out] 队列结构体的指针
///@param[in] capacity 初始容量
///@return 无
void queue_init(queue_t* q, const int capacity)
{
	q->front = 0;
	q->rear = 0;
	q->capacity = capacity;
	q->elems = (queue_elem_t*)malloc(capacity * sizeof(queue_elem_t));
}

///@brief 释放队列
///@param[inout] q 队列对象的指针
///@return 无
void queue_uninit(queue_t* q)
{
	q->front = 0;
	q->rear = 0;
	q->capacity = 0;
	free(q->elems);
	q->elems = NULL;
}

///@brief 判断队列是否为空
///@param[in] q 队列结构体的指针
///@return 如果队列为空，返回true；否则返回false
bool queue_empty(const queue_t* q)
{
	return q->front == q->rear;
}

///@brief 获取元素个数
///@param[in] s 栈对象的指针
///@return 元素个数
int queue_size(const queue_t* q)
{
	//因为队列为循环队列？所以需要加长取模
	return (q->rear - q->front + q->capacity) % q->capacity;
}

///@brief 在队尾添加元素
///@param[in] q 指向队列结构体的指针
///@param[in] x 要添加的元素
///@return 无
void queue_push(queue_t* q, const queue_elem_t x)
{
	//如果队列现有内存空间已满
	if((q->rear + 1) % q->capacity == q->front)
	{
		queue_elem_t* tmp = (queue_elem_t*)malloc(q->capacity * 2 * sizeof(queue_elem_t));
		//如果队首指针在队尾指针的前方
		if(q->front < q->rear)	
		{
			memcpy(tmp, q->elems + q->front, (q->rear - q->front) * sizeof(queue_elem_t));
		}
		//如果对手指针在队尾的后方
		else if(q->front > q->rear)
		{
			//将q->elms中q->front至末尾的元素先复制到新的内存空间前半部分
			memcpy(tmp, q->elems + q->front, (q->capacity - q->front) * sizeof(queue_elem_t));

			//将q->elms中开始至q->rear的元素先复制到新的内存空间后半部分
			memcpy(tmp + (q->capacity - q->front), q->elems, (q->rear * sizeof(queue_elem_t)));

			//重置rear和front
			q->rear += q->capacity - q->front; //等价于q->rear = q->capacity - 1
			q->front = 0;
		}
		free(q->elems);	//释放原有的内存空间
		q->elems = tmp;
		q->capacity *= 2;
	}
	q->elems[q->rear] = x;
	q->rear = (q->rear + 1) % q->capacity;	//因为是循环存储，所以注意取模
}

///@brief 获取队首元素
///@param[in] q 队列对象的指针
///@return 队首元素
queue_elem_t queue_front(const queue_t* q)
{
	return q->elems[q->front];
}

///@brief 获取队尾元素
///@param[in] q 队列对象的指针
///@return 队尾元素
queue_elem_t queue_rear(const queue_t* q)
{
	return q->elems[q->rear];
}

///@brief 弹出队首元素
///@param[in] q 队列指针
///@return 无
void queue_pop(queue_t* q)
{
	q->front = (q->front + 1) % q->capacity;
	return;
}
int main()
{
	return 0;
}