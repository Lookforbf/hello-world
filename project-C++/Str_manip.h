/*����һ���ַ�������*/

#ifndef STR_MANIP_H
#define STR_MANIP_H

#include <string>
#include <sstream>

using namespace std;

void UpCase(string& rstring);/*��Сд����ɴ�д*/

void RemoveSeparator(string& rstring);/*�Ƴ����еķָ���*/

bool isDataLegal(string& rstring);//�ж����ڸ�ʽ�Ƿ���ȷ

void str_rvs(string& rstring);//��ת�ַ���


#endif