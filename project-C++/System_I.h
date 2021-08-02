#ifndef SYSTEM_I_H
#define SYSTEM_I_H

#include <string>
#include "Base32.h"
using namespace std;
#define SYS_I_CC_LEN 10 //编码系统I的联系码长度
#define SYS_I_CHECKCODE_LEN 1 //编码系统I的校验码长度
#define SYS_I_UNCOMCC_LEN (SYS_I_CC_LEN-SYS_I_CHECKCODE_LEN) //除去校验码的联系码长度

#define WEIGHT 7;//校验位的权

void CalculateCheckCode(unsigned int &Err,string& CC_,char& CheckCode);	/*计算校验码*/
bool VerifyCC(string& CC,char& CheckCode);//验证整码的正确性


#endif