///@file Threaded_Binary_Tree
///@author zhaowei
///@date 2014.11.15
/* @note 二叉树中存在很多空指针，可以利用这些空指针，指向其前驱或者后继。这些利用起来的空指针称为线索，这种改进后的二叉树叫做线索二叉树。
		 
		 一棵n个节点的二叉树含有n+1个空指针。这是因为，假设叶子节点数为n0，度为1的节点数为n1，度为2的节点数为n2，每个叶子节点有2个空指针，
		 每个度为1的节点有1个空指针，则空指针总数为2*n0 + n1，又有n0 = n2 + 1，因此指针总数为2n0 + n1 = n0 + n2 + 1 + n1 = n + 1.
		 
		 在二叉树线索化过程中通常规定，若无左子树，另lchild指向前驱，若无右子树，则令rchild指向后继。此外，还需要两个额外的标志域来表示当前
		 指针是否是线索。例如ltag = 1表示lchild是前驱，ltag = 0表示lchild指向的是左孩子，rtag类似。
		 
		 二叉树的线索化实质上就是遍历一棵树，只是在遍历的过程中，检查当前节点的左右指针是否为空，若为空，将它们改为指向前驱或后继的线索。
		 
		 线索二叉树主要用于中序遍历，因为其比传统二叉树的中序遍历递归算法更快。
		 
	//	 在中序线索的基础上稍加修改可以得到先序和后序线索二叉树。
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

///@brief 建立中序线索二叉树
///@param[in] root 树根
///@return 无
void create_in_thread(tbt_node_t* root)
{
	tbt_node_t* pre = NULL;	//前驱节点指针
	if(root != NULL)
	{
		in_thread(root, &pre);	//中序遍历线索化二叉树

		//处理中序中最后一个节点
		pre->rchild = NULL;
		pre->rtag = 1;
	}
}

///@brief 在中序线索二叉树上执行中序遍历
///@param[in] root
///@param[in] visit 访问节点的数据的函数
///@return 无
void in_order(tbt_node_t* root, int(*visit)(elem_t*))
{
	tbt_node_t* p;
	for(p = first(root); p != NULL; p = next(p))
	{
		(void)visit(&(p->data));
	}
}

///@brief 中序线索化二叉树的主过程
///@param[in] p 当前要处理的节点
///@param[inout] pre 当前节点的前驱节点
///@return 无
static void in_thread(tbt_node_t* p, tbt_node_t** pre)
{
	if(p != NULL)
	{
		in_thread(p->lchild, pre);	//线索化左子树
		if(p->lchild == NULL)	//左子树为空，建立前驱
		{
			p->lchild = *pre;
			p->ltag = 1;
		}

		//建立前驱节点的后继线索
		if((*pre) != NULL && (*pre)->rchild == NULL)
		{
			(*pre)->rchild = p;
			(*pre)->rtag = 1;
		}
		*pre = p;	//更新前驱
		in_thread(p->rchild, pre);	//线索化右子树
	}
}

///@brief 寻找线索二叉树的中序下的第一个节点
///@param[in] p 线索二叉树的任意节点
///@return 此线索二叉树的第一个节点
static tbt_node_t* first(tbt_node_t* p)
{
	if(p = NULL)
		return NULL;
	while (p->ltag == 0)
	{
		p = p->lchild;	//最左下节点，不一定是叶节点。因为中序遍历的第一个节点一定是最左下的节点
	}
	return p;
}

///@brief 求中序线索二叉树中某节点的后继
///@param[in] p 某节点
///@return p的后继
static tbt_node_t* next(const tbt_node_t* p)
{
	if(p->rtag == 0)	//如果右孩子存在
		return first(p->rchild);	//why??	
									//因为按照中序遍历的定义，对于右子树的遍历应该最先访问的是右子树最左下角节点，即p->rchild的前驱节点
	else
		return p->rchild;
}
int main()
{
	return 0;
}