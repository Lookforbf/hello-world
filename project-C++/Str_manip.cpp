#include "Str_manip.h"
using namespace std;

void UpCase(string& rstring){
	int len=rstring.length();
	for(int i=0;i<len;i++){
		rstring[i]=toupper(rstring[i]);
	}
}

/*ÒÆ³ýÂëÖÐµÄ·Ö¸ô·û*/
void RemoveSeparator(string& rstring){
	int len=rstring.length();
	for(int i=len-1;i>0;i--){
		char temp=rstring.at(i);
		if(temp=='-'||temp=='/'||temp=='\\'){
			rstring.erase(i,1);
		}
	}
}
bool isDataLegal(string& rstring)
{
	int len=rstring.length();
	if(len!=10)return false;
	if(rstring[4]!='/'||rstring[7]!='/')return false;
	return true;
}

void str_rvs( string& rstring )
{
	stringstream ss;
	int len=rstring.length();
	for(int i=len-1;i>=0;i--)
	{
		char c=rstring[i];
		ss<<c;
	}
	rstring=ss.str();
}
