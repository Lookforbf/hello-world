#ifndef ULIST_H
#define ULIST_H
#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>

#include "Str_manip.h"
using namespace std;

#define ELEMENTS_OF_AULINE 6
#define CC_LENGHT 10  //��׼CC����

#define SECONDS_OF_A_DAY 86400//һ�������
#define UNIX_TIME_AT_TZTO 1609430400//2021����Unixʱ���

class AnULine
{
public:
	AnULine();
	AnULine(string& newIc,unsigned int &Err,string& warning);//string& newCC,string& newAt,string& newNPTD,string& newName,string& newRemarks);
	
	void getIndex_code(string& temp);
	void getConectionCode(string& temp);
	void getAllocate_time(string& temp);
	void getNumOfThatDay(int& temp);
	void getName(string& temp);
	void getRemarks(string& temp);
	void getAll(string& temp,int mode=0);

	void setIndex_code(string& temp,unsigned int& Err);
	void setConectionCode(string& temp,unsigned int& Err);
	void setAllocate_time(string& temp,unsigned int& Err);
	void setNumOfThatDay(string& temp,unsigned int& Err);
	void setName(string& temp,unsigned int& Err);
	void setRemarks(string& temp,unsigned int& Err);
	void setAll(string& temp,unsigned int& Err,string& ErrsHint);

	void ErrAnalyze(unsigned int Err,string& warning);//Err��ֵ
	void AutoGenAllocate_time();
	void GenIndex_code(int NOTD,unsigned int &Err);
	void GeneralMode(unsigned int &Err,string& FourElementsAline,string& warning);

	
private:
	char Index_code[7];
	char ConectionCode[11];
	char Allocate_time[11];
	int NumOfThatDay;
	char Name[41];//�ײ�20������
	char Remarks[13];//�ײ�12������
};

unsigned int aul_bnr_writeapp(string& FileName,AnULine a);
unsigned int aul_bnr_read(string& FileName,string& outpt,int mode=2,int startLine=0);
void Modify_AULine_MODE(string& FileName,string& outpt,AnULine a,int startLine);

//��ûʵ��ɾ����

#define MAGIC_NUM_OF_AUL 0xCABCAF78

class AulFile
{
public:
	bool cmpMagicNum();

	string getTime();
	int getSum();
	string getRemark();

	void setTime();
	void setSum(int num);
	void setMagicNum();
	void setRemark(string& temp);
	void tryaddNOTD();//���Լ�
	void resetNOTD();//��Ϊ��
private:
	unsigned int magic_num ;
	char lastModiTime[20];
	time_t tlastModiTime;//����
	int sum;
	char Remarks[51];
	int numOfThatDay;
};

unsigned int aulf_get_prt(AulFile aulf,string& outpt);
unsigned int aulf_creat(string& FileName);
unsigned int aulf_copy_or_delete(string& OldName,string& NewName,int* linesToBeDel);//�̶�ס�洢 ��Ҫɾ�������� ����;��������뱣֤���Ԫ��Ϊ��
void CopyOrDelete_MODE();
//unsigned int aulf_modi(string FileName,int mode=0);//mode==0����ULine��Ҫ���޸�ģʽ

#endif