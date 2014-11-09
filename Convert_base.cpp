///@file 进制转换
///@author zhaowei
///@date 2014.11.08

#include <stack>
#include <iostream>

using namespace std;

///@brief 进制转换，将一个10进制整数转换为d进制，d <= 10
///@param[in] n 整数n
///@param[in] d d进制
///@return 无
void convert_base(int n, const int d)
{
	stack<int> s;
	int e;

	while(n != 0)
	{
		e = n % d;
		s.push(e);
		n /= d;
	}
	while(!s.empty())
	{
		e = s.top();
		s.pop();
		cout << e;
	}
	return;
}

///@brief 进制转换，将一个10进制的整数转换为d进制，d <= 10，更优化的版本
/*		  如果可以预估栈的最大空间，则用数组来模拟栈。这是一个常用技巧。
		  如果CPU为64位，则最大整数是2^64.由于数制最小为2，在2进制下最大数需要64位，即栈的最大长度。
*/
///@param[in] n 整数n
///@param[in] d d进制
///@return 无

#define MAX 64
int stck[MAX];
int top = -1;

void convert_base2(int n, const int d)
{
	int e;

	while(n != 0)
	{
		e = n % d;
		stck[++top] = e;	//入栈
		n /= d;
	}
	while(top >= 0)
	{
		e = stck[top--];	//出栈
		cout << e;
	}
	return;
}


int main()
{
	int n = 0, d = 0;
	cout << "input d: ";
	cin >> d;
	cout << "input n: ";
	cin >> n;

	convert_base(n, d);
	cout << endl;

	convert_base2(n, d);
	cout << endl;
	return 0;
}

