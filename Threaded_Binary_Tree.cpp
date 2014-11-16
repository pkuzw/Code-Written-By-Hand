///@file Threaded_Binary_Tree
///@author zhaowei
///@date 2014.11.15
/* @note 二叉树中存在很多空指针，可以利用这些空指针，指向其前驱或者后继。这些利用起来的空指针称为线索，这种改进后的二叉树叫做线索二叉树。
		 一棵n个节点的二叉树含有n+1个空指针。这是因为，假设叶子节点数为n0，度为1的节点数为n1，度为2的节点数为n2，每个叶子节点有2个空指针，
		 每个度为1的节点有1个空指针，则空指针总数为2*n0 + n1，又有n0 = n2 + 1，因此指针总数为2n0 + n1 = n0 + n2 + 1 + n1 = n + 1.
		 在二叉树线索化过程中通常规定，若无左子树，另lchild指向前驱，若无右子树，则令rchild指向后继。此外，还需要两个额外的标志域来表示当前
		 指针是否是线索。例如ltag = 1表示lchild是前驱，ltag = 0表示lchild指向的是左孩子，rtag类似。
		 二叉树的线索化实质上就是遍历一棵树，只是在遍历的过程中，检查当前节点的左右指针是否为空，若为空，将它们改为指向前驱或后继的线索。
*/
#include <cstddef>	//for NULL
#include <iostream>

///@brief 节点数据类型
typedef int elem_t;

///@struct
///@brief 线索二叉树节点
typedef struct tbt_node_t
{
	int ltag;	//1：表示线索；0：表示孩子
	int rtag;	//1：表示线索；0：表示孩子
	tbt_node_t* lchild;	//左孩子指针
	tbt_node_t* rchild;	//右孩子指针
	elem_t data; //节点存放的数据
}tbt_node_t;

/*
静态成员函数用于访问私有静态成员变量。静态成员函数不依赖于任何对象，故导致：1.其没有this指针；2. 其只能访问静态成员变量，而不能访问其他非静态成员变量。
因为后者依赖于确定的对象。在使用静态成员函数的时候不需要初始化一个对象，通过对象来调用函数，只需要通过“类名::静态成员函数”就可以调用。另外，虽然通过某一对象
也能访问静态成员函数，但不推荐这么使用。
http://www.learncpp.com/cpp-tutorial/812-static-member-functions/
/////////////////////////////////
因为《手写代码》中该程序是纯c的代码，并未涉及c++中类的内容。故上述静态成员函数的知识与代码关系不大，属于自学。
/////////////////////////////////
*/
//内部函数
static void in_thread(tbt_node_t* p, tbt_node_t** pre);
static tbt_node_t* first(tbt_node_t* p);
static tbt_node_t* next(const tbt_node_t* p);

int main()
{
	return 0;
}