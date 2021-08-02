/*
	32进制规范参考
	https://www.crockford.com/base32.html
*/

#ifndef BASE_32_H
#define BASE_32_H
#include "Str_manip.h"
#include <string>
#include <sstream>
using namespace std;

extern int sym2num[26];
extern char charNum2sym[32];

void int_DEC2str_Base32(unsigned int &Err,string& b32str,int num);


void Base_32_legality(unsigned int &Err,//错误提示
					string& rstring,//原始字符串
					int mode=0);//指定mode==1时不允许小写字母出现
void Base_32_legality_with_An_Arr(unsigned int &Err,string& rstring,int *empty_arr);//Base_32合法性验证顺带提供10进制数组

#endif

