///@file 食物链
///@author zhaowei
///@date 2014.12.10
///@version 1.0
/* @note
   描述
   动物王国中有三类动物A, B, C，这三类动物的食物链构成了有趣的环形。A吃B，B吃C，C吃A。现有N个动物，从1到N编号。
   每个动物都是A, B, C中的一种，但是我们并不知道它到底是哪一种。
   有人说用两种说法对这N个动物构成的食物链进行描述：
   1. 第一种说法是“1 X Y”，表示X和Y是同类。
   2. 第二种说法是“2 X Y”，表示X吃Y。
   此人对N个动物，用上述两种说法，一句接一句地说出K句话，这K句话有的是真的，有的是假的。当一句话满足下列三个条件之一时，
   这句话就是假话，否则就是真话。
   1. 当前的话与前面的某些真话冲突，就是假话；
   2. 当前的话中X或Y比N大，就是假话；
   3. 当前的话表示X吃X，就是假话。
   你的任务是根据给定的N（1 <= N <= 50,000）和K句话（0 <= K <= 100,000）输出假话的总数。

   输入
   第一行是两个整数N和K，以一个空格分隔。
   以下K行每行是三个正整数D，X，Y，两数之间用一个空格隔开，其中D表示说法的种类。
   • 若D=1，则表示X和Y是同类。
   • 若D=2，则表示X吃Y。

   输出
   只有一个整数，表示假话的数目。

   样例输入
   100 7
   1 101 1
   2 1 2
   2 2 3
   2 3 3
   1 1 3
   2 3 1
   1 5 5

   样例输出
   3

   本题与POJ 1182食物链相同。
*/

#include <cstdlib>
#include <iostream>
using namespace std;

typedef struct ufs_t
{
	int *p;		//保存并查集的数组
	int *dist;	//表示x与父节点p[x]的关系：0表示x与p[x]是同类；1表示x吃p[x]；2表示p[x]吃x
	int size;	//并查集的大小
}ufs_t;

///@brief 创建并查集
///@param[in] n 数组的容量
///@return 并查集
ufs_t* ufs_create(const int n)
{
	ufs_t *ufs = (ufs_t*)malloc(sizeof(ufs_t));
	ufs->p = (int*)malloc(n * sizeof(int));
	ufs->dist = (int*)malloc(n * sizeof(int));
	ufs->size = n;

	for (int i = 0; i < n; i++)
	{
		ufs->p[i] = -1;
		ufs->dist[i] = 0;	//初始时并查集每个元素的根节点就是其本身，故自身与自身是同类
	}
	return ufs;
}

///@brief 销毁并查集
///@param[in] ufs 并查集指针
///@return 无
void ufs_destroy(ufs_t *ufs)
{
	if (ufs->p != NULL)
	{
		free(ufs->p);
		ufs->p = NULL;
	}

	if (ufs->dist != NULL)
	{
		free(ufs->dist);
		ufs->dist = NULL;
	}

	if (ufs != NULL)
	{
		free(ufs);
		ufs = NULL;
	}
}

///@brief Find操作，压缩路径递归版
///@param[in] ufs 并查集指针
///@param[in] x 待查找的元素
///@return 元素所在树的根节点
int ufs_find(ufs_t *ufs, int x)
{
	if (ufs->p[x] < 0)
	{
		return x;
	}
	int parent = ufs->p[x];
	ufs->p[x] = ufs_find(ufs, ufs->p[x]);	//压缩路径
	ufs->dist[x] = (ufs->dist[x] + ufs->dist[parent]) % 3;	//??更新关系
	return ufs->p[x];
}

///@brief Union操作，将root2并入root1
///@param[in] ufs 并查集指针
///@param[in] root1 一棵树的指针
///@param[in] root2 另一棵树的指针
///@return 如果二者已经在同一集合，则返回-1；否则返回0
int ufs_union(ufs_t *ufs, int root1, int root2)
{
	if (root1 == root2)
	{
		return -1;
	}
	ufs->p[root1] += ufs->p[root2];
	ufs->p[root2] = root1;
	return 0;
}

///@brief 添加一对关系
///@param[inout] ufs 并查集
///@param[in] x 元素x
///@param[in] y 元素y
///@param[len] relation 关系
///@return 无
void ufs_add_relation(ufs_t *ufs, int x, int y, int relation)
{
	const int root_x = ufs_find(ufs, x);
	const int root_y = ufs_find(ufs, y);
	ufs_union(ufs, root_x, root_y);
	ufs->dist[root_y] = (ufs->dist[x] - ufs->dist[y] + 3 + relation) % 3;	//??
}

int main()
{
	int n = 0;	//动物数目
	int k = 0;	//信息数目
	int result = 0;	//假话数目
	ufs_t *ufs = NULL;

	cin >> n >> k;
	ufs = ufs_create(n + 1);	//p数组和dist数组的0号元素未使用

	while (k--)
	{
		int d = 0;	//信息种类
		int x = 0, y = 0;	//动物编号
		cin >> d >> x >> y;

		if (x > n || y > n || (d == 2 && x == y))
		{
			result++;
		}
		else
		{
			const int root_x = ufs_find(ufs, x);
			const int root_y = ufs_find(ufs, y);

			if (root_x == root_y)	//若在同一个集合则可以确定x和y的关系
			{
				if ((ufs->dist[x] - ufs->dist[y] + 3) % 3 != d - 1)	//??
				{
					result++;
				}
			} 
			else
			{
				ufs_add_relation(ufs, y, x, d - 1);	//??注意x与y的顺序，为什么颠倒顺序就会出错？
			}
		}
	}
	cout << result << endl;
	ufs_destroy(ufs);
	return 0;
}