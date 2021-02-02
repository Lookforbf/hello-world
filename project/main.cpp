#include <iostream>
#include <fstream>
#include "UList.h"
#include "Base32.h"
#include "System_I.h"
using namespace std;

void CalculateCheckCode_Mode(){
	/*欢迎*/
	cout<<">>>>>Welcome to Calculating Check Code Mode."<<endl;
	cout<<"@:Now you can input CCs WITHOUT CHECK CODE and the program will output the corresponding Check Code. "<<endl;
	cout<<"@:Please enter a CC per line."<<endl;
	string CC_;
	while(cin>>CC_){
		/* 系统退出 */
		if(CC_=="q"||CC_=="Q")break;

		/*进入函数准备*/
		unsigned int Err=0;
		char CheckCode;
		CalculateCheckCode(Err,CC_,CheckCode);
		if(Err){
			cout<<"@:Wrong Code!"<<endl;
			cout<<"@:Please enter again!"<<endl;
			continue;
		}

		cout<<"@:get Check Code '"<<CheckCode<<"'"<<endl;

		/*输出全部大写*/
		UpCase(CC_);

		string CompleteCode=CC_+CheckCode;
		//带着分隔符输出
		CompleteCode.insert(9,"-");
		CompleteCode.insert(8,"-");
		CompleteCode.insert(4,"-");
		cout<<CompleteCode<<endl;
	}
	/*退出*/
	cout<<"<Exit.>"<<endl<<endl;
}

void VerifyCC_Mode(){
	/*欢迎*/
	cout<<">>>>>Welcome to Verify CC Mode."<<endl;
	cout<<"@:Now you can input CCs to verify it. Please enter a CC per line."<<endl;
	string CC;
	while(cin>>CC){
		/* 系统退出 */
		if(CC=="q"||CC=="Q")break;

		char CheckCode;
		if(!VerifyCC(CC,CheckCode)){
			cout<<"@:Check code does not match!"<<endl;
			cout<<"@:The Check code should be '"<<CheckCode<<"'"<<endl;
			cout<<"@:Hint:if CheckCode is '#', it means the CC you input is incorrect."<<endl;
		}
		else{
			cout<<"@:Verification passed."<<endl;
		}
	}
	/*退出*/
	cout<<"<Exit.>"<<endl<<endl;
}

int main()
{
//#define TEST	//测试用的宏开关
#ifdef TEST
	while(true){
		for(int i=0;i<3;i++)
			cout<<"]]]]]]]]]]]]]]]]TEST[[[[[[[[[[[[[[[[[[[["<<endl;
		string t;
		unsigned int Err=0;
		string wn;
		AulFile aulf;
		string name="test.dat";
		aulf_creat(name);
		for(int j=0;j<5;j++)
		{
			getline(cin,t);
			AnULine a(t,Err,wn);
			if(Err){
				cout<<wn<<endl;
				system("pause");
				continue;
			}
			aul_bnr_writeapp(name,a);
		}
		string opt;
		aul_bnr_read(name,opt);
		cout<<opt;

		CopyOrDelete_MODE();
		string opt1;
		string cpt="ctest.dat";
		aul_bnr_read(cpt,opt1);
		cout<<opt1;

		system("pause");
	}
#endif
	while(true){
		cout<<"@you:which mode?"<<endl;
		cout<<"@:CalculateCheckCodeMode:1"<<endl;
		cout<<"@:VerifyCCMode:2"<<endl;
		int mode;
		cin>>mode;
		switch(mode){
		case 1:CalculateCheckCode_Mode();continue;
		case 2:VerifyCC_Mode();continue;
		default:system("pause");exit(0);
		}
	}
	system("pause");
	return 0;
}