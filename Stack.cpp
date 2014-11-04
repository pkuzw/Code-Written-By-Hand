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

typedef struct stack_t {
	int size;	//实际元素个数
	int capacity; //容量
	stack_elem_t* elems; //栈的数组
}stack_t;