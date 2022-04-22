#include<iostream>
#include"gmtcovertor.h"  //header file for gmtcovertor
using namespace std;
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
	int serv_fd = socket(AF_INET, SOCK_STREAM, 0); 

	struct sockaddr_in sock_addr_serv; 
	sock_addr_serv.sin_family=AF_INET; 
	sock_addr_serv.sin_port= 8088; 
	sock_addr_serv.sin_addr.s_addr=inet_addr("127.0.0.1"); 

	bind(serv_fd, (struct sockaddr *)&sock_addr_serv, sizeof(sock_addr_serv));

	listen(serv_fd,5);
	int GMThour,GMTmin,GMTsec;
	gmtcovertor(GMThour,GMTmin,GMTsec);
	cout<<"Current time : "<<GMThour<<":"<<GMTmin<<":"<<GMTsec<<" GMT"<<endl;
	
	while(1)
	{
		cout<<"Waiting for client"<<endl;
		struct sockaddr_in sock_addr_cli;
		socklen_t cli_len = sizeof(sock_addr_cli);
		int client_fd=accept(serv_fd, (struct sockaddr *)&sock_addr_cli, &cli_len);
		char ch;
		read(client_fd, &ch, 1); 
		cout<<"from client "<<ch<<endl;
		ch++;
		write(client_fd, &ch, 1);
	}
	close(serv_fd);
}
