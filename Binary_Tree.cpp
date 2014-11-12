///@file 二叉树的遍历
///@author zhaowei
///@date 2014.11.12
/*@note 
		二叉树的前序遍历：根节点在其左右子树之前输出；
		二叉树的中序遍历：根节点在其左右子树之间输出；
		二叉树的后序遍历：根节点在其左右子树之后输出；
		在中序遍历中，一个节点的前驱，是其左子树的最右下角节点；后继是其右子树的最左下角节点
		在后序遍历中，若节点是根节点，则后继为空；
		若节点是双亲的右子树，或是左子树但双亲无右子树，则其后继为双亲节点；
		若节点是双亲的左子树且双亲有右子树，则其后继为右子树按后序遍历的第一个节点
*/

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

///@struct
///@brief 二叉树节点
typedef struct binary_tree_node_t
{
	binary_tree_node_t* lchild;	//左孩子
	binary_tree_node_t* rchild;	//右孩子
	void* data;	//节点数据
}binary_tree_node_t;

///@brief 先序遍历，递归版
///@param[in] root 根节点
///@param[in] visit 访问数据元素的函数指针
///@return 无
/*@note	学习了一下什么是函数指针。
		1. 函数指针就是指向函数的指针，它能够在返回值、参数类型和个数均相同的情况下被赋值。
		2. 函数指针最主要的作用是提高代码的复用。
		3. int (*foo)(int, double);就是一个名为foo，返回值类型为int，形参为int和double的函数指针。其中第一个括号不能省略，否则
		回来带歧义，变成了返回值为int*的函数foo。
		4. typedef bool (*pfcnValidate)(int, int); 是将pfcnValiadate变为一个别名。起到增加易读性的作用。例如将
			bool Validate(int nX, int nY, bool (*pfcn)(int, int)); 变为 bool Validate(int nX, int nY, pfcnValidate pfcn);
*/	
void pre_order_r(const binary_tree_node_t* root, int (*visit)(void*))
{
	if(root != NULL)
	{
		(void)visit(root->data);	//由于形参中visit的返回值是int型，而在binary_tree_node_t的定义中data又为void*型，故这里强制转换为void。根据实际情况可以更改。
		pre_order_r(root->lchild, visit);
		pre_order_r(root->rchild, visit);
	}
}

///@brief 中序遍历，递归版
///@param[in] root 根节点
///@param[in] visit 访问数据元素的函数指针
///@return 无
void in_order_r(const binary_tree_node_t* root, int (*visit)(void*))
{
	if(root != NULL)
	{
		in_order_r(root->lchild, visit);
		(void)visit(root->data);	//由于形参中visit的返回值是int型，而在binary_tree_node_t的定义中data又为void*型，故这里强制转换为void。根据实际情况可以更改。
		in_order_r(root->rchild, visit);
	}
}

///@brief 后序遍历，递归版
///@param[in] root 根节点
///@param[in] visit 访问数据元素的函数指针
///@return 无
void post_order_r(const binary_tree_node_t* root, int (*visit)(void*))
{
	if(root != NULL)
	{
		post_order_r(root->lchild, visit);
		post_order_r(root->rchild, visit);
		(void)visit(root->data);
	}
}

///@brief 先序遍历，迭代版
///@param[in] root 根节点
///@param[in] visit 访问数据元素的函数指针
///@return 无
void pre_order(const binary_tree_node_t* root, int (*visit)(void*))
{
	const binary_tree_node_t* p;
	stack<const binary_tree_node_t*> s;

	p = root;	//先将根节点入栈
	if(p != NULL)
	{
		s.push(p);
	}

	while(!s.empty())	
	{
		//取出栈顶元素，并访问其中数据
		p = s.top();
		s.pop();
		(void)visit(p->data);

		//先将右子树节点入栈，后将左子树节点入栈。根据栈的FILO原则，会先出栈左子树节点，后出栈右子树节点。
		if(p->rchild != NULL)
			s.push(p->rchild);

		if(p->lchild != NULL)
			s.push(p->lchild);
	}
}

///@brief 中序遍历，迭代版
///@param[in] root 根节点
///@param[in] visit 访问数据元素的函数指针
///@return 无
void in_order(const binary_tree_node_t* root, int (*visit)(void*))
{
	const binary_tree_node_t* p;
	stack<const binary_tree_node_t*> s;

	p = root;

	while(!s.empty() || p != NULL)	//如果p为空，说明左子树访问完毕；如果栈为空且p为空，则遍历完毕
	{
		
		if(p != NULL)	//如果p不为空，说明一直存在左孩子，一直压栈
		{
			s.push(p);
			p = p->lchild;
		}
		else	//如果p为空，说明已经到叶子节点，取出栈顶元素，即该叶子节点的父节点，获取数据后访问右子树
		{
			p = s.top();
			s.pop();
			(void)visit(p->data);
			p = p->rchild;
		}
	}
}

int main()
{
	return 0;
}