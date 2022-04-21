#include<iostream>
using namespace std;
#include<ctime>
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
	while(2)
	{
	
	time_t curr_time;
	curr_time = time(NULL);
	tm *tm_gmt = gmtime (&curr_time);
	cout<<"Current time : "<< tm_gmt->tm_hour  <<":"<<tm_gmt->tm_min <<":"<<tm_gmt->tm_sec<<" GMT"<<endl;
	sleep(3600);
	}

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
