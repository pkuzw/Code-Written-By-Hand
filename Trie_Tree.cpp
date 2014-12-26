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

   5.8.2 Immediate Decodebility
   描述
   An encoding of a set of symbols is said to be immediately decodable if no code for one symbol is the
   prefix of a code for another symbol. We will assume for this problem that all codes are in binary, that no
   two codes within a set of codes are the same, that each code has at least one bit and no more than ten bits,
   and that each set has at least two codes and no more than eight.
   Examples: Assume an alphabet that has symbols {A, B, C, D}.
   following code is immediately decodable:
   A:01 B:10 C:0010 D:0000
   but this one is not:
   A:01 B:10 C:010 D:0000 (Note that A is a prefix of C)

   输入
   Write a program that accepts as input a series of groups of records from standard input. Each record
   in a group contains a collection of zeroes and ones representing a binary code for a different symbol. Each
   group is followed by a single separator record containing a single 9; the separator records are not part of
   the group. Each group is independent of other groups; the codes in one group are not related to codes in
   any other group (that is, each group is to be processed independently).

   输出
   For each group, your program should determine whether the codes in that group are immediately
   decodable, and should print a single output line giving the group number and stating whether the group is,
   or is not, immediately decodable.

   样例输入
   01
   10
   0010
   0000
   9
   01
   10
   010
   0000
   9

   样例输出
   Set 1 is immediately decodable
   Set 2 is not immediately decodable

   分析
   判断一个串是否是另一个串的前缀，这正是Trie 树（即字典树）的用武之地。

   题目来自于POJ 1056，提交后能够Accepted.
*/

//#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define MAXN 10000		//输入编码的最大个数
#define CHAR_COUNT 2	//字符的种类，即单个节点的子树的最大数目
#define MAX_CODE_LEN 10	//编码的最大长度
#define MAX_NODE_COUNT ((1 << (MAX_CODE_LEN + 1)) - 1)	//Trie的最大节点数目

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
bool trie_tree_insert(trie_tree_t *tree, const char* word)
{
	trie_node_t *p = tree->root;
	//int word_len = word.length();
	int index = 0;
	while(*word)
	{
		int curword = *word - '0';
		if (p->next[curword] == NULL)
		{
			p->next[curword] = &(tree->nodes[tree->size++]);
		}
		p = p->next[curword];

		if (p->is_tail)	//如果某串是当前串的前缀
		{
			return false;
		}
		word++;	//指针下移
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

int main()
{
	int sample_num = 0;
	char input_code[MAX_CODE_LEN];
	
	trie_tree_t *trie = trie_tree_create();
	bool is_legal = true;

	while (scanf("%s", input_code) != EOF)
	{				
		if (strcmp(input_code, "9") == 0)
		{
			if (is_legal)
			{
				printf("Set %d is immediately decodable\n", ++sample_num);				
			}
			else
			{
				printf("Set %d is not immediately decodable\n", ++sample_num);
			}
			trie_tree_clear(trie);
			is_legal = true;
		}
		else
		{
			if (is_legal)
			{
				is_legal = trie_tree_insert(trie, input_code);
			}
		}
		//memset(input_code, 0, 15);
	}
	trie_tree_delete(trie);
	return 0;
}