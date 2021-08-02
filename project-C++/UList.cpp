#include "UList.h"
#include "Base32.h"
#include <sstream>
using namespace std;



AnULine::AnULine()
{
	//char Emp[2] = "";
	char Emp[6]="EmPtY";
	strcpy_s(Index_code,7,Emp);
	strcpy_s(ConectionCode,11,Emp);
	strcpy_s(Allocate_time,11,Emp);
	NumOfThatDay= 0;
	strcpy_s(Name,41,Emp);
	strcpy_s(Remarks,13,Emp);
}

AnULine::AnULine(string& temp,unsigned int& Err,string& warning)
{
	setAll(temp,Err,warning);
}

void AnULine::ErrAnalyze(unsigned int Err,string& warning)
{
	if(!Err)return;
	stringstream ss;
	ss<<"There are some errors in a U line:"<<endl;
	int ErrCount=1;
	if(Err&1){
		ss<<"Error "<<ErrCount<<":The number of elements is not Legal. You should input "<<ELEMENTS_OF_AULINE<<" elements in a line."<<endl;
		ErrCount++;
	}
	if((Err>>1)&1){
		ss<<"Error "<<ErrCount<<":The Index Code is Wrong!"<<endl;
		ErrCount++;
	}
	if((Err>>2)&1){
		ss<<"Error "<<ErrCount<<":The CC is Wrong!"<<endl;
		ErrCount++;
	}
	if((Err>>3)&1){
		ss<<"Error "<<ErrCount<<":The Time is Wrong!"<<endl;
		ErrCount++;
	}
	if((Err>>4)&1){
		ss<<"Error "<<ErrCount<<":The Number of that day is Wrong!"<<endl;
		ErrCount++;
	}
	if((Err>>5)&1){
		ss<<"Error "<<ErrCount<<":The Name is too long!"<<endl;
		ErrCount++;
	}
	if((Err>>6)&1){
		ss<<"Error "<<ErrCount<<":The Remark is too long!"<<endl;
		ErrCount++;
	}
	warning=ss.str();
}

void AnULine::setAll(string& temp,unsigned int &Err,string& warning)
{
	stringstream ss;
	string s1,s2,s3,s4,s5,s6;
	ss<<temp;
	int count=0;
	while(!ss.eof())
	{
		string tempp;
		ss>>tempp;
		count++;
	}
	if(count!=6)
	{
		Err+=1;
		ErrAnalyze(Err,warning);
		return;
	}
	ss.clear();
	ss<<temp;
	ss>>s1>>s2>>s3>>s4>>s5>>s6;
	setIndex_code(s1,Err);
	setConectionCode(s2,Err);
	setAllocate_time(s3,Err);
	setNumOfThatDay(s4,Err);
	setName(s5,Err);
	setRemarks(s6,Err);
	if(Err)
	{
		ErrAnalyze(Err,warning);
		return;
	}
	
}

void AnULine::getAll(string& temp,int mode)
{
	stringstream ss;
	if(mode==0)
		ss<<Index_code<<" "<<ConectionCode<<" "<<Allocate_time<<" "<<NumOfThatDay<<" "<<Name<<" "<<Remarks;
	else
		ss<<Index_code<<"	"<<ConectionCode<<"	"<<Allocate_time<<"	"<<NumOfThatDay<<"	"<<Name<<"	"<<Remarks;
	temp=ss.str();
}

void AnULine::getIndex_code(string& temp)
{
	temp=Index_code;
}
void AnULine::getConectionCode(string& temp)
{
	temp=ConectionCode;
}

void AnULine::getAllocate_time(string& temp)
{
	temp=Allocate_time;
}
void AnULine::getNumOfThatDay(int& temp)
{
	temp=NumOfThatDay;
}
void AnULine::getName(string& temp)
{
	temp=Name;
}
void AnULine::getRemarks(string& temp)
{
	temp=Remarks;
}


