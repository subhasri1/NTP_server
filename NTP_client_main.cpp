#include "NTP_client_header.h"
#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<stdio.h>//gets function
#include<cstring>//strcpy
#define size 256

int main(int argc,char *argv[])
{
	int port=8088;
	int choice;	
	//   ./client portnumber 
	//   ./client  portnumber  user_name 
	
	choice_and_port_set_on_cmd_line_argument(argc,argv,port,choice);
	
	
	
	// socket_creation
	int client_des=socket(AF_INET,SOCK_STREAM,0); //-1
	if(client_des == -1)
	{
		perror("Socket creation error ");
		exit(1);
	}


	//sockaddr of sockaddr_in initialization
	struct sockaddr_in sock_addr_client;
	sock_addr_client.sin_family=AF_INET;//donmain ipv4
	sock_addr_client.sin_port=port;
	sock_addr_client.sin_addr.s_addr=inet_addr("127.0.0.1");

	 
	//connecting
	int srever_des=connect(client_des,(struct sockaddr *)&sock_addr_client,sizeof(sock_addr_client));
	if(srever_des == -1)
	{
		perror("Connecting error ");
		exit(1);
	}
	else
	{
	//handshaking with server
 	char msg[size];
 	bzero(msg,sizeof(msg));
 	read(client_des,&msg,sizeof(msg));
 	cout<<msg<<endl;
 	}
	
	
	//class object
 	newUser object;
 	
	/*cout<<"\nChoose from Menu"<<endl;
	cout<<"--------------------"<<endl;
	cout<<"1 : Existing User"<<endl;
	cout<<"2 : New User"<<endl;
	cout<<"0 : Exit"<<endl;
	int choice;
	cin>>choice;*/
	int cnt=3;
	while(1)
	{
		int k=0;
		switch(choice)
		{
			case 0 :	{
						char msg[]="e";
						write(client_des,&msg,sizeof(msg));
						exit(1);
					}
					
			case 1 :	{
						object.existing_user(argv[2],cnt);
			 			string cred=object.existingUserCredInOneString(argv[2]);
			 			int len1=cred.length();
						char char_cred[len1];
						strcpy(char_cred,cred.c_str());
						write(client_des,&char_cred,sizeof(char_cred));
						 	
						char ret;
						 read(client_des,&ret,sizeof(ret));
						 if(ret=='1')
						 {
						 	cout<<"\nLogin Successful !\n\n"<<endl;
						 	k=1;
						 }
						 else if(ret == '2')
						 {
						 	if(cnt>1)//3 2 1
						 	{
						 	cnt--;
						 	//cout<<"Only "<<cnt<<" Attempts Left !"<<endl;
						 	//cout<<"\nLogin Credentials are Invalid ! \nPlseae Enter Correct Details"<<endl;
						 	choice=1;
						 	}
						 	else
						 	{
						 	cout<<"\n\nOOPS! Limits has been exeeded !"<<endl;
						 	choice=0;
						 	}
						 			
						 }
						 else
						 {
						 	cout<<"\nUser not found !\n"<<endl;
						 	choice=2;
					 	 }
				 	}
					break;
					
			case 2 :	{
						object.add_new_User();
						string data=object.newUserDataInOneString();
						int len2=data.length();
						char char_data[len2];
						strcpy(char_data,data.c_str());
						write(client_des,&char_data,sizeof(char_data));
						
						char msg;
						read(client_des,&msg,sizeof(msg));
						if(msg == '3')
						{
					 		cout<<"\n\nRegistration Successfull\n"<<endl;
					 		k=1;
					 	}
					}
					break;
					
			default :	{cout<<"\nInvalid Entry"<<endl;}
		}
		if(k==1)
		break;
 	}
 	
 	/*while(1)
 	{
		
		//request to server
		
		//statement
		
		
		//pause();
	  	//alarm(3600);
	  	
  	}*/
		
	//socket close
 	if(close(client_des) == -1)
	{
		perror("Socket Close error ");
		exit(1);
	}
  	
	return 0;
}


