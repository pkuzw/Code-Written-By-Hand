///@brief 选择排序
///@author zhaowei
///@date 2015.01.04
///@version 1.0

#include <iostream>
using namespace std;

///@brief 交换两个元素
///@param[in] a 待交换的元素
///@param[in] b 待交换的元素
///@return 无
void swap_elem(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

///@brief 选择排序
///@param[in] arr 待排序的数组指针
///@param[in] p 待排序的数组首元素下标
///@param[in] r 待排序的数组末元素下标
///@return 无
void select_sort(int *arr, int p, int r)
{
	for (int i = p; i < r; i++)	//外层循环每次遍历寻找第i小的数
	{
		int min_index = i;
		for (int j = i; j <= r; j++)	//内层循环找当前剩余数中的最小数
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}
		swap_elem(arr[i], arr[min_index]);
	}
}

int main()
{
	cout << "Input the unsorted array's length: ";
	int len = 0;
	cin >> len;

	int *arr = new int[len];

	cout << "Input the array: ";
	for (int i = 0; i < len; i++)
	{
		cin >> arr[i];
	}

	select_sort(arr, 0, len-1);

	cout << "Output the sorted array: ";
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	delete[] arr;

	return 0;
}