// C++ program for the Client Side
#include<iostream.h>
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

#include<semaphore.h>
using namespace std;

#define PORT 8808

int main()
{

// Function to send data to server socket.


int clientsocket,ret;
struct sockaddr_in serveraddr;
char buffer[1024]


	// Create a stream socket
	clientsocket = socket(AF_INET,SOCK_STREAM, 0);
	 if(clientsocket < 0)
	 {
	 cout<<"error in client connecion"<<endl;
	 exit(1);
	 }
	 cout<<"[+]Clinet socet created"<<endl;
	 

	// Initialise port number and address
	
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(PORT);

	// Initiate a socket connection
	int connection_status;
	socklen_t len=sizeof(serveraddr);
	connection_status = connect(clientsocket,(struct sockaddr*)&serveraddr,len);

	// Check for connection error
	if (connection_status < 0)
	 {
		cout<<"connection error";
		exit(1);
	}
	cout<<"connected to server"<<endl;
	
	// Send data to the socket
	//send(network_socket, &client_request,sizeof(client_request), 0);

	while(1)
	{
	cout<<"client :"<<endl;
	send(clientsocket,buffer,strlen(buffer),0);
	
	if(strcmp(buffer,":exit") == 0)
	{
	cout<<"disconnected from server"<<endl;
	exit(1);
	}
	
	}
	

	return 0;
}


