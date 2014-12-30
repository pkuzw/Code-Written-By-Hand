//
//  Hardwood_Species1.cpp
//  Code Written By Hand
//
//  Created by Zhao Wei on 14/12/30.
//  Copyright (c) 2014年 Zhao Wei. All rights reserved.
//

#include "Hardwood_Species1.h"
///@file Hardwood Species
///@author zhaowei
///@date 2014.12.30
///@version 2.0
/* @note
 描述
 现在通过卫星扫描，扫描了很多区域的树，并获知了每棵树的种类，求每个种类的百分比。
 
 输入
 一行一棵树，表示该树的种类。每个名字不超过30个字符，树的种类不超过10,000；树的总数不超过1,000,000.
 
 输出
 按字母顺序，打印每个种类的百分比，精确到小数点后4位
 
 样例输入
 Red Alder
 Ash
 Aspen
 Basswood
 Ash
 Beech
 Yellow Birch
 Ash
 Cherry
 Cottonwood
 Ash
 Cypress
 Red Elm
 Gum
 Hackberry
 White Oak
 Hickory
 Pecan
 Hard Maple
 White Oak
 Soft Maple
 Red Oak
 Red Oak
 White Oak
 Poplan
 Sassafras
 Sycamore
 Black Walnut
 Will
 
 样例输出
 Ash 13.7931
 Aspen 3.4483
 Basswood 3.4483
 Beech 3.4483
 Black Walnut 3.4483
 Cherry 3.4483
 Cottonwood 3.4483
 Cypress 3.4483
 Gum 3.4483
 Hackberry 3.4483
 Hard Maple 3.4483
 Hickory 3.4483
 Pecan 3.4483
 Poplan 3.4483
 Red Alder 3.4483
 Red Elm 3.4483
 Red Oak 6.8966
 Sassafras 3.4483
 Soft Maple 3.4483
 Sycamore 3.4483
 White Oak 10.3448
 Willow 3.4483
 Yellow Birch 3.4483
 
 本题来自POJ 2418
 */

///@file Hardwood Species
///@author zhaowei
///@date 2014.12.27
///@version 1.0
/* @note
 描述
 现在通过卫星扫描，扫描了很多区域的树，并获知了每棵树的种类，求每个种类的百分比。
 
 输入
 一行一棵树，表示该树的种类。每个名字不超过30个字符，树的种类不超过10,000；树的总数不超过1,000,000.
 
 输出
 按字母顺序，打印每个种类的百分比，精确到小数点后4位
 
 样例输入
 Red Alder
 Ash
 Aspen
 Basswood
 Ash
 Beech
 Yellow Birch
 Ash
 Cherry
 Cottonwood
 Ash
 Cypress
 Red Elm
 Gum
 Hackberry
 White Oak
 Hickory
 Pecan
 Hard Maple
 White Oak
 Soft Maple
 Red Oak
 Red Oak
 White Oak
 Poplan
 Sassafras
 Sycamore
 Black Walnut
 Will
 
 样例输出
 Ash 13.7931
 Aspen 3.4483
 Basswood 3.4483
 Beech 3.4483
 Black Walnut 3.4483
 Cherry 3.4483
 Cottonwood 3.4483
 Cypress 3.4483
 Gum 3.4483
 Hackberry 3.4483
 Hard Maple 3.4483
 Hickory 3.4483
 Pecan 3.4483
 Poplan 3.4483
 Red Alder 3.4483
 Red Elm 3.4483
 Red Oak 6.8966
 Sassafras 3.4483
 Soft Maple 3.4483
 Sycamore 3.4483
 White Oak 10.3448
 Willow 3.4483
 Yellow Birch 3.4483
 
 本题来自POJ 2418，提交后能够Accepted
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000   //NO MORE THAN 1000 TREE SPECIES，如果是10000，会MEMORY LIMIT EXCEEDED
#define CHAR_COUNT 128 //ASCII编码范围
#define MAX_WORD_LEN 30 //树名字的最大长度
#define MAX_NODE_COUNT ((MAXN * MAX_WORD_LEN) + 1) //TRIE中节点数目

///@breif trie树节点定义
typedef struct trie_node_t
{
    trie_node_t *next[CHAR_COUNT];
    int count;  //该单词出现的次数
}trie_node_t;

///@brief trie树定义
typedef struct trie_tree_t
{
    trie_node_t *root;
    int size;
    trie_node_t nodes[MAX_NODE_COUNT];
}trie_tree_t;

///@brief 创建trie树
///@param 无
///@return 返回创建的trie对象指针
trie_tree_t* trie_tree_create()
{
    trie_tree_t *tree = (trie_tree_t*)malloc(sizeof(trie_tree_t));
    tree->root = &(tree->nodes[0]);
    memset(tree->nodes, 0, sizeof(tree->nodes));
    tree->size = 1;
    return tree;
}

///@brief 销毁trie树
///@param[in] tree trie树指针
///@return 无
void trie_tree_destroy(trie_tree_t *tree)
{
    free(tree);
    tree = NULL;
}

///@brief 将当前trie树中的所有节点信息清空
///@param[in] tree trie树指针
///@return 无
void trie_tree_clear(trie_tree_t *tree)
{
    memset(tree->nodes, 0, sizeof(tree->nodes));
    tree->size = 1;
}

///@brief 在当前树中插入word字符串
///@param[in] tree trie树指针
///@param[in] word 待插入的字符串
///@return 无
void trie_tree_insert(trie_tree_t *tree, char *word)
{
    trie_node_t *p = tree->root;
    while (*word)
    {
        if (p->next[*word] == NULL)
        {
            p->next[*word] = &(tree->nodes[tree->size++]);
        }
        p = p->next[*word];
        word++;
    }
    p->count++;
    return;
}

int trees_num = 0;  //树木的数目

///@brief 深度优先遍历trie树
///@param[in] root trie树根节点
///@return 无
void dfs_travel(trie_node_t *root)
{
    static char word[MAX_WORD_LEN+1];   //中间结果
    static int pos; //当前位置
    
    if (root->count)    //如果count不为0，则肯定找到了一个单词
    {
        word[pos] = '\0';
        printf("%s %0.4f\n", word, ((float)root->count * 100) / trees_num);
    }
    for (int i = 0; i < CHAR_COUNT; i++)
    {
        if (root->next[i])
        {
            word[pos++] = i;
            dfs_travel(root->next[i]);
            pos--;
        }
    }
}

int main()
{
    char line[MAX_WORD_LEN+1];
    trie_tree_t *trie_tree = trie_tree_create();
    
    while (gets(line))
    {
        trie_tree_insert(trie_tree, line);
        trees_num++;
    }
    dfs_travel(trie_tree->root);
    trie_tree_destroy(trie_tree);
    
    return 0;
}

