﻿///@file 线段树练习
///@author zhaowei
///@date 2014.12.15
///@version 1.0
/* @note
描述
一行N(1  N < 100000) 个方格，开始每个格子里都有一个整数。现在动态地提出一些命令请求，有两种命令，查询和增加：求某一个特定的
子区间[a, b]中所有元素的和；指定某一个格子x，加上一个特定的值A。现在要求你能对每个请求作出正确的回答。

输入
输入文件第一行为一个整数N，接下来是n 行每行1 个整数，表示格子中原来的整数。接下来是一个正整数Q，再接下来有Q 行，表示Q 个询问，
第一个整数表示命令代号，命令代号1 表示增加，后面的两个数a 和x 表示给位置a 上的数值增加x，命令代号2 表示区间求和，后面两个整数
a 和b，表示要求[a,b] 之间的区间和。

输出
共Q 行，每个整数

样例输入
6
4
5
6
2
1
3
4
1
3 5
2 1 4
1 1 9
2 2 6

样例输出
22
22
*/