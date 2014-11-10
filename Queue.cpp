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

int main()
{
	return 0;
}