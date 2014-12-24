///@file Trie树原理
///@auhtor zhaowei
///@date 2014.12.23
///@version 1.0
/* @note
   Trie树是用来存储和查找字符串的N叉树（或者优化后的三叉树）。每个节点存储字符串的一个字符和一个值，
   在查找时如果匹配，就继续往下找，直到找完时节点值非空即可。如果节点不存在或者节点值为空，则没有找到。
   在插入时也是一样，从根节点向下找，找到不一样的节点时开始插入字符和值。
   删除时是将节点值置为0，如果连接到该节点的父节点值也为零，则将该节点删除，否则保留。
   参考文献：http://algs4.cs.princeton.edu/lectures/52Tries.pdf
*/

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAXN 10000		//输入编码的最大个数
#define CHAR_COUNT 10	//字符的种类，即单个节点的子树的最大数目
#define MAX_CODE_LEN 10	//编码的最大长度
#define MAX_NODE_COUNT (MAXN * MAX_CODE_LEN + 1)	//Trie的最大节点数目

///@brief Trie节点
typedef struct trie_node_t
{
	trie_node_t *next[CHAR_COUNT];	//子树节点指针
	bool is_tail;	//标记当前字符是否位于某一字符串的尾部
}trie_node_t;

///@brief Trie树
typedef struct trie_tree_t
{
	trie_node_t *root;	//trie树根节点
	int size;			//trie树中节点数目
	trie_node_t nodes[MAX_NODE_COUNT];
}trie_tree_t;

///@brief 创建Trie树
///@return 返回Trie指针
trie_tree_t* trie_tree_create()
{
	trie_tree_t *tree = (trie_tree_t*)malloc(sizeof(trie_tree_t));
	tree->root = &(tree->nodes[0]);
	memset(tree->nodes, 0, sizeof(tree->nodes));
	tree->size = 1;
	return tree;
}

///@brief 销毁Trie树
///@param[in] tree trie树指针
///@return 无
void trie_tree_delete(trie_tree_t *tree)
{
	free(tree);
	tree = NULL;
	return;
}

///@brief 将Trie中所有节点信息清空
///@param[in] tree trie树指针
///@return 无
void trie_tree_clear(trie_tree_t *tree)
{
	memset(tree->nodes, 0, sizeof(tree->nodes));
	tree->size = 1;
}

///@brief 在当前Trie树中插入新的字符串
///@param[in] tree trie树指针
///@param[in] word 新插入的字符串
///@return 如果插入成功，返回true，否则返回false
bool trie_tree_insert(trie_tree_t *tree, const string word)
{
	trie_node_t *p = tree->root;
	int word_len = word.length();
	int index = 0;
	while(index < word_len)
	{
		int curword = word[index] - '0';
		if (p->next[curword] == NULL)
		{
			p->next[curword] = &(tree->nodes[tree->size++]);
		}
		p = p->next[curword];

		if (p->is_tail)	//如果某串是当前串的前缀
		{
			return false;
		}
		index++;
	}
	p->is_tail = true;	//标记当前串已经到达结尾

	for (int i = 0; i < CHAR_COUNT; i++)
	{
		if (p->next[i] != NULL)
		{
			return false;
		}
	}
	return true;
}

