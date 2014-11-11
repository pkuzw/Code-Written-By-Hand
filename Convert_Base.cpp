///@file 进制转换
///@author zhaowei
///@date 2014.11.08

#include <stack>
#include <iostream>

using namespace std;

///@brief 进制转换，将一个10进制整数转换为d进制，d <= 16
///@param[in] n 整数n
///@param[in] d d进制
///@return 无
void convert_base(long long n, const int d)
{
	stack<char> s;
	int e = 0;
	char tmp = '0';

	while(n != 0)
	{
		e = n % d;
		if (e >= 0 && e <= 9)
		{
			tmp = '0' + e;
		}
		else
		{
			tmp = 'A' + e - 10;
		}
		s.push(tmp);
		n /= d;
	}
	while(!s.empty())
	{
		tmp = s.top();
		s.pop();
		cout << tmp;
	}
	return;
}

///@brief 进制转换，将一个10进制的整数转换为d进制，d <= 16，更优化的版本
/*		  如果可以预估栈的最大空间，则用数组来模拟栈。这是一个常用技巧。
		  如果CPU为64位，则最大整数是2^64.由于数制最小为2，在2进制下最大数需要64位，即栈的最大长度。
*/
///@param[in] n 整数n
///@param[in] d d进制
///@return 无

#define MAX 64
char stck[MAX];
int top = -1;

void convert_base2(long long n, const int d)
{
	int e;
	char tmp = '0';

	while(n != 0)
	{
		e = n % d;
		if (e >= 0 && e <= 9)
		{
			tmp = '0' + e;
		}
		else
		{
			tmp = 'A' + e - 10;
		}
		stck[++top] = tmp;	//入栈
		n /= d;
	}
	while(top >= 0)
	{
		tmp = stck[top--];	//出栈
		cout << tmp;
	}
	return;
}

///@brief 进制转换，将一个d进制整数转换为10进制，d <= 16
///@param[in] s d进制整数
///@param[in] d d进制
///@return 10进制整数
long long restore(const char s[MAX], const int d)
{
	long long result = 0;	//long: -2^31 - 2^31-1，4字节，容易越界
							//long long: -2^63 - 2^63-1，8字节，不容易越界
	int one;

	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			one = s[i] - '0';
		}
		else if (s[i] >= 'A' && s[i] <= 'F')
		{
			one = s[i] - 'A' + 10;
		}
		else
		{
			one = s[i] - 'a' + 10;
		}

		result = result * d + one;	//假设d进制数有n位，从d进制的最高位开始，自高向低每一位都乘以d^(i-1)，其中1 <= i <= n
	}
	return result;
}
int main()
{
	long long n = 0;
	int d = 0;
	
	cout << "Convert decimal number to d number. d <= 16" << endl;
	cout << "input d: ";
	cin >> d;
	cout << "input n: ";
	cin >> n;

	convert_base(n, d);
	cout << endl;

	convert_base2(n, d);
	cout << endl;
	cout << "----------------------------------------------" << endl;
	
	cout << "Convert  d number to decimal number. d <= 16" << endl;
	char d_num[MAX] = "";
	cout << "input string s: ";
	cin >> d_num;

	cout << "input d: ";
	cin >> d;

	cout << "restore result: " << restore(d_num, d);
	cout << endl;
	return 0;
}

