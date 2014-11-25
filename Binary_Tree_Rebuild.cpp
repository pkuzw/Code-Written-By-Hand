///@file 重建二叉树
///@author zhaowei
///@date 2014.11.25
///@version 1.0

#include <iostream>
#include <cstdlib>
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

int main()
{
	/*测试如下二叉树
		1
	   / \
	  2   3
	 / \ / \
	4  5 6  7
	*/
	build_post_test();
	return 0;
}