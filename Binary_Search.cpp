///@file �۰����
///@author zhaowei
///@date 2014.12.29
///@version 1.0

#include <iostream>
using namespace std;

typedef unsigned int elem_t;

///@brief ����˳���Ķ��ֲ����㷨
///@param[in] a ���ź��������
///@param[in] n �����Ԫ�ظ���
///@param[in] x �����ҵ�Ԫ��
///@return ��������д��ڸ�Ԫ�أ��򷵻�Ԫ���±ꣻ���򷵻�-1
int binary_search(elem_t *a, int b_index, int e_index, const elem_t x)
{
	int mid = (e_index + b_index) / 2;
	if (x == a[mid])
	{
		return mid;
	}
	else if (x < a[mid] && x >= a[b_index])
	{
		return binary_search(a, b_index, mid - 1, x);
	}
	else if (x > a[mid] && x <= a[e_index])
	{
		return binary_search(a, mid + 1, e_index, x);
	}
	return -1;
}

int main()
{
	elem_t arr[10] = {1, 3, 5, 12, 44, 56, 100, 123, 231, 233};
	int x = 0;
	cout << "Input the element you want: \n";
	while (cin >> x)
	{
		int result = binary_search(arr, 0, 9, x);
		cout << result;
		cout << endl;
	}
	return 0;
}
