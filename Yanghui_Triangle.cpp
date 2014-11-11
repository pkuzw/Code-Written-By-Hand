///@file 打印杨辉三角
///@author zhaowei
///@date 2014.11.11
///@version 1.0

#include <queue>
#include <iostream>

using namespace std;

///@brief 打印杨辉三角系数
/*	分行打印二项式(a+b)^n展开式的系数。在输出上一行系数的同时，将其下一行的系数预先计算好，放入队列。
	在各行系数之间插入一个0
*/
///@param[in] n
///@return 无
void yanghui_triangle(const int n)
{
	int x = 1;
	queue<int> q;
	q.push(x);	//预先放入杨辉三角的第一行1

	for(int i = 0; i <= n; i++)	//杨辉三角的第n+1行代表着(a+b)^n的二项展开式系数
	{
		int s = 0;	//s在这里初始化为0.在内循环中相当于上一行的第-1个元素。
					//这样在利用"第i+1行的第j个数 = 第i行的第j-1个数 + 第i行的第j个数"时，对于新一行的第一个元素，就总能得到1

		q.push(s);	//在各行之间插入一个0，相当于在每一行的末尾添加了一个0.原本第i行有i+1个数，现在变为i+2个数

		//处理第i行的i+2个系数（包括一个0）
		for(int j = 0; j < i+2; j++)
		{
			int t = 0, tmp = 0;
			t = q.front();	//读取一个系数放入t
			q.pop();		//出队
			tmp = s + t;	//计算下一行的系数，并入队。第i+1行的第j个数 = 第i行的第j-1个数 + 第i行的第j个数
			q.push(tmp);	//入队
			s = t;			//s是每一个最新出队的元素
			if(j != i+1)	//打印一个系数，第i+2个是0，不打印
				cout << s << ' ';
		}
		cout << endl;
	}
}

int main()
{
	int n = 0;

	cout << "Input the number of lines: ";
	cin >> n;

	cout << "Output the triangles: " << endl;
	yanghui_triangle(n);
	return 0;
}