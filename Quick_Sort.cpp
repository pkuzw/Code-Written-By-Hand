///@brief ��������
///@author zhaowei
///@date 2015.01.04
///@version 1.0

#include <iostream>
using namespace std;

///@brief ��������Ԫ��
///@param[in] a ��������Ԫ��
///@param[in] b ��������Ԫ��
///@return ��
void swap_elem(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

///@brief ��������л��֣�����С�Ļ�����࣬�ϴ�Ļ����Ҳ�
///@param[in] arr �����ֵ�����
///@param[in] p �������������ʼ�±�
///@param[in] r �������������ֹ�±�
///@return ��������ֵ�����±�
int partition(int* arr, int p, int r)
{
	int x = arr[r];	//��Ϊ����ֵ(pivot_value)
	int i = p - 1;

	for (int j = p; j < r; j++)
	{
		if (arr[j] <= x)
		{
			i++;
			swap_elem(arr[i], arr[j]);	//������ֵС�Ķ�����ǰ��
		}
	}
	swap_elem(arr[++i], arr[r]);	//�Ż�����ֵ
	return i;
}

///@brief �ݹ��������
///@param[in] arr �����������
///@param[in] p ������ʼ�±�
///@param[in] r ������ֹ�±�
///@return ��
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