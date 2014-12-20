﻿///@file 约瑟夫问题
///@author zhaowei
///@date 2014.12.20
///@version 1.0
/* @note
   描述
   有编号从1到N的N个小朋友在玩一种出圈的游戏。开始时N个小朋友围成一圈，编号为
   i+1的小朋友站在编号为i小朋友左边。编号为1的小朋友站在编号为N的小朋友左边。首先编号
   为1的小朋友开始报数，接着站在左边的小朋友顺序报数，直到数到某个数字M时就出圈。直到
   只剩下1个小朋友，则游戏完毕。现在给定N，M，求N个小朋友的出圈顺序。

   输入
   唯一的一行包含两个整数N，M(1 <= N，M <= 30000)。

   输出
   唯一的一行包含N个整数，每两个整数中间用空格隔开，第i个整数表示第i个出圈的小朋友的编号。
   
   样例输入
   5 3

   样例输出
   3 1 5 2 4

*/
