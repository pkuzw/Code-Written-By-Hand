///@file 直接插入排序
///@author zhaowei
///@date 2015.01.02
///@version 1.0

#include <iostream>
#include <string>
using namespace std;

///@brief 将给定的整数数组进行插入排序
///@param[in] arr 待排序的数组指针
///@param[in] order_type 升序：asc；降序：des
///@param[in] p 排序的起始元素下标
///@param[in] q 排序的终止元素下标
///@return 无
void insertion_sort(int *arr, const string order_type, int p, int q)
{
	if (order_type == "asc")
	{
		for (int i = p; i < q; i++)
		{
			int tmp = arr[i + 1];
			for (int j = i + 1; j > p; j--)
			{				
				if (tmp < arr[j - 1])	//不带"="，是稳定排序。在键值相同的情况下，原本在前面的元素在排序后仍在前面。
				{
					arr[j] = arr[j - 1];
					if (j == p + 1)
					{
						arr[j - 1] = tmp;
					}
				}
				else
				{
					arr[j] = tmp;
					break;
				}
			}			
		}
	}
	else
	{
		for (int i = p; i < q; i++)
		{
			int tmp = arr[i + 1];
			for (int j = i + 1; j > p; j--)
			{				
				if (tmp > arr[j - 1])
				{
					arr[j] = arr[j - 1];
					if (j == p + 1)
					{
						arr[j - 1] = tmp;
					}
				}
				else
				{
					arr[j] = tmp;
					break;
				}
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

	cout << "Input the sort's type: ";
	string sort_type = "asc";
	cin >> sort_type;

	insertion_sort(arr, sort_type, 0, len-1);

	cout << "Output the sorted array: ";
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	delete[] arr;

	return 0;
}