#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include"gmtcovertor.h"  //header file for gmtcovertor
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<fstream>//filehandling
#include<map>//map STL
#include<cstring>//strcpy
#define size 256


void user_cred_file_to_map(map<string, string> &user_cred)
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
int main()
{
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
	sock_addr_server.sin_port=8088;
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
	 	
listen(sock_des,3);
	int GMThour,GMTmin,GMTsec;
	gmtcovertor(GMThour,GMTmin,GMTsec);
	cout<<"Current time : "<<GMThour<<":"<<GMTmin<<":"<<GMTsec<<" GMT"<<endl;
	
	while(1)
	{
		cout<<"Waiting for client"<<endl;
		struct sockaddr_in sock_addr_cli;
		socklen_t cli_len = sizeof(sock_addr_cli);
		int client_fd=accept(sock_des, (struct sockaddr *)&sock_addr_cli, &cli_len);
		char ch;
		read(client_fd, &ch, 1); 
		cout<<"from client "<<ch<<endl;
		ch++;
		write(client_fd, &ch, 1);
	 	
	}
	 	
	//CLOSING the socket 1
	if(close(sock_des) == -1)
	{
		perror("Client acceptance error ");
		exit(1);
	}
  
	return 0;
	
}


