#include "NTP_server_header.h"
#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<fstream>//filehandling
#include<map>//map STL
#include<cstring>//strcpy
#include<stdlib.h>//atoi


#define size 256

int main(int argc,char *argv[])
{
	int port=8088;
	if(argc == 2)
	{
		port = atoi(argv[1]);
	}
	// socket_creation
	int sock_des=socket(AF_INET,SOCK_STREAM,0); //-1
	if(sock_des == -1)
	{
		perror("Socket creation error ");
		exit(1);
	}
	
	
	//sockaddr of sockaddr_in initialization
	struct sockaddr_in sock_addr_server;
	sock_addr_server.sin_family=AF_INET;//donmain ipv4
	sock_addr_server.sin_port=port;
	sock_addr_server.sin_addr.s_addr=inet_addr("127.0.0.1");
	 
	 
	//binding
	int b = bind(sock_des,(struct sockaddr *)&sock_addr_server,sizeof(sock_addr_server));
	if(b == -1)
	{
		perror("Binding error ");
		exit(1);
	}
	 
	 
	//listening
	int l = listen(sock_des,10);
	if(l == -1)
	{
		perror("Listening error ");
		exit(1);
	}
	
	//map creation
	map<string, string>userCred;
	user_cred_file_to_map(userCred);//cred insertion in map
	
	int x=1;
	while(x)
	{
	 	cout<<"Server are listening on port Number "<<sock_addr_server.sin_port<<endl;
	 	
	 	
	 	//acceptance
	 	struct sockaddr_in sock_addr_client;
		socklen_t len =sizeof(sock_addr_client);
	 	int cli_des=accept(sock_des,(struct sockaddr *)&sock_addr_client,&len);
	 	if(cli_des == -1)
		{
			perror("Clint acceptance error ");
			exit(1);
		}
		else
		{
	 	//handshaking with client
	 	char msg[]="Successfull Connection established from the Server";
	 	write(cli_des,&msg,sizeof(msg));
	 	}
	 	
	 	login_and_registration_of_user(cli_des,userCred);
	 	
	 	
	 	//{
	 	//take request from client
	 	
	 	
	 	//statement
	 	char che[size];
	 	bzero(che,sizeof(che));
		int z=read(cli_des,&che,sizeof(che));
		if(string(che)=="Requisting")
		{
			//cout<<che<<endl;
			int  epochserv,GMThour,GMTmin,GMTsec,GMTmday,GMTmon,GMTyear;
			time_t curr_time;
			curr_time = time(NULL);
			
			//best -> GMT Time
			best_time_to_GMT_conversion(curr_time,GMThour,GMTmin,GMTsec,GMTmday,GMTmon,GMTyear);
			
			//GMT->Epoch
			GmT_to_epoch_coversion(epochserv,GMThour,GMTmin,GMTsec,GMTmday,GMTmon,GMTyear);
			
			//cout<<"Epoch CONVERTED TIME FROM GMT : "<<epochserv<<endl;//epochserv
			//cout<<"Connecting to Clients"<<endl;
			//cout<<"Epoch "<<epochserv<<endl;
			
			string s= to_string(epochserv); 
			char nchar[s.length()] ; //converting long to char part 1
			strcpy(nchar,s.c_str()); //part 2
			int w=write(cli_des,&nchar,sizeof(nchar));
			
			
			//cout<<"Epoch TIME >>"<<nchar<<endl;
			//sleep(5);
			//char che[size];
			//int z=read(cli_des,che,sizeof(che));
			//bzero(che,sizeof(che));
			//puts(che);
			//bzero(che,sizeof(che));
			
			//int w=write(cli_des,nchar,sizeof(nchar));
			
			//int w=write(cli_des,&nchar,sizeof(nchar));
			//cout<<w<<endl;
	 	}
	 	
	 	
	 	//}
	 	
	 	
	}
	 	
	//CLOSING the socket 1
	if(close(sock_des) == -1)
	{
		perror("Client acceptance error ");
		exit(1);
	}
  
	return 0;
}

