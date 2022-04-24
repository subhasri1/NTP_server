#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
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

int user_cred_authentication(map<string, string> user_cred, char data[],int n)
{
	//cout<<data<<endl;
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
		cout<<i.first<<" "<<user<<endl<<i.second<<" "<<password<<endl;
		if(i.first==user && i.second==password)
		return 1;
		else if(i.first==user)
		return 2;
	}
	return 0;
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
	sock_addr_server.sin_port=9999;
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
	for(auto i:userCred)
	cout<<i.first<<" "<<i.second<<endl;
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
	 	
	 	
	 	char buffer[size];
	 	bzero(buffer,sizeof(buffer));	 	
	 	int n=read(cli_des,&buffer,sizeof(buffer));
	 	//cout<<"from Client side "<<buffer<<endl;
	 	if(buffer[0]=='1')
	 	{
		 	int ret=user_cred_authentication(userCred,buffer,n);
		 	//cout<<ret<<endl;
		 	string message;
		 	if(ret==1)
		 	message="Login Successful !";
		 	else if(ret == 2)
		 	message="Login Credentials are Invalid ! \nPlseae Enter Correct Details";
		 	else
		 	message="User not found ! \nEnter 2 for Register your self";
			
			int msg_len = message.length();
			cout<<"message length"<<msg_len<<endl;
			char msg[msg_len];
			//bzero(msg,sizeof(msg));
			strcpy(msg,message.c_str());
		 	write(cli_des,&msg,sizeof(msg));
	 	}
	 	else if(buffer[0]=='2')
	 	{
		 	//int k=read(cli_des,&buffer,sizeof(buffer));
		 	user_cred_addition(userCred,buffer,n);//to write user in file and map
		 	char msg[]="Registration Successfull";
		 	write(cli_des,&msg,sizeof(msg));
	 	}
	 	 
	}
	 	
	//CLOSING the socket 1
	if(close(sock_des) == -1)
	{
		perror("Client acceptance error ");
		exit(1);
	}
  
	return 0;
}


