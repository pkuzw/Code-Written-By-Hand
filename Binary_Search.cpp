///@file 折半查找
///@author zhaowei
///@date 2014.12.29
///@version 1.0

#include <iostream>
using namespace std;

typedef unsigned int elem_t;

///@brief 有序顺序表的二分查找算法
///@param[in] a 已排好序的数组
///@param[in] n 数组的元素个数
///@param[in] x 待查找的元素
///@return 如果数组中存在该元素，则返回元素下标；否则返回-1
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
