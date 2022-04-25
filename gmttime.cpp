#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
// server receives a string from the client and it sends back a string to the client
int main()
{

//socket creation
int serv_fd = socket(AF_INET,SOCK_STREAM,0);
if (serv_fd == -1)
{
	perror("socket creation error");
	exit(1);
}
//initialize the socaddr_in structure
struct sockaddr_in sock_addr_serv;// sockaddr_in for IPV4
sock_addr_serv.sin_family = AF_INET;
sock_addr_serv.sin_port = 8088;
sock_addr_serv.sin_addr.s_addr = inet_addr("127.0.0.1");

//bind the socket with ip address and port
if (bind(serv_fd,(struct sockaddr *)&sock_addr_serv,sizeof(sock_addr_serv))==-1)
{
	perror("bind error");
	exit(1);
}

// listening (waiting) for client request
if (listen(serv_fd,2)==-1)
{
	perror("listen error");
	exit(1);
}


//while(2)
//	{
	
	time_t curr_time;
	curr_time = time(NULL);
	char* dt = ctime(&curr_time);
	cout << "The current local date and time is: "  << dt <<endl;
//	sleep(10);
// 	}
while (1)
{
	
	cout << "server waiting for client to connect"  << endl;
	
	//accepting client request
	struct sockaddr_in sock_addr_cli;
	socklen_t cli_len = sizeof(sock_addr_cli);
	int client_fd=accept(serv_fd,(struct sockaddr *)&sock_addr_cli,&cli_len);
	
 
	if (client_fd==-1)
	{
		perror(" accept error");
		exit(1);
	}
	char ch[100];
	read(client_fd,ch,sizeof(ch));
	puts(ch);
	char greet[]={"Hey"};
	
	strcat(greet,ch);
	//write(client_fd,"received",8);	
	write(client_fd,greet,strlen(greet));	
	
}

//close socket
if (close(serv_fd)==-1)
{
	perror("socket close error");
	exit(1);
}
}
