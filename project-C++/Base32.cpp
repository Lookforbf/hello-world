#include "Base32.h"

using namespace std;

enum DECto32{
	A = 10,B,C,D,E,F,G,H,J,K,M,N,P,Q,R,S,T,V,W,X,Y,Z
}dto32;

int sym2num[26]={A,B,C,D,E,F,G,H,-1,J,K,-1,M,N,-1,P,Q,R,S,T,-1,V,W,X,Y,Z};
char charNum2sym[32]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','J','K','M','N','P','Q','R','S','T','V','W','X','Y','Z'};


void Base_32_legality(unsigned int &Err,string& rstring,int mode)
{
	Err=0;
	int len=rstring.length();
	for(int i=0;i<len;i++){
		char temp=rstring.at(i);
		if(temp<='9'&&temp>='0')				//����0~9
			continue;
		else if((temp>='A'&&temp<='Z')||(temp>='a'&&temp<='z'))
		{							//32������ĸ
			if(mode==1&&temp>='a'&&temp<='z')//mode==1ģʽ������Сд��ĸ����
			{
				Err+=1;
				return;
			}
			temp=toupper(temp);
			int ind=static_cast<int>(temp)-'A';
			if(sym2num[ind]<0){	//���ڷǷ���д��ĸ
				Err+=2;
				return;
			}
		}
		else							//���ڷǷ�����
		{
			Err+=4;
			return;
		}
	}

}


void Base_32_legality_with_An_Arr(unsigned int &Err,string& rstring,int *empty_arr)
{
	Err=0;
	int len=rstring.length();//�����������С��������ַ�������
	if(len==0){
		Err+=1;
		return;
	}
	//int *num = new int[len];
	for(int i=0;i<len;i++){
		char temp=rstring.at(i);
		if(temp<='9'&&temp>='0')				//����0~9
			empty_arr[i]=temp-'0';
		else if((temp>='A'&&temp<='Z')||(temp>='a'&&temp<='z'))
		{																//32������ĸ
			temp=toupper(temp);
			int ind=static_cast<int>(temp)-'A';
			if(sym2num[ind]<0){	//���ڷǷ���д��ĸ
				Err+=2;
				return;
			}
			empty_arr[i]=sym2num[ind];
		}
		else							//���ڷǷ�����
		{
			Err+=4;
			return;
		}
	}
}

void int_DEC2str_Base32( unsigned int &Err,string& b32str,int num )
{
	Err=0;
	if(num<0)
	{
		Err=1;
		return;
	}
	stringstream ss;
	while(num>=32)
	{
		int temp=num%32;
		char c=charNum2sym[temp];
		num/=32;
		ss<<c;
	}
	char c=charNum2sym[num];
	ss<<c;
	string rvrs_str=ss.str();
	str_rvs(rvrs_str);
	b32str=rvrs_str;
}
