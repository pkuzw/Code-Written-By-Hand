///@file 二叉树的遍历
///@author zhaowei
///@date 2014.11.12
/*@note 在中序遍历中，一个节点的前驱，是其左子树的最右下角节点；后继是其右子树的最左下角节点
		在后序遍历中，若节点是根节点，则后继为空；
		若节点是双亲的右子树，或是左子树但双亲无右子树，则其后继为双亲节点；
		若节点是双亲的左子树且双亲有右子树，则其后继为右子树按后序遍历的第一个节点
*/

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main()
{
	return 0;
}