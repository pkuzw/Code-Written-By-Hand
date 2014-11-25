///@file �ؽ�������
///@author zhaowei
///@date 2014.11.25
///@version 1.0

#include <iostream>
#include <cstdlib>
#include <cstring>	//for strchr
#include <cstddef>

using namespace std;

///@brief ����ǰ��������������������������
///@param[in] pre ǰ�����������
///@param[in] in �������������
///@param[in] n ���еĳ��ȣ����������Ľڵ���
///@param[out] post �������������
///@return ��
///@note ���˼·�Ƿ��η��������������ʱ���ڵ��λ�ã�������������е��������ڵ��ȵݹ鴦�����Ȼ���ٵݹ鴦���������ڵ㣬����ϸ��ڵ�
void build_post(const char *pre, const char *in, const int n, char *post)
{
	if (n <= 0)
	{
		return;
	}
	//��������������
	int left_len = strchr(in, pre[0]) - in;	//strchr: ��ָ���ַ�����Ѱ��ָ���ַ���һ���γ��ֵ�λ��
		
	build_post(pre + 1, in, left_len, post);//�ݹ鴦��������

	build_post(pre + left_len + 1, in + left_len + 1, n - left_len - 1, post + left_len);//�ݹ鴦��������

	post[n - 1] = pre[0];	//������ڵ�
}

///@brief ����build_post����
///@return ��
#define MAX 128
void build_post_test()
{
	char pre[MAX] = {};
	char in[MAX] = {};
	char post[MAX] = {};


	cout << "Input the pre order sequence: " << endl;
	cin >> pre;
	cout << "Input the in order sequence: " << endl;
	cin >> in;

	build_post(pre, in, strlen(pre), post);
	cout << "Output the post order sequence: " << endl;
	cout << post << endl;
	return;
}

int main()
{
	/*�������¶�����
		1
	   / \
	  2   3
	 / \ / \
	4  5 6  7
	*/
	build_post_test();
	return 0;
}