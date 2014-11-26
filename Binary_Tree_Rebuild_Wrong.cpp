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
void rebuild(const char *pre, const char *in, int n, bt_node_t *root)
{
	if (n <= 0 || pre == NULL || in == NULL)
	{
		return;
	}
	//获得前序遍历的第一个节点
	root = (bt_node_t *)malloc(sizeof(bt_node_t));	
	//why root is a pointer of pointer?? 如果改为指针，在测试的时候进入post_order()函数时，root会为空。但为什么会为空呢？

	//2014.11.26
	//1. 如果使用一级指针root，在函数内部对其进行的赋值实际上只是对root的副本赋值，而不能影响到函数外面的root。

	//2. 堆：用于存储全局变量和静态变量，手动分配和回收（这个代码中没有对malloc()分配的内存进行释放free()操作，是个缺陷，会造成内存
	//   泄露。注意，free()之后应该将指针置为空，防止它指向不明确的内存空间），速度比较慢，不限制空间（上限是系统分配给进程的内存空间），
	//   实际的表示是链表的结构，每个节点代表可以分配的内存块。在进程建立的时候初始化。

	//3. 栈：用于存储局部变量和函数参数，系统自动分配和管理，在函数退出时栈会被清空；空间受限，速度比较快。在线程建立的时候初始化。

	//4. 静态变量：相当于在函数内部定义的文件范围内的全局变量。在C++中，静态成员变量不依赖于任何类的对象，只与类有关，在初始化时在静态变量
	//	 前添加类名和作用域符号"::"即可。它能够被所有该类的对象访问和更改，这些更改也能被所有该类的对象看到。

	//5. 静态成员函数：与静态成员变量类似，只与类相关，而不依赖于特定的类的对象。它有两个特点：a. 没有this指针，因为不依赖于对象；b. 只能
	//   访问静态成员变量，因为非静态成员变量都与特定对象相关。

	//6. 值传递：将一个变量X的内容复制给另一个变量Y，Y所代表的是副本，Y上的所有操作不影响X上的值。

	//7. 引用传递：将变量Y指向了X所表示的内容，相当于Y是X的别名，二者对内容的修改互相可见。


	(root)->data = *pre;
	(root)->lchild = NULL;
	(root)->rchild = NULL;

	int left_len = strchr(in, pre[0]) - in;	//计算左子树的节点数

	//以下参数都要抛去根节点
	rebuild(pre + 1, in, left_len, root->lchild);	//重建左子树， pre + 1是因为第一个是根节点，需要跳过

	rebuild(pre + left_len + 1, in + left_len + 1, n - left_len - 1, root->rchild);	//重建右子树, in + left + 1是因为中间有一个根节点，需要多加1
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

	rebuild(pre, in, strlen(pre), root);
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
//	build_post_test();

	rebuild_test();
	return 0;
}