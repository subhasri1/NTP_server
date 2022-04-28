#include "NTP_client_header.h"
#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<stdio.h>//gets function
#include<cstring>//strcpy

#define size 256
void choice_and_port_set_on_cmd_line_argument(int argc,char *argv[],int &port,int &choice)
{
	int temp_port;
	
	if(argc == 1)
	{	
		choice = 2;
	}
	else if(argc == 2 )
	{
		temp_port=atoi(argv[1]);
		if(temp_port > 3)
		port = atoi(argv[1]);	
		else if(temp_port != 0 && temp_port < 4) 
		{
		cout<<"Provide port Number Greater than 3"<<endl;
		exit(1);
		}
		
		choice = 2;
	}
	else if(argc == 3 )
	{
		temp_port=atoi(argv[1]);
		if(temp_port > 3)
		port = atoi(argv[1]);	
		else if(temp_port != 0 && temp_port < 4) 
		{
		cout<<"Provide port Number Greater than 3"<<endl;
		exit(1);
		}
		
		choice = 1;
	}
}
void newUser :: add_new_User()
{
	string re_password;
	cout<<"\n\nNew User Details "<<endl;
	cout<<"-------------------------------"<<endl;
	
	cout<<"\nEnter your Name :"<<endl<<"=> ";
	//fgets(name,sizeof(name)-1,stdin);
	getline(cin>>ws,name);
	cout<<"Enter User ID :"<<endl<<"=> ";
	cin>>userId;
	cout<<"Enter your Email ID :"<<endl<<"=> ";
	cin>>emailId;
	cout<<"Enter your Mobile Number :"<<endl<<"=> ";
	cin>>mobile;
	while(1)
	{
		cout<<"Enter Password :"<<endl<<"=> ";
		cin>>password;
		cout<<"Enter Re-Password :"<<endl<<"=> ";
		cin>>re_password;
		if(password == re_password)
		{
			break;
		}
		else
		{
			cout<<"\n\nPassword and Re-Password are not same ! \nPlease Enter again\n"<<endl;
		}
	
	}
}
void newUser :: existing_user(string user,int cnt)
{
	if(cnt==3)
	{
	cout<<"\n\nExisting User"<<endl;
	cout<<"------------------------------------"<<endl;
	cout<<"User Id : "<<user<<endl;
	//cout<<"Only "<<cnt<<" Attempts Left !"<<endl;
	/*cout<<"\nEnter Your User ID :"<<endl;
	cin>>temp_User;*/
	cout<<"Enter Your Password :"<<endl<<"=> ";
	cin>>temp_Password;
	}
	else
	{
	cout<<"\nLogin Credentials are Invalid !"<<endl;
	cout<<"Only "<<cnt<<" Attempts Left !"<<endl;
	/*cout<<"\nEnter Your User ID :"<<endl;
	cin>>temp_User;*/
	cout<<"Please enter your Correct Password :"<<endl<<"=> ";
	cin>>temp_Password;
	}
}
string newUser :: newUserDataInOneString()
{
	string sum="2"+userId+","+password+","+emailId+","+mobile+","+name;
	return sum;
}

string newUser :: existingUserCredInOneString(string user)
{
	string sum="1"+user+","+temp_Password;
	return sum;
}

void epoch_to_client_time_zone(long &tot , char buf[size])
{
	time_t xepoch_time=tot;
	
	/*CONVERT To Struct tm */
	struct tm *converted_time;
	converted_time = localtime(&xepoch_time);
	
	//tzset();//setting time
	cout<<converted_time<<endl;
	strftime(buf,26,"%Y-%m-%d %H:%M:%S",converted_time);
	cout<<"TIME STAMP ACCORDING TO SYSTEM TIMEZONE=>"<<tzname[converted_time->tm_isdst]<<endl;
	//timezonetime=buffer+" "+tzname[converted_time->tm_isdst];

	return ;
}
