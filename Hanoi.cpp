///@file Hanoi塔问题
//		 n阶Hanoi塔问题假设有三个分别命名为X、Y、Z的塔座，在塔座X上插有n个直径大小各不相同、从小到大编号为1，2，...，n
//		 的圆盘。现要求将X塔上的n个圆盘移动到Z上并仍按同样的顺序叠放，圆盘移动时必须遵循以下规则：
//		 1. 每次只能移动一个圆盘；
//		 2. 圆盘可以插在任一塔座上；
//		 3. 任何时刻都不能将一个较大的圆盘压在较小的圆盘之上
///@author zhaowei
///@date 2014.11.07

#include <iostream>
using namespace std;

int counter = 0;	//全局变量，对于移动步数计数

///@brief 将x塔座上编号为n的圆盘移动到z塔座上
///@param[in] n 圆盘编号
///@param[in] x 源塔座
///@param[in] z 目标塔座
void move(int n, char x, char z)
{
	cout << ++counter << ". Move disk " << n << " from " << x << " to " << 
		z << "." << endl;
}

///@brief 将塔座x上按直径由小到大且自上而下进行编号为1至n的n个圆盘按规则搬到塔座z上，y可以用作辅助塔座
///@param[in] n 圆盘数目
///@param[in] x 源塔座
///@param[in] y 辅助塔座
///@param[in] z 目标塔座
///@return 无
///@note 无
///@remarks 无
void hanoi(int n, char x, char y, char z)
{
	if (n == 1)
	{
		move(1, x, z);
		return;
	}
	else
	{
		hanoi(n-1, x, z, y);
		move(n, x, z);
		hanoi(n-1, y, x, z);
	}
}


int main()
{
	hanoi(3, 'X', 'Y', 'Z');
	return 0;
}