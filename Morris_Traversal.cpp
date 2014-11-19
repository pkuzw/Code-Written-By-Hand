///@file Morris遍历
///@author zhaowei
///@date 2014.11.18
/* @note Morris遍历是一种只需要O(1)的空间复杂度的二叉树遍历方法。这种算法和线索二叉树很像，只不过它是一边建线索，一边访问数据，
访问完后销毁线索，保持二叉树不变。
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


int main()
{
	return 0;
}