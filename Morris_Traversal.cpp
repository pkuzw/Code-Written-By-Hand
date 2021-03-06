﻿///@file Morris遍历
///@author zhaowei
///@date 2014.11.18
/* @note Morris遍历是一种只需要O(1)的空间复杂度的二叉树遍历方法。这种算法和线索二叉树很像，只不过它是一边建线索，一边访问数据，访问完后销毁线索，保持二叉树不变。
*/

#include <iostream>
#include <cstdlib>

using namespace std;

typedef int elem_t;	//节点数据类型
///@struct 
///@brief 二叉树节点
typedef struct bt_node_t
{
	elem_t data;		//节点数据
	bt_node_t* lchild;	//左孩子
	bt_node_t* rchild;	//右孩子
}bt_node_t;

///@brief Morris中序遍历
///@param[in] root 根节点
///@param[in] visit 访问函数
///@return 无
/* @note Morris中序遍历的步骤如下：
		 1. 初始化当前节点cur为root节点
		 2. 如果cur没有左孩子，则输出当前节点，并将其右孩子作为当前节点，即cur = cur->rchild
		 3. 如果cur有左孩子，则寻找cur的前驱，即cur的左子树的最右下角节点
			a. 如果前驱节点的右孩子为空，则将它的右孩子指向当前节点，当前节点更新为当前节点的左孩子，即cur = cur->lchild
			b. 如果前驱节点的右孩子非空，即指向当前节点，则断开该指向，即将前驱节点的右孩子置为空，输出当前节点cur，并将当前节点更新为
				当前节点的右孩子，即cur = cur->rchild
		 4. 重复步骤2和步骤3，直至cur为空
*/
void in_order_morris(bt_node_t* root, int(*visit)(elem_t))
{
	bt_node_t *cur = NULL, *pre = NULL;	//声明指针的时候如果多个指针在同一行声明，应该在每一个变量名前加*号

	cur = root;
	while(cur != NULL)
	{
		if(cur->lchild == NULL)
		{
			visit(cur->data);
			cur = cur->rchild;
		}
		else
		{
			//查找当前节点的前驱节点，即左子树中的最右下角节点
			pre = cur->lchild;
			while(pre->rchild != NULL && pre->rchild != cur)
			{
				pre = pre->rchild;
			}

			if(pre->rchild == NULL)	//若还未线索化，则线索化，并将当前节点更新为左孩子
			{
				pre->rchild = cur;
				cur = cur->lchild;
			}
			else					//若已经线索化，则断开线索，访问节点并更新节点至右孩子
			{
				pre->rchild = NULL;
				visit(cur->data);
				cur = cur->rchild;
			}
		}
	}
}

///@brief Morris先序遍历二叉树
///@param[in] root 根节点
///@param[in] visit 访问节点数据函数
///@return 无
/* @note Morris先序遍历算法的步骤如下：
		 1. 初始化当前节点cur为root节点
		 2. 如果cur没有左孩子，则输出当前节点，并将当前节点更新为其右孩子，即cur = cur->rchild
		 3. 如果cur有左孩子，则寻找其前驱节点，即左子树的最右下角节点：
			a. 如果当前节点的前驱节点的右孩子为空，则输出当前节点，并将前驱节点的右孩子指向当前节点，然后将当前节点更新为其左孩子，即
			cur = cur->lchild
			b. 如果当前节点的前驱节点的右孩子指向当前节点，则断开该指向，将前驱节点的右孩子指向空指针，然后将当前节点更新为其右孩子，即
			cur = cur->rchild
		 4. 重复步骤2、3，直至cur为空
*/
void pre_order_morris(bt_node_t* root, int (*visit)(elem_t))
{
	bt_node_t *cur = root, *pre = NULL;
	while (cur != NULL)
	{
		if (cur->lchild == NULL)	//如果没有左孩子，则访问当前节点，并将当前节点更新为其右孩子
		{
			visit(cur->data);
			cur = cur->rchild;
		}
		else						//如果有左孩子
		{
			pre = cur->lchild;		//寻找当前节点的前驱节点
			while (pre->rchild != NULL && pre->rchild != cur)
			{
				pre = pre->rchild;
			}
			if (pre->rchild == NULL)//如果前驱未指向当前节点，则访问当前节点，将前驱节点右孩子指向当前节点，更新为当前节点的左孩子
			{	
				visit(cur->data);
				pre->rchild = cur;
				cur = cur->lchild;
			}
			else if (pre->rchild == cur)//如果前驱节点指向当前节点，则断开该指向，并将当前节点更新为当前节点的右孩子
			{
				pre->rchild = NULL;
				cur = cur->rchild;
			}
		}
	}
}

//逆转路径
static void reverse(bt_node_t* from, bt_node_t* to);

//逆转访问指定节点间的节点
static void visit_reverse(bt_node_t* from, bt_node_t* to, int (*visit)(elem_t));

