//@file Stack.cpp
//@brief C语言实现栈
//@author zhaowei
//@date 2014.11.03
//@version 1.0

#include <stdlib.h>	// for malloc()
#include <string.h>	// for memcpy()

typedef int stack_elem_t; //元素类型

//@struct
//@brief 栈的结构体

typedef struct stack_t
{
	int size;	//实际元素个数
	int capacity; //容量
	stack_elem_t* elems; //栈的数组
}stack_t;

//@brief 初始化栈
//@param[inout] s 栈对象的指针
//@param[in] capacity 初始容量
//@return 无
void stack_init(stack_t* s, const int capacity)
{
	s->size = 0;
	s->capacity = capacity;
	s->elems = (stack_elem_t*)malloc(capacity * sizeof(stack_elem_t));
}

//@brief 释放栈空间
//@param[inout] s 栈对象指针
//@return 无
void stack_uninit(stack_t* s)
{
	s->size = 0;
	s->capacity = 0;
	free(s->elems);
	s->elems = NULL;
}
