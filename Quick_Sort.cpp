///@brief 快速排序
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

///@brief 对数组进行划分，将较小的划在左侧，较大的划在右侧
///@param[in] arr 待划分的数组
///@param[in] p 待划分数组的起始下标
///@param[in] r 待划分数组的终止下标
///@return 返回中轴值所在下标
int partition(int* arr, int p, int r)
{
	int x = arr[r];	//作为中轴值(pivot_value)
	int i = p - 1;

	for (int j = p; j < r; j++)
	{
		if (arr[j] <= x)
		{
			i++;
			swap_elem(arr[i], arr[j]);	//比中轴值小的都放在前面
		}
	}
	swap_elem(arr[++i], arr[r]);	//放回中轴值
	return i;
}

///@brief 递归快速排序
///@param[in] arr 待排序的数组
///@param[in] p 数组起始下标
///@param[in] r 数组终止下标
///@return 无
void quick_sort(int *arr, int p, int r)
{
	if (p < r)
	{
		int q = partition(arr, p, r);
		quick_sort(arr, p, q - 1);
		quick_sort(arr, q + 1, r);
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

    quick_sort(arr, 0, len-1);

	cout << "Output the sorted array: ";
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	delete[] arr;

	return 0;
}