///@brief Morris后序遍历二叉树
///@param[in] root 根节点
///@param[in] visit 访问节点数据的函数
///@return 无
///@note Morris后序遍历二叉树的算法步骤
//       1. 将当前节点cur置为root；
//       2. 如果当前节点没有左孩子，则将当前节点更新为当前节点的右孩子，即cur = cur->rchild
//       3. 如果当前节点有左孩子，则寻找当前节点的前驱节点，即当前节点左子树的最右下角节点：
//          a. 如果前驱节点的右孩子为空，则将右孩子指向当前节点，并将当前节点更新为当前节点的左孩子，即cur = cur->lchild
//          b. 如果前驱节点的右孩子指向当前节点，则断开该指向，即将前驱节点的右孩子指向空指针，然后按照从前驱节点到当前节点的左孩子的顺序输出路径上
//             的所有节点，并将当前节点更新为当前节点的右孩子，即cur = cur->rchild
//       4. 重复步骤2和步骤3，直至当前节点为空，即cur = NULL
void post_order_morris(bt_node_t* root, int (*visit)(elem_t))
{
	bt_node_t dump = {0, NULL, NULL};	//临时节点，令其左孩子为根节点
	dump.lchild = root;
	bt_node_t *cur = &dump, *pre = NULL;

	while (cur != NULL)
	{
		if (cur->lchild == NULL)	//如果当前节点的左孩子为空，则更新当前节点为其右孩子
		{
			cur = cur->rchild;
		}
		else						//如果当前节点的左孩子非空，则寻找当前节点的前驱节点
		{
			pre = cur->lchild;
			while (pre->rchild != NULL && pre->rchild != cur)
			{
				pre = pre->rchild;
			}

			if (pre->rchild == NULL)//如果前驱节点的右孩子未指向当前节点（线索化），则将前驱的右孩子指向当前节点，并将当前节点移到其左孩子
			{
				pre->rchild = cur;
				cur = cur->lchild;
			} 
			else	//如果前驱节点的右孩子指向了当前节点，则反向输出从当前节点的左孩子到前驱节点路径上的所有节点，并清除该指向，让后将当前节点移到右孩子
			{
				visit_reverse(cur->lchild, pre, visit);
				pre->rchild = NULL;
				cur = cur->rchild;
			}
		}
	}
}

///@brief 逆转路径
///@param[in] from 起始节点
///@param[to] to 终止节点
///@return 无
///@note 逆转路径限定在当前节点的左孩子到当前节点的前驱节点之间的路径，这就相当于在二者之间的单向链表
static void reverse(bt_node_t *from, bt_node_t *to)
{
	if (from == to)
	{
		return;
	}
	bt_node_t *x = from, *y = from->rchild, *z = NULL;
	while (x != to)
	{
		z = y->rchild;	//z后移
		y->rchild = x;	//why?	这里相当于将y的右孩子转向。
		x = y;			//x后移
		y = z;			//y后移
	}
}

///@brief 访问逆转后的路径上的所有节点
///@param[in] from 起始节点
///@param[in] to 终止节点
///@return 无
static void visit_reverse(bt_node_t *from, bt_node_t *to, int (*visit)(elem_t))
{
	reverse(from, to);	//先将节点顺序颠倒过来

	bt_node_t *p = to;
	while(1)
	{
		visit(p->data);
		if (p == from)
		{
			break;
		}
		p = p->rchild;	//因为前驱节点是左子树的最右下角节点，只需要一直向右下角遍历
	}

	reverse(to, from);	//再把节点顺序还原
}

///@brief 分配一个新结点
///@param[in] data 新结点的数据
///@return 新结点
bt_node_t* new_node(int data)
{
	bt_node_t* node = (bt_node_t*) malloc(sizeof(bt_node_t));
	node->data = data;
	node->lchild = NULL;
	node->rchild = NULL;

	return node;
}

///@brief 打印函数
///@param[in] data 节点的数据
///@return 返回节点数据
static int print(const elem_t data)
{
	cout << data << ' ';
	return 0;
}

int main()
{
	/*构造如下二叉树
		1
	   / \
	  2   3
	 / \ / \
	4  5 6  7
	*/
	bt_node_t *root = new_node(1);
	root->lchild = new_node(2);
	root->rchild = new_node(3);

	root->lchild->lchild = new_node(4);
	root->lchild->rchild = new_node(5);

	root->rchild->lchild = new_node(6);
	root->rchild->rchild = new_node(7);

	cout << "In order morris: " << endl;
	in_order_morris(root, print);
	cout << endl;

	cout << "Pre order morris: " << endl;
	pre_order_morris(root, print);
	cout << endl;

	cout << "Post order morris: " << endl;
	post_order_morris(root, print);
	cout << endl;

	return 0;
}