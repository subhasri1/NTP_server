#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// client sends a string to the server and it recieves the  string with greetings from the server
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

// connecting to server
while(1)
{
socklen_t len = sizeof(sock_addr_serv);
if (connect(serv_fd,(struct sockaddr *)&sock_addr_serv,len)==-1)
{
	perror("connect error");
	exit(1);
}

char ch[100], buf[100];
cout << "enter a string " << endl;
fgets(ch, sizeof(ch)-1, stdin);

write(serv_fd,ch,strlen(ch));// writes a string to server
int n =read(serv_fd,buf,sizeof(buf));// reads the acknowledgement from server
write(1,buf,n);

close(serv_fd);
}

sleep(3600);
}
return 0;