void AnULine::setIndex_code(string& temp,unsigned int& Err)
{
	int len=temp.length();
	UpCase(temp);
	if(len!=6||temp[0]!='U'||temp[1]!='0')
	{
		Err+=2;
		return;
	}
	unsigned int Err_temp=0;
	string _temp=temp;
	Base_32_legality(Err_temp,temp.erase(0,1));//注意哦，U在Base_32里面是不合法的
	if(Err_temp)
	{
		Err+=2;
		return;
	}
	strcpy_s(Index_code,7,_temp.c_str());
}

void AnULine::setConectionCode(string& temp,unsigned int& Err)
{
	RemoveSeparator(temp);//储存的时候不要存分隔符
	int len=temp.length();
	if(len!=CC_LENGHT)//长度不合法
	{
		Err+=4;
		return;
	}
	unsigned int Err_temp=0;
	Base_32_legality(Err_temp,temp);
	if(Err_temp)//Base_32不合法
	{
		Err+=4;
		return;
	}
	//////*******没有进行验证码检验*******//////////
	UpCase(temp);//都存大写
	strcpy_s(ConectionCode,11,temp.c_str());

	
}
void AnULine::setAllocate_time(string& temp,unsigned int& Err)
{
	if(!isDataLegal(temp)){
		Err+=8;
		return;
	}
	strcpy_s(Allocate_time,11,temp.c_str());
}
void AnULine::setNumOfThatDay(string& temp,unsigned int& Err)
{
	int len=temp.length();
	if(len==1)
	{
		temp[0]=toupper(temp[0]);
		char num=temp.at(0);
		int i;
		for(i=0;i<32;i++)
		{
			if(num==charNum2sym[i])
			{
				break;
			}
		}
		if(i==32)//即不符合Base_32
		{
			Err+=16;
			return;
		}
		NumOfThatDay=i;
		return;
	}
	else if(len==2&&isdigit(temp[0])&&isdigit(temp[1]))//输入的是个十进制的两位数
	{
		stringstream ss;
		ss<<temp;
		int i;
		ss>>i;
		NumOfThatDay=i;
		return;
	}

	//错误输入
	Err+=16;

}
void AnULine::setName(string& temp,unsigned int& Err)
{
	if(temp.length()>=41)
	{
		//cout<<temp.length()<<"namel"<<endl;
		Err+=32;
		return;
	}
	strcpy_s(Name,41,temp.c_str());
}
void AnULine::setRemarks(string& temp,unsigned int& Err)
{
	if(temp.length()>=13)
	{
		//cout<<temp.length()<<"namel"<<endl;
		Err+=64;
		return;
	}
	strcpy_s(Remarks,13,temp.c_str());
}

void AnULine::AutoGenAllocate_time()//注意这里并不通过set函数设置
{
	time_t now = time(0);
	tm* ltm=localtime(&now);
	stringstream ss;
	int year=ltm->tm_year + 1900;
	int month=ltm->tm_mon+1;
	int day=ltm->tm_mday;
	ss<<year<<"/"<<month<<"/"<<day;
	string ssstr=ss.str();
	strcpy_s(Allocate_time,11,ssstr.c_str());
}

void AnULine::GenIndex_code( int NOTD,unsigned int &Err )
{
	unsigned int Err_temp=0;
	string b32_1;
	int_DEC2str_Base32(Err_temp,b32_1,NOTD);
	stringstream ss;
	ss<<"U0";
	int days=(time(0)-UNIX_TIME_AT_TZTO)/SECONDS_OF_A_DAY;//“魔数”已修复

	string b32_2;
	int_DEC2str_Base32(Err_temp,b32_2,days);

	if (Err_temp)
	{
		Err+=2;
		return;
	}
	//日期编码部分有三个字符
	if (b32_2.length()==1)
	{
		b32_2="00"+b32_2;
	}
	else if(b32_2.length()==2)
	{
		b32_2="0"+b32_2;
	}
	ss<<b32_2<<b32_1;
	setIndex_code(ss.str(),Err);
}

