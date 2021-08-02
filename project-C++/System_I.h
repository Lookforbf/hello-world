#ifndef SYSTEM_I_H
#define SYSTEM_I_H

#include <string>
#include "Base32.h"
using namespace std;
#define SYS_I_CC_LEN 10 //����ϵͳI����ϵ�볤��
#define SYS_I_CHECKCODE_LEN 1 //����ϵͳI��У���볤��
#define SYS_I_UNCOMCC_LEN (SYS_I_CC_LEN-SYS_I_CHECKCODE_LEN) //��ȥУ�������ϵ�볤��

#define WEIGHT 7;//У��λ��Ȩ

void CalculateCheckCode(unsigned int &Err,string& CC_,char& CheckCode);	/*����У����*/
bool VerifyCC(string& CC,char& CheckCode);//��֤�������ȷ��


#endif