///@file Babelfish
///@author zhaowei
///@date 2015.01.01
///@version 1.0
/* @note
   描述
   You have just moved from Waterloo to a big city. The people here speak an incomprehensible dialect
   of a foreign language. Fortunately, you have a dictionary to help you understand them.

   输入
   Input consists of up to 100,000 dictionary entries, followed by a blank line, followed by a message
   of up to 100,000 words. Each dictionary entry is a line containing an English word, followed by a
   space and a foreign language word. No foreign word appears more than once in the dictionary. The message
   is sequence of words in the foreign language, one word on each line. Each word in the input is a sequence
   of at most 10 lowercase letters.

   输出
   Output is the message translated to English, one word per line. Foreign words not in the dictionary should 
   be translated as "eh".

   样例输入
   dog ogday
   cat atcay
   pig igpay
   froot ootfray
   loops oopslay

   atcay
   ittenkay
   oppslay

   样例输出
   cat
   eh
   loops

   本题来自于POJ 2503，提交后能够Accepted.
*/

#include <cstdio>
#include <map>
#include <string>
#include <cstring>

using namespace std;

const int MAX_WORD_LEN = 10;	//字符串最大长度

int main()
{
	char line[MAX_WORD_LEN * 3 + 1];
	char s1[MAX_WORD_LEN + 1], s2[MAX_WORD_LEN + 1];
	map<string, string> dict;

	while (gets(line) && line[0] != 0)	//将输入数据读入line
	{	
		sscanf(line, "%s %s", s1, s2);	//将line中信息分为s1和s2
		dict[s2] = s1;
	}

	while (gets(line))
	{
		if (dict[line].length() == 0)	//判断在字典中是否有这个生词
		{
			printf("eh\n");
		}
		else
			printf("%s\n", dict[line].c_str());
	}
	return 0;
}