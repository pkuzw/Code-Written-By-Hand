///@file 冒泡排序
///@author zhaowei
///@date 2015.01.03
///@version 1.0

#include <iostream>
#include <string>
using namespace std;

///@brief 交换两个元素的值
///@param[in] p 待交换的元素p
///@param[in] q 待交换的元素q
///@return 无
void swap_value(int &p, int &q)
{
	int tmp = p;
	p = q;
	q = tmp;
}


///@brief 将给定的整数数组进行冒泡排序
///@param[in] arr 待排序的数组指针
///@param[in] p 排序的起始元素下标
///@param[in] q 排序的终止元素下标
///@return 无
void bubble_sort(int *arr, int p, int q)
{
	for (int i = p; i < q; i++)	//外层循环保证每一次循环使得最小的元素位于最前端，最多n-1趟完成排序
	{
		for (int j = q; j > i; j--)	//内层循环从后往前比较相邻的两个元素，如果出现逆序，就交换两元素
		{
			if (arr[j - 1] > arr[j])
			{
				swap(arr[j - 1], arr[j]);
			}
		}
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

	bubble_sort(arr, 0, len-1);

	cout << "Output the sorted array: ";
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	delete[] arr;

	return 0;
}