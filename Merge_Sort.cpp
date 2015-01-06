///@brief 归并排序
///@author zhaowei
///@date 2015.01.06
///@version 1.0

#include <iostream>
#include <stdlib.h>
using namespace std;

///@brief 将两个已经排好序的子序列归并为一个序列
///@param[in] arr 数组首地址
///@param[in] p 第一个子序列起始元素下标
///@param[in] q 第一个子序列终止元素下标
///@param[in] r 第二个子序列终止元素下标
///@return 无
void merge(int *arr, int p, int q, int r)
{
	int *n1 = new int[q - p + 2];	//多申请一位留作末尾的哨兵，用于合并时比较实际元素，将剩余元素全部放入原数组
	int *n2 = new int[r - q + 1];

	for (int i = 0; i < q - p + 1; i++)
	{
		n1[i] = arr[p + i];
	}

	for (int j = 0; j < r - q; j++)
	{
		n2[j] = arr[q + 1 + j];
	}

	int max_num = 1;
	max_num = max_num << 30;
	n1[q - p + 1] = max_num;
	n2[r - q] = max_num;

	int u = 0, v = 0; 
	for (int k = 0; k < r - p + 1; k++)
	{
		if (n1[u] <= n2[v])
			arr[p + k] = n1[u++];	//这里应该是arr[p+k]，而非arr[k]。否则递归后半部分的时候会错。		
		else
			arr[p + k] = n2[v++];
	}

	delete[] n1;
	delete[] n2;
}

///@brief 归并排序
///@param[in] arr 待排序数组
///@param[in] p 起始元素下标
///@param[in] r 终止元素下标
///@return 无
void merge_sort(int *arr, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		merge_sort(arr, p, q);
		merge_sort(arr, q + 1, r);
		merge(arr, p, q, r);
	}
}
int main()
{
	while (1)
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

		merge_sort(arr, 0, len-1);

		cout << "Output the sorted array: ";
		for (int i = 0; i < len; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
		delete[] arr;
	}
	return 0;
}