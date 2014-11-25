///@file 重建二叉树
///@author zhaowei
///@date 2014.11.25
///@version 1.0

#include <iostream>
#include <cstdlib>	//for malloc
#include <cstring>	//for strchr
#include <cstddef>

using namespace std; 

///@brief 给定前序遍历和中序遍历，输出后序遍历
///@param[in] pre 前序遍历的序列
///@param[in] in 中序遍历的序列
///@param[in] n 序列的长度，即二叉树的节点数
///@param[out] post 后序遍历的序列
///@return 无
///@note 解决思路是分治法，利用中序遍历时根节点的位置，将先序遍历序列的左子树节点先递归处理掉，然后再递归处理右子树节点，最后补上根节点
void build_post(const char *pre, const char *in, const int n, char *post)
{
	if (n <= 0)
	{
		return;
	}
	//计算左子树长度
	int left_len = strchr(in, pre[0]) - in;	//strchr: 在指定字符串中寻找指定字符第一个次出现的位置
		
	build_post(pre + 1, in, left_len, post);//递归处理左子树

	build_post(pre + left_len + 1, in + left_len + 1, n - left_len - 1, post + left_len);//递归处理右子树

	post[n - 1] = pre[0];	//处理根节点
}

///@brief 测试build_post函数
///@return 无
#define MAX 128
void build_post_test()
{
	char pre[MAX] = {};
	char in[MAX] = {};
	char post[MAX] = {};


	cout << "Input the pre order sequence: " << endl;
	cin >> pre;
	cout << "Input the in order sequence: " << endl;
	cin >> in;

	build_post(pre, in, strlen(pre), post);
	cout << "Output the post order sequence: " << endl;
	cout << post << endl;
	return;
}

///@brief 节点数据类型
///@struct
typedef char elem_t;
typedef struct bt_node_t
{
	elem_t data;	//节点数据
	bt_node_t *lchild;	//左孩子
	bt_node_t *rchild;  //右孩子
}bt_node_t;

///@brief 给定前序遍历和中序遍历，重建二叉树
///@param[in] pre 前序遍历序列
///@param[in] in 中序遍历序列
///@param[in] n 遍历序列的长度，即二叉树节点数目
///@param[out] root 重建后的二叉树根节点
///@return 无
void rebuild(const char *pre, const char *in, int n, bt_node_t **root)
{
	if (n <= 0 || pre == NULL || in == NULL)
	{
		return;
	}
	//获得前序遍历的第一个节点
	*root = (bt_node_t *)malloc(sizeof(bt_node_t));	//why root is a pointer of pointer?? 如果改为指针，在测试的时候进入post_order()函数时，root会为空。
													//但为什么会为空呢？
	(*root)->data = *pre;
	(*root)->lchild = NULL;
	(*root)->rchild = NULL;

	int left_len = strchr(in, pre[0]) - in;	//计算左子树的节点数

	//以下参数都要抛去根节点
	rebuild(pre + 1, in, left_len, &((*root)->lchild));	//重建左子树， pre + 1是因为第一个是根节点，需要跳过

	rebuild(pre + left_len + 1, in + left_len + 1, n - left_len - 1, &((*root)->rchild));	//重建右子树, in + left + 1是因为中间有一个根节点，需要多加1
}


///@brief 后序遍历二叉树
///@param[in] root 根节点
///@return 无
void post_order(bt_node_t *root)
{
	if (root != NULL)
	{
		post_order(root->lchild);
		post_order(root->rchild);
		cout << root->data;
	}	
}

///@brief 测试重建二叉树函数
///@return 无
void rebuild_test()
{
	char pre[MAX] = {};
	char in[MAX] = {};
	bt_node_t *root = NULL;


	cout << "Input the pre order sequence: " << endl;
	cin >> pre;
	cout << "Input the in order sequence: " << endl;
	cin >> in;

	rebuild(pre, in, strlen(pre), &root);
	cout << "Output the post order sequence: " << endl;
	post_order(root);
	cout << endl;
	return;
}


int main()
{
	/*测试如下二叉树
		1
	   / \
	  2   3
	 / \ / \
	4  5 6  7
	pre order:	1245367
	in order:	4251637
	post order:	4526731
	*/
	build_post_test();

	rebuild_test();
	return 0;
}