#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<stdio.h>//gets function
#include<signal.h>//signal
#include<string.h>
#include<fstream>
#include<map>//map STL
#include<stdlib.h>//atoi
#include<time.h>//gmt


#define SIZE 256
extern char buffer[SIZE];
extern int client_des;


class newUser
{
	//data member for class
	string mobile,name,userId,password,emailId,temp_Password;
	public:
	//function member for class
	
	newUser();
	newUser(string mobile,string name,string userId,string password,string emailId,string temp_Password);
	//creating a new User
	void add_new_User();
	
	//asking for password of existing user
	void existing_user(string,int);
	
	//will convert all new user data entered in to one string will separated by ","
	string newUserDataInOneString();
	
	//will convert existing user and password in to one string will separated by ","
	string existingUserCredInOneString(string);
	
	//destructor
	~newUser()
	{	}
};

//handling of choice according to cmd arguments 
void choice_and_port_set_on_cmd_line_argument(int argc,char* argv[],int &port,int &choice);

//signal handler
void sig_handler(int signum);




