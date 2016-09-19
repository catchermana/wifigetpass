#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;
using std::vector;
using std::regex;
using std::cout;
using std::endl;

void regexUser(const char *file,vector<string>& value)
{
	ifstream in(file);  
    string filename;  
    string line;
	std::regex regex ("[^(�����û������ļ� : )].*"); //"\\b(sub)([^ ]*)"
	std::regex pattern ("(.*)(����)(.*)");
	std::smatch m;
  
    if ( in )
    {  
        while ( getline (in, line) ) // line�в�����ÿ�еĻ��з�  
        {   
			if ( std::regex_match(line,pattern) )
			{
				if ( std::regex_search (line,m,regex) )
				{
					//std::cout << m.str(0) << std::endl;
					value.push_back(m.str(0));
				}
			}
        }  
    }  
    else 
    {  
        std::cout <<"no such file" << std::endl;  
    }
}

void regexPwd( const char *file ,const string& user )
{
	ifstream in(file);  
    string filename;  
    string line;
	std::regex regex ("[^(�ؼ�����            : )].*"); //"\\b(sub)([^ ]*)"
	std::regex pattern ("(.*)(�ؼ�����)(.*)");
	std::smatch m;

	if ( in )
    {  
        while ( getline (in, line) ) // line�в�����ÿ�еĻ��з�  
        {   
			if ( std::regex_match(line,pattern) )
			{
				if ( std::regex_search (line,m,regex) )
				{
					std::cout << "wifi: "<<user << " password: " << m.str(0) << std::endl;
				}
			}
        }  
    }  
    else 
    {  
        std::cout <<"no such file" << std::endl;  
    }
}

int main()
{
	
	vector<string> value;
	string user;
	char *file = "tmp";

	string command = "netsh wlan show profiles > tmp";
	system(command.c_str());
	regexUser(file,value);

	
	/* �����û����鿴��Ӧ����,netsh wlan show profiles name="yjftest" key=clear > tmp*/
	char cmd[100];
	vector<string>::iterator iter;
	for ( iter = value.begin(); iter != value.end(); ++iter )
	{
		user = *iter;
		sprintf(cmd,"netsh wlan show profiles name=%s key=clear > tmp",user.c_str());
		system(cmd);
		regexPwd(file,user);
	}
	return 0;
}