void AnULine::GeneralMode( unsigned int &Err,string& FourElementsAline ,string& warning)
{
	stringstream ss;
	ss<<FourElementsAline;
	string CC;
	string NOTD;
	string Nm;
	string Rms;
	ss>>CC>>NOTD>>Nm>>Rms;

	setNumOfThatDay(NOTD,Err);
	GenIndex_code(NumOfThatDay,Err);
	setConectionCode(CC,Err);
	AutoGenAllocate_time();
	setName(Nm,Err);
	setRemarks(Rms,Err);
	if (Err)
	{
		ErrAnalyze(Err,warning);
		return;
	}
}

unsigned int aul_bnr_writeapp( string& FileName,AnULine a )
{
	fstream bnrio;
	bnrio.open(FileName.c_str(),ios::out|ios::binary|ios::app);
//	bnrio.seekp(ios::end);
	bnrio.write(reinterpret_cast<char*>(&a),sizeof(AnULine));
	bnrio.close();

	//修改aulf头(理解不深，只能重新打开了）
	AulFile aulf;
	bnrio.open(FileName.c_str(),ios::in|ios::out|ios::binary);
	bnrio.seekg(ios::beg);
	bnrio.read(reinterpret_cast<char*>(&aulf),sizeof(AulFile));
	int num=aulf.getSum();
	aulf.setSum(num+1);
	aulf.setTime();
	bnrio.seekp(ios::beg);
	bnrio.write(reinterpret_cast<char*>(&aulf),sizeof(AulFile));
	bnrio.close();
	return 0;
}

unsigned int aul_bnr_read( string& FileName,string& outpt,int mode,int startLine)
{
	AnULine a;
	string temp;
	fstream bnrio;
	bnrio.open(FileName.c_str(),ios::in|ios::binary);
	stringstream ss;
	if(mode==0){//单条读入模式
		if(startLine<1)return 1;
		bnrio.seekg(sizeof(AulFile)+sizeof(AnULine)*(startLine-1));
		bnrio.read(reinterpret_cast<char*>(&a),sizeof(AnULine));
		a.getAll(temp);
		ss<<temp<<endl;
		bnrio.close();
	}
	else if(mode==1){//表格全部显示
		bnrio.seekg(sizeof(AulFile));
		bnrio.read(reinterpret_cast<char*>(&a),sizeof(AnULine));
		while(!bnrio.eof()){
			a.getAll(temp);
			ss<<temp<<endl;
			bnrio.read(reinterpret_cast<char*>(&a),sizeof(AnULine));
		}
		bnrio.close();
	}
	else if(mode==2){//表格输出，搭上魔数匹配，文件头
		AulFile aulf;
		bnrio.read(reinterpret_cast<char*>(&aulf),sizeof(AulFile));
		string outputt;
		unsigned opErr=aulf_get_prt(aulf,outputt);
		if(opErr){
			//cout<<"文件类型错误！"<<endl;
			return 1;
		}
		ss<<outputt<<"序号"<<"	"<<"索引码"<<"	"<<"  联系码"<<"	"<<" 发码时间"<<"	"<<"i"<<"	"<<"书名"<<"	"<<"备注"<<endl;
		bnrio.read(reinterpret_cast<char*>(&a),sizeof(AnULine));
		int i=1;
		while(!bnrio.eof()){
			a.getAll(temp,1);
			ss<<i<<"	"<<temp<<endl;
			i++;
			bnrio.read(reinterpret_cast<char*>(&a),sizeof(AnULine));
		}
		bnrio.close();
		ss<<endl<<"------------------------------  END  ------------------------------"<<endl;
	}
	else return 1;

	outpt=ss.str();
	return 0;
}

