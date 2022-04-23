#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<fstream>//filehandling
#include<map>//map STL
#define size 256


void user_cred_file_to_map(map<string, string> &user_cred)
{
	fstream fin;
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
	
}

int user_cred_authentication(map<string, string> user_cred, char cred[])
{
	int cnt=0;
	string user="",password="";
	for(int i=0;i<data.length();i++)
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
		return 1;
	}
	return 0;
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
	sock_addr_server.sin_port=99999;
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
	int i=1;
	while(i>0)
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
		else if(i==1)
		{
	 	//handshaking with client
	 	char msg[]="Successfull Connection established from the Server";
	 	write(cli_des,&msg,sizeof(msg));
	 	i=2;
	 	}
	 	
	 	
	 	map<string, string>userCred;
	 	user_cred_file_to_map(userCrede);//cred insertion in map
	 	
	 	
	 	char temp_Cred[size];	 	
	 	read(cli_des,&temp_Cred,sizeof(temp_Cred));
	 	cout<<"from Client side "<<temp_Cred<<endl;
	 	int ret=user_cred_authentication(userCred,temp_Cred);
	 	
	 	/*
	 	char buffer[size];
	 	read(cli_des,&buffer,sizeof(buffer));
	 	*/
	 	user_cred_addition(userCred,temp_Cred);
	 	 
	}
	 	
	//CLOSING the socket 1
	if(close(sock_des) == -1)
	{
		perror("Client acceptance error ");
		exit(1);
	}
  
	return 0;
}


