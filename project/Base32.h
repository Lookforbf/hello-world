/*
	32���ƹ淶�ο�
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


void Base_32_legality(unsigned int &Err,//������ʾ
					string& rstring,//ԭʼ�ַ���
					int mode=0);//ָ��mode==1ʱ������Сд��ĸ����
void Base_32_legality_with_An_Arr(unsigned int &Err,string& rstring,int *empty_arr);//Base_32�Ϸ�����֤˳���ṩ10��������

#endif

