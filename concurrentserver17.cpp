// C++ program for the Server Side
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<errno.h>
// inet_addr
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
// For threading, link with lpthread
#include<sys/types.h>
#include<semaphore.h>
using namespace std;

#define PORT 8808

int main()
{

// Function to send data to server socket.:

char buffer[1024];
	// Create a stream socket

int newsocket;

struct sockaddr_in newaddr;
pid_t childpid;

	int clientsocket = socket(AF_INET,SOCK_STREAM, 0);
	 if(clientsocket < 0)
	 {
	 cout<<"error in server connecion"<<endl;
	 exit(1);
	 }
	 cout<<"[+]server socet created"<<endl;
	 

	// Initialise port number and address
	
	struct sockaddr_in serveraddr;
	memset(&serveraddr,'\0',sizeof(serveraddr));
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(PORT);


	// binding a socket connection
	int connection_status;
	//socklen_t len =sizeof(serveraddr);
	connection_status = bind(clientsocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

	// Check for connection error
	if (connection_status < 0)
	 {
		cout<<" error in binding"<<endl;
		exit(1);
	}
	cout<<"bind to port :"<<PORT<<endl;
	
	if(listen(clientsocket,10) == 0)
	{
	cout<<"listeningg ...."<<endl;
	}
	else
	{
	cout<<"error in bining"<<endl;
	}
	
	// Send data to the socket
	//send(network_socket, &client_request,sizeof(client_request), 0);

	while(1)
	{
	socklen_t newlen =sizeof(newaddr);
	newsocket = accept(clientsocket,(struct sockaddr*)&newaddr,&newlen);
	if(newsocket < 0)
	{
	exit(1);
	}
	cout<<"connecion accepted from  : "<<inet_ntoa(newaddr.sin_addr)<<":"<<ntohs(newaddr.sin_port)<<endl;
	
	if((childpid = fork()) == 0)
	{
	close(clientsocket);
	
		while(1)
		{
		recv(newsocket,buffer,1024,0);
		
	
		if(strcmp(buffer,":exit") == 0)
		{
		close(clientsocket);
		cout<<"disconnected from server  : "<<inet_ntoa(newaddr.sin_addr)<<":"<<ntohs(newaddr.sin_port)<<endl;
		break;
		}
		else
		{
		cout<<"client :"<<buffer<<endl;
		send(clientsocket,buffer,strlen(buffer),0);
		bzero(buffer,sizeof(buffer));
	
	}
	}
	}
	} 
	
	close(newsocket);
		return 0;
}


