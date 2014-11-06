///@file Stack.cpp
///@brief C语言实现栈
///@author zhaowei
///@date 2014.11.03
///@version 1.0

#include <stdlib.h>	// for malloc()
#include <string.h>	// for memcpy()

typedef int stack_elem_t; //元素类型

///@struct
///@brief 栈的结构体
///@author zhaowei
///@date 2014.11.04

typedef struct stack_t
{
	int size;	//实际元素个数
	int capacity; //容量
	stack_elem_t* elems; //栈的数组
}stack_t;

///@brief 初始化栈
///@param[inout] s 栈对象的指针
///@param[in] capacity 初始容量
///@return 无
///@author zhaowei
///@date 2014.11.04
void stack_init(stack_t* s, const int capacity)
{
	s->size = 0;
	s->capacity = capacity;
	s->elems = (stack_elem_t*)malloc(capacity * sizeof(stack_elem_t));
}

///@brief 释放栈空间
///@param[inout] s 栈对象指针
///@return 无
///@author zhaowei
///@date 2014.11.04
void stack_uninit(stack_t* s)
{
	s->size = 0;
	s->capacity = 0;
	free(s->elems);
	s->elems = NULL;
}

///@brief 获取元素个数
///@param[in] s 栈对象
///@return 元素个数
///@author zhaowei
///@date 2014.11.05
int stack_size(const stack_t* s)
{
	return s->size;
}

///@brief 进栈
///@param[in] s 栈对象指针
///@param[in] x 准备进栈的元素
///@return 无
///@author zhaowei
///@date 2014.11.05
void stack_push(stack_t* s, const stack_elem_t x)
{
	if(s->size == s->capacity)
	{
		stack_elem_t* tmp = (stack_elem_t*)realloc(s->elems, s->capacity * 2 * sizeof(stack_elem_t));
		s->capacity *= 2;
		s->elems = tmp;
	}
	s->elems[s->size++] = x;
}

///@brief 弹出栈顶元素
///@param[in] s 栈对象指针
///@return 如果成功弹出栈顶元素，则返回true，否则返回false
///@author zhaowei
///@date 2014.11.05
bool stack_pop(stack_t* s)
{
	if(s->size == 0)
		return false;
	else
	{
		s->size--;
		return true;
	}
}

///@brief 获取栈顶元素
///@param[in] s 栈对象指针
///@return 栈顶元素
///@author zhaowei
///@date 2014.11.05
stack_elem_t stack_top(const stack_t* s)
{
	if(s->size)
	{
		return s->elems[s->size - 1];
	}
	else
		return INT_MAX;
}

int main()
{
	return 0;
}

