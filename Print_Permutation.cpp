///@file 打印1到n的所有排列
///@author zhaowei
///@date 2015.01.09
///@version 1.0

#include <iostream>
using namespace std;

///@brief 打印1到n的所有排列
///@param[in] n 数组的长度
///@return 无
void print_permutation(const int n)
{
	int prmt_cnt = n;
	for (int i = n-1; i > 0; i--)
	{
		prmt_cnt *= i;
	}
	int *permutation = new int[prmt_cnt];

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