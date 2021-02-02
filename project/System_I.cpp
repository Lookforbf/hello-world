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
	int num[SYS_I_UNCOMCC_LEN];//��֤������ַ�������Ϊ9
	Base_32_legality_with_An_Arr(Err,CC_,num);//Base32��ȷ��
	if(Err)
	{
		return;
	}

	int sum=0;
	for(int i=0;i<9;i++){				//ȥ���ָ���ǰ9λ
		if(i%2==0){					//����������λ�ϵ����֣�ͳһΪ32���ƣ�
			sum+=num[i]*WEIGHT;
		}
		else{						//������ż��λ�ϵ�����
			sum+=num[i];
		}
	}
	sum%=32;
	CheckCode=charNum2sym[32-sum];		//�õ���д��֤��
}

bool VerifyCC( string& CC ,char& CheckCode)
{
	int len=CC.length();
	char tobeComp=CC[len-1];//���һ���ַ�
	unsigned int Err=0;
	string CC_=CC.erase(len-1,1);
	char toComp;//��ȷ��checkcode
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