void Modify_AULine_MODE( string& FileName,string& outpt,AnULine a,int startLine )
{
	if(startLine<1)
	{
		cout<<"数字不合法！"<<endl;
		return;
	}
	AnULine new_a;
	AulFile aulf;
	fstream bnrio;
	bnrio.open(FileName.c_str(),ios::in|ios::out|ios::binary);
	bnrio.read(reinterpret_cast<char*>(&aulf),sizeof(AulFile));
	bnrio.seekg(sizeof(AnULine)*(startLine-1));
	bnrio.read(reinterpret_cast<char*>(&new_a),sizeof(AnULine));
	string t;
	new_a.getAll(t);
	cout<<">修改提示<"<<endl;
	cout<<"行"<<startLine<<"："<<endl<<"-"<<t<<endl;
	a.getAll(t);
	cout<<"将修改为"<<endl<<"+"<<t<<endl;
	cout<<"确定请输入数字'1':";
	int cf=0;
	cin>>cf;
	if (cf!=1)
	{
		cout<<"修改取消。"<<endl;
		bnrio.close();
	}
	new_a=a;
	bnrio.seekp(sizeof(AulFile)+sizeof(AnULine)*(startLine-1));
	bnrio.write(reinterpret_cast<char*>(&new_a),sizeof(AnULine));
	//修改aulf头
	aulf.setTime();
	bnrio.seekp(ios::beg);
	bnrio.write(reinterpret_cast<char*>(&aulf),sizeof(AulFile));

	bnrio.close();
}

unsigned int aulf_get_prt(AulFile aulf,string& outpt)
{
	stringstream ss;
	if (!aulf.cmpMagicNum())
	{
		//cout<<"文件类型错误！"<<endl;
		return 1;
	}
	ss<<"上次修改时间："<<aulf.getTime()<<endl;
	ss<<"总条目数："<<aulf.getSum()<<endl;
	ss<<"备注："<<aulf.getRemark()<<endl<<endl;
	ss<<"-----------------------------  BEGIN  -----------------------------"<<endl<<endl;;
	outpt=ss.str();
	return 0;
}

bool AulFile::cmpMagicNum()
{
	if (magic_num!=MAGIC_NUM_OF_AUL)
	{
		return false;
	}
	return true;
}

std::string AulFile::getTime()
{
	string t=lastModiTime;
	return t;
}

int AulFile::getSum()
{
	return sum;
}

std::string AulFile::getRemark()
{
	string t=Remarks;
	return t;
}

void AulFile::setSum(int num)
{
	if (sum<0)
	{
		sum=0;
	}
	sum=num;
}

void AulFile::setTime()
{
	time_t now = time(0);
	tlastModiTime=now;
	tm* ltm=localtime(&now);
	stringstream ss;
	int year=ltm->tm_year + 1900;
	int month=ltm->tm_mon+1;
	int day=ltm->tm_mday;
	int h=ltm->tm_hour;
	int m=ltm->tm_min;
	int s=ltm->tm_sec;

	ss<<year<<"/"<<month<<"/"<<day<<" "<<h<<":"<<m<<":"<<s;
	string ssstr=ss.str();
	strcpy_s(lastModiTime,20,ssstr.c_str());
}

void AulFile::setMagicNum()
{
	magic_num=MAGIC_NUM_OF_AUL;
}

void AulFile::setRemark( string& temp )
{
	if(temp.length()>=51)return;
	strcpy_s(Remarks,51,temp.c_str());
}

void AulFile::tryaddNOTD()
{
	time_t now=time(0);
	time_t past=tlastModiTime;
	if (now-past>=SECONDS_OF_A_DAY)
	{
		numOfThatDay=0;//第二天重设
	}
	else
	{
		numOfThatDay++;
	}

}

void AulFile::resetNOTD()
{
	numOfThatDay=0;
}


