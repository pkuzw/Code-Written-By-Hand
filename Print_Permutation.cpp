///@file 打印1到n的所有排列
///@author zhaowei
///@date 2015.01.09
///@version 1.0
///@note 递归求解，先输出以1开头的排列，然后输出以2开头的排列，最后输出以n开头的排列。

#include <iostream>
using namespace std;

///@brief 递归打印1到n的全排列
///@param[in] n 排列的最大元素数
///@param[in] cur 当前递归的位置
///@param[out] permutation 存放的排列
///@return 无
static void print_permutation_r(const int n, int cur, int* permutation)
{
	if (cur == n)
	{
		for (int i = 0; i < n; i++)
			cout << permutation[i] << " ";
		cout << endl;
	}

	for (int i = 1; i <= n; i++)
	{
		int used = 0;
		for (int j = 0; j < cur; j++)
		{
			if (permutation[j] == i)
			{
				used = 1;	//如果i已经在permutation[0...cur-1]出现过，则不能再选
			}
		}
		if (!used)
		{
			permutation[cur] = i;
			print_permutation_r(n, cur + 1, permutation);	//递归调用
		}
	}
}

///@brief 打印1到n的所有排列
///@param[in] n 数组的长度
///@return 无
void print_permutation(const int n)
{
	int prmt_cnt = n;
	int *permutation = new int[prmt_cnt];
	print_permutation_r(n, 0, permutation);
	delete[] permutation;
}

int main()
{
	cout << "Input n: ";
	int n = 0;
	cin >> n;

	print_permutation(n);

	return 0;
}