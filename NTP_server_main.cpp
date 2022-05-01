

//****************************MAIN*******************************

#include "NTP_server_header.h"
#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<fstream>//filehandling
#include<map>//map STL
#include<cstring>//strcpy
#include<stdlib.h>//atoi
#include <wait.h>
#include<fstream>
#define SIZE 256

char buffer[SIZE];

void transact_with_client(int sock);

//to avoid zombie process
void sighandler(int signum)
{
	cout << strsignal(signum) << endl;
	wait(NULL);
}


//Main of Program
int main(int argc,char *argv[])
{
	int port=8088;
	int n;
	
	ofstream foutlog;
	foutlog.open("server.log",ios::app);
	
	foutlog<<"[INFO] : Socket creation "<<endl;
	// socket_creation
	int sock_des=socket(AF_INET,SOCK_STREAM,0); //-1
	if(sock_des == -1)
	{
		perror("Socket creation error ");
		foutlog<<"[ERROR] : Socket creation error "<<endl;
		exit(1);
	}
	
	foutlog<<"[INFO] : Sock addr initialization "<<endl;
	//sockaddr of sockaddr_in initialization
	struct sockaddr_in sock_addr_server;
	sock_addr_server.sin_family=AF_INET;//donmain ipv4
	sock_addr_server.sin_port=port;
	sock_addr_server.sin_addr.s_addr=inet_addr("127.0.0.1");
	 
	 
	 foutlog<<"[INFO] : Socket Binding "<<endl;
	//binding
	int b = bind(sock_des,(struct sockaddr *)&sock_addr_server,sizeof(sock_addr_server));
	if(b == -1)
	{
		perror("Binding error ");
		foutlog<<"[ERROR] : Socket Binding error "<<endl;
		exit(1);
	}
	 
	 
	//listening
	foutlog<<"[INFO] : Server Listening "<<endl;
	int l = listen(sock_des,10);
	if(l == -1)
	{
		perror("Listening error ");
		foutlog<<"[ERROR] : ERROR in Server Listening "<<endl;
		exit(1);
	}
	
	//map creation
	foutlog<<"[INFO] : Map(STL) creation "<<endl;
	map<string, string>userCred;
	
	foutlog<<"[INFO] : Map Inotalization "<<endl;
	user_cred_file_to_map(userCred);//cred insertion in map
	
	int x=1;
	while(x)
	{
	 	cout<<"Server are listening on port Number "<<sock_addr_server.sin_port<<endl;
		foutlog<<"[INFO] : Server are Listening on  8088 "<<endl;	 	
			 	
	 	//acceptance
	 	foutlog<<"[INFO] : Sever  acceptance "<<endl;
	 	struct sockaddr_in sock_addr_client;
		socklen_t len =sizeof(sock_addr_client);
	 	int cli_des=accept(sock_des,(struct sockaddr *)&sock_addr_client,&len);
	 	if(cli_des == -1)
		{
			perror("Clint acceptance error ");
			foutlog<<"[ERROR] : Server Acceptance error "<<endl;
			exit(1);
		}
		else
		{
		 	//handshaking with client
		 	foutlog<<"[INFO] : Handshaking with client"<<endl;
		 	char msg[]="Successfull Connection established from the Server";
		 	n=write(cli_des,&msg,sizeof(msg));
		 	if(n!=strlen(msg)==0)
			{
				foutlog<<"[INFO] : Handshaking Error on server"<<endl;
				cout<<"Hanshaking : Error in Sending Message from Server"<<endl;
			}	
	 	}
	 	
		 //Login or Registration
		 foutlog<<"[INFO] : Login or Registration Oparation"<<endl;
		login_and_registration_of_user(cli_des,userCred);
		 
		 foutlog<<"[INFO] : Creating a  Process "<<endl;
		pid_t pid= fork();
		if (pid==0)
		{
			foutlog<<"[INFO] : inside the child Process"<<endl;
			foutlog<<"[INFO] : Server performing on client request "<<endl;
			transact_with_client(cli_des);
			exit(0);
		}
	
	} //end of server acceptance loop
	 

	 	
	//CLOSING the socket 1
	foutlog<<"[INFO] : Socket Closing "<<endl;
	if(close(sock_des) == -1)
	{
		foutlog<<"[INFO] : Socket Closing Error "<<endl;
		perror("Client acceptance error ");
		exit(1);
	}
  
	return 0;
}


void transact_with_client(int cli_des)
{	
	while(1)
		{
			 bzero(buffer,sizeof(buffer)); 
			 read(cli_des,&buffer,sizeof(buffer));
			if(strcmp(buffer,"bye")==0)
			{
				break;	
			}
				 cout<<buffer<<" By Client for Time"<<endl;
			 
			char* host_name1 = "us.pool.ntp.org";
			char* host_name2 = "time.google.com";
			
			//time from local, server1 and server2
			time_t local_time=gettimefromLocalMachine();
			time_t server1_time=gettimefromserver(host_name1);
			time_t server2_time=gettimefromserver(host_name2);
			
			
			//time difference
			long diff_time1,diff_time2,diff_time3;
			diff_time1=difftime(local_time, server1_time);
			diff_time2=difftime(local_time, server2_time);
			diff_time3=difftime(server2_time, server1_time);
			
			//Best Time selection
		  	time_t best_time;
		  	
			if(diff_time1 < diff_time2 && diff_time1 < diff_time3)
			{
				best_time=local_time;
			}
			else if(diff_time2 < diff_time3 && diff_time2 < diff_time1)
			{
				best_time=local_time;
			}
			else
			{
				best_time=server2_time;
			}
			
			//best time to gmt
			
			tm * best_time_gmt;
		  	best_time_gmt = gmtime ( &best_time);
		  	
		  	 
			 //Best time gmt to epoch
			time_t epoch_time=GmT_to_epoch_coversion(best_time_gmt);
		
			
			//epoch to char
			string tim=to_string(epoch_time);
			//cout<<"string"<<tim<<endl;
			char ep[SIZE];
			strcpy(ep,tim.c_str());
			write(cli_des,&ep,sizeof(ep));
		
		}//end pof inner loop	
	
}
