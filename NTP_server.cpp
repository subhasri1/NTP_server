#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip

int main()
{
	string temp_User,temp_Password;
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
	  
	while(1)
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
	 	
	 	//Reading from client
	 	//char buff[100];
	 	//read(cli_des,&buff,sizeof(buff));
	 	//cout<<"Client side "<<buff<<endl;
	 	
	 	
	 	//string temp_User,temp_Password;
	 	/*read(cli_des,&temp_User,sizeof(temp_User));
	 	read(cli_des,&temp_Password,sizeof(temp_Password));
	 	
	 	cout<<"from Client side "<<temp_User<<" "<<temp_Password<<endl;*/
	 	
	 	string buffer1;
	 	//ssize_t recv(int socket, void *buffer, size_t length, int flags);
	 	ssize_t l=recv(cli_des,(void *)&buffer1,(size_t)buffer1.length(), 0);
	 	cout<<l<<endl;
	 	cout<<(string)buffer1<<endl;
	 	 
	}
	 	
	//CLOSING the socket 1
	if(close(sock_des) == -1)
	{
		perror("Client acceptance error ");
		exit(1);
	}
 
 
	return 0;
}


