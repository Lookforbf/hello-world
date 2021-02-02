/*我有一套字符处理技术*/

#ifndef STR_MANIP_H
#define STR_MANIP_H

#include <string>
#include <sstream>

using namespace std;

void UpCase(string& rstring);/*把小写都变成大写*/

void RemoveSeparator(string& rstring);/*移除码中的分隔符*/

bool isDataLegal(string& rstring);//判断日期格式是否正确

void str_rvs(string& rstring);//翻转字符串


#endif