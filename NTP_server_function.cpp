#include "NTP_server_header.h"
#include<iostream>//system call, data types
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<fstream>//filehandling
#include<map>//map STL
#include<cstring>//strcpy
#include<stdlib.h>//atoi

#include<time.h>//gmt
using namespace std;
#define size 256
void user_cred_file_to_map(map<string, string> &user_cred)//key,value--->userid,password
{
	ifstream fin;
	string data;
	fin.open("user_Credentials.txt",ios::in);
	while(getline(fin,data))
	{
		string user="",password="";
		int cnt =0;
		for(int i=0;i<data.length();i++)
		{
			if(cnt==2)
			break;
			else if(data[i]==',')
			cnt++;
			else if(cnt==0)
			user+=data[i];
			else if(cnt==1)
			password+=data[i];
		}
		
		user_cred.insert(pair<string,string>(user,password));
	}
	
	fin.close();
	
}

void login_and_registration_of_user(int cli_des,map<string, string> userCred)
{

	while(1)
	 	{
	 		int k=0;
		 	char buffer[size];
		 	bzero(buffer,sizeof(buffer));	 	
		 	int n=read(cli_des,&buffer,sizeof(buffer));
		 	
		 	if(buffer[0]=='1')
		 	{
			 	char ret=user_cred_authentication(userCred,buffer,n);
			 	write(cli_des,&ret,sizeof(ret));
			 	if(ret == '1')
			 		k=1;
		 	}
		 	else if(buffer[0]=='2')
		 	{
			 	user_cred_addition(userCred,buffer,n);//to write user in file and map
			 	char msg='3';
			 	write(cli_des,&msg,sizeof(msg));
			 	k=1;
		 	}
		 	
			 if(buffer[0]=='e' || k==1)
			 break;
		 
	 	}
}


char user_cred_authentication(map<string, string> user_cred, char data[],int n)
{
	int cnt=0;//user,password
	string user="",password="";
	for(int i=1;i<n;i++)
	{
		if(data[i]==',')
		  cnt++;
		else if(cnt==0)
		  user+=data[i];
		else if(cnt==1)
		  password+=data[i];
	}
	
	for(auto i:user_cred)
	{
		if(i.first==user && i.second==password)
		return '1';
		else if(i.first==user)
		return '2';
	}
	return '0';
}



void user_cred_addition(map<string, string> &user_cred,char new_user_info[],int k)
{
	int cnt=0;//user,password
	string user="",password="",data="";
	for(int i=1;i<k;i++)
	{
		if(new_user_info[i]==',')
		  cnt++;
		else if(cnt==0)
		  user+=new_user_info[i];
		else if(cnt==1)
		  password+=new_user_info[i];
		  
		data+=new_user_info[i];
	}
	user_cred.insert(pair<string,string>(user,password));
	
	ofstream fout;
	fout.open("user_Credentials.txt",ios::app);
	fout<<data;
	fout<<"\n";
	fout.close();
}
void best_time_to_GMT_conversion(time_t curr_time,int &GMThour,int &GMTmin,int &GMTsec,int &GMTmday,int &GMTmon,int &GMTyear)
{
	cout<<curr_time<<endl;
	//time_t curr_time;
	//curr_time = time(NULL);
	tm *X = gmtime (&curr_time);
	//cout<<"Current time : "<< X->tm_hour  <<":"<<X->tm_min <<":"<<X->tm_sec<<" GMT"<<endl;
	GMThour=X->tm_hour;
	GMTmin=X->tm_min;
	GMTsec=X->tm_sec;
	GMTmday=X->tm_mday;
	GMTmon=X->tm_mon+1;
	GMTyear=X->tm_year+1900;
	//cout<<"day ->"<<GMTmday<<"/"<<GMTmon<<"/"<<GMTyear<<endl;
	//cout<<GMThour<<endl;

}

void GmT_to_epoch_coversion(int &epochserv,int &GMThour,int &GMTmin,int &GMTsec,int &GMTmday,int &GMTmon,int &GMTyear)
{
	struct tm t={0};//initiazlinzing all to zeros
	time_t epochtime;
	t.tm_year=GMTyear-1900;
	t.tm_mon=GMTmon-1;
	t.tm_mday=GMTmday;
	t.tm_hour=GMThour;
	t.tm_min=GMTmin;
	t.tm_sec=GMTsec;
	//t.tm_isdst=-1;                                //Is DST on ? 1 on yes / 0 on no / -1 on unknown
	epochtime = mktime(&t);
	//cout<<"Seconds since the Epoch is "<< (long) epochtime<<endl;
	epochserv=(long) epochtime;

}