unsigned int aulf_creat( string& FileName )
{
	fstream bnrio;
	AulFile aulf;
	aulf.setMagicNum();
	aulf.setSum(0);
	aulf.setTime();
	aulf.resetNOTD();
	string rms="[empty]";
	aulf.setRemark(rms);
	bnrio.open(FileName.c_str(),ios::out|ios::binary);
	bnrio.write(reinterpret_cast<char*>(&aulf),sizeof(AulFile));
	bnrio.close();
	return 0;
}

unsigned int aulf_copy_or_delete( string& OldName,string& NewName,int* linesToBeDel )
{
	fstream bnrio_old;
	fstream bnrio_new;
	AulFile aulf_temp;
	bnrio_old.open(OldName.c_str(),ios::in|ios::binary);
	bnrio_old.read(reinterpret_cast<char*>(&aulf_temp),sizeof(AulFile));
	bnrio_new.open(NewName.c_str(),ios::out|ios::binary);
	bnrio_new.write(reinterpret_cast<char*>(&aulf_temp),sizeof(AulFile));
	int li=0,dli=0;
	bool symOfContinueToComp=true;
	AnULine a;
	bnrio_old.read(reinterpret_cast<char*>(&a),sizeof(AnULine));
	while(!bnrio_old.eof())
	{
		if(symOfContinueToComp&&linesToBeDel[dli]==0)
		{
			symOfContinueToComp=false;
		}

		if(symOfContinueToComp&&li+1==linesToBeDel[dli])
		{
			dli++;li++;
			bnrio_old.read(reinterpret_cast<char*>(&a),sizeof(AnULine));
			continue;
		}
		else
		{
			li++;
			bnrio_new.write(reinterpret_cast<char*>(&a),sizeof(AnULine));
			bnrio_old.read(reinterpret_cast<char*>(&a),sizeof(AnULine));
		}
	}
	bnrio_new.close();
	bnrio_old.close();
	return 0;
}

void CopyOrDelete_MODE()
{

	/*欢迎*/
	cout<<">>>>>Now you come to Copy Or Delete ULines Mode."<<endl;
	cout<<"@:Enter 【0】, you can copy a file to a new file. But I think you would never use this function :-)"<<endl;
	cout<<"@:Enter indexs of the line you would like to delete, new file names as well, you can delete some lines of an old file and get a new version of that file. ATTENTINON:You should enter nums no more than 20 at once. Please enter nums in a line end with 【0】."<<endl;
	int sym=-1;
	while (true)
	{
		sym++;
		if(sym){
			cout<<"Continue?Enter 【1】 if you want to continue this MODE"<<endl;
			int tempp;
			cin>>tempp;
			if(tempp!=1)break;
		}
		cout<<"Please Enter OldFileName and NewFileName"<<endl;
		string oldf,newf;
		cin>>oldf>>newf;
		int linesToBeDel[21]={0};
		int temp,i;
		cout<<"Please Enter nums end with 【0】."<<endl;
		for(i=0;i<20;i++)
		{
			cin>>temp;
			if (!temp)
			{
				break;
			}
			linesToBeDel[i]=temp;
		}
		if(i==21){
			cout<<"@:Error! Too much nums or【0】hasn't found!"<<endl;
			cout<<"Please Enter Again!"<<endl;
			continue;
		}
		sort(linesToBeDel,linesToBeDel+i);
		int j=0;
		while(linesToBeDel[j]!=0)
		{
			cout<<"Line "<<linesToBeDel[j]<<" "<<endl;
			j++;
		}
		if (j==0)
		{
			cout<<"@:No lines will be delete."<<endl;
			cout<<"@:"<<oldf<<" will copy to "<<newf<<endl;
		}
		else{
			cout<<"will be delete. New file's name is "<<newf<<endl;
		}
		unsigned int Err=aulf_copy_or_delete(oldf,newf,linesToBeDel);
		if (Err)
		{
			cout<<"There is an Error in aulf_copy_or_delete()!"<<endl;
			continue;
		}
	}
	cout<<"Exit."<<endl<<endl;
}
