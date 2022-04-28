#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<stdio.h>//gets function
#include<cstring>//strcpy

class newUser
{
	string mobile,name,userId,password,emailId,temp_Password;
	public:
	void add_new_User();
	void existing_user(string,int);
	string newUserDataInOneString();
	string existingUserCredInOneString(string);
};

void choice_and_port_set_on_cmd_line_argument(int argc,char* argv[],int &port,int &choice);
