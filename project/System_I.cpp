#include "System_I.h"
using namespace std;

void CalculateCheckCode(unsigned int &Err,string& CC_,char& CheckCode)
{
	RemoveSeparator(CC_);
	if(CC_.length()!=SYS_I_UNCOMCC_LEN)
	{
		Err=1;
		return;
	}
	int num[SYS_I_UNCOMCC_LEN];//保证传入的字符串长度为9
	Base_32_legality_with_An_Arr(Err,CC_,num);//Base32正确性
	if(Err)
	{
		return;
	}

	int sum=0;
	for(int i=0;i<9;i++){				//去掉分隔符前9位
		if(i%2==0){					//从左到右奇数位上的数字（统一为32进制）
			sum+=num[i]*WEIGHT;
		}
		else{						//从左到右偶数位上的数字
			sum+=num[i];
		}
	}
	sum%=32;
	CheckCode=charNum2sym[32-sum];		//得到大写验证码
}

bool VerifyCC( string& CC ,char& CheckCode)
{
	int len=CC.length();
	char tobeComp=CC[len-1];//最后一个字符
	unsigned int Err=0;
	string CC_=CC.erase(len-1,1);
	char toComp;//正确的checkcode
	CalculateCheckCode(Err,CC_,toComp);
	if (Err)
	{
		CheckCode='#';
		return 0;
	}

	if (toComp==tobeComp)
	{
		return 1;
	}
	else {
		CheckCode=toComp;
		return 0;
	}
}
