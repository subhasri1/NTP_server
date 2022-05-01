

//****************************MAIN*******************************

#include "NTP_client_header.h"

#define SIZE 256
char buffer[SIZE];
int client_des;

void signal_handler_for_abnormal_termination(int signum);





int main(int argc,char *argv[])
{
	int port=8088;
	int choice;
	int n;	
	ofstream foutLog;
	foutLog.open("client.log",ios::app);
	//   ./client  -> argc =1 ->new user
	//   ./client user_name  ->argc 2 ->existing user
	
	//handle choice on the base of number of argument
	foutLog<<"[Info] : setting the choice on the bases of Number of Arguments"<<endl;	
	choice_and_port_set_on_cmd_line_argument(argc,argv,port,choice);
	
	
	
	// socket_creation
	client_des=socket(AF_INET,SOCK_STREAM,0); //-1
	foutLog<<"[Info] : Creatinng a client Socket"<<endl;
	if(client_des == -1)
	{
		perror("Socket creation error ");
		foutLog<<"error : Client Socket creation Error"<<endl;
		exit(1);
	}


	//sockaddr of sockaddr_in initialization
	struct sockaddr_in sock_addr_client;
	sock_addr_client.sin_family=AF_INET;//donmain ipv4
	sock_addr_client.sin_port=port;
	sock_addr_client.sin_addr.s_addr=inet_addr("127.0.0.1");

	 
	//connecting
	foutLog<<"[Info] : Connecting to server"<<endl;
	int srever_des=connect(client_des,(struct sockaddr *)&sock_addr_client,sizeof(sock_addr_client));
	if(srever_des == -1)
	{
		perror("Connecting error ");
		foutLog<<"[error] : Connecting to server error"<<endl;
		exit(1);
	}
	else
	{
		foutLog<<"[Info] : Handshaking to server"<<endl;
		//handshaking with server
	 	char msg[SIZE];
	 	bzero(msg,sizeof(msg));
	 	n=read(client_des,&msg,sizeof(msg));
	 	if(n!=strlen(msg)==0)
	 	{
	 		cout<<"Handshaking : Error in Reading "<<endl;
	 		foutLog<<"[error] : Handshaking to server failed"<<endl;
	 	}else
	 	{ 
	 		cout<<msg<<endl;
	 	}
 	}
	
	
	//class object
 	newUser object;
 	
	
	/*
	"1 : Existing User"
	"2 : New User"
	"0 : Exit"
	*/

	int cnt=3;
	while(1)
	{
		int k=0;
		switch(choice)
		{
			case 0 :	{
						//terminating the process
						char msg[]="e";
						write(client_des,&msg,sizeof(msg));
						exit(1);
					}
					
			case 1 :	{
						foutLog<<"[INFO] : User Validation"<<endl;
						object.existing_user(argv[1],cnt); //for existing user password
			 			string cred=object.existingUserCredInOneString(argv[1]); //user id and password into one string
			 			int len1=cred.length();
						char char_cred[len1];
						strcpy(char_cred,cred.c_str());
						n=write(client_des,&char_cred,sizeof(char_cred));//credentials sending to server
						if(n==strlen(char_cred)==0)
					 	{
					 		cout<<"Existing user : Error in Sending of Credentials "<<endl;
					 	}
						 	
						char ret;
						 read(client_des,&ret,sizeof(ret)); //reading the res of server
						 if(ret=='1')
						 {
						 	cout<<"\nLogin Successful !\n\n"<<endl;
						 	k=1;
						 }
						 else if(ret == '2')
						 {
						 	if(cnt>1)//3 2 1
						 	{
						 	cnt--;
						 	choice=1;
						 	}
						 	else
						 	{
						 	cout<<"\n\nOOPS! Limits has been exeeded !"<<endl;
						 	choice=0;
						 	}
						 			
						 }
						 else
						 {
						 	cout<<"\nUser not found !\n"<<endl;
						 	choice=2;
					 	 }
				 	}
					break;
					
			case 2 :	{
						foutLog<<"[INFO] : User Creation"<<endl;
						object.add_new_User();//new user data
						string data=object.newUserDataInOneString(); //new user data in one string
						int len2=data.length();
						char char_data[len2];
						strcpy(char_data,data.c_str());
						n=write(client_des,&char_data,sizeof(char_data)); //data sending to server
						if(n!=strlen(char_data)==0)
					 	{
					 		cout<<"New user : Error in Sending of Data "<<endl;
					 	}
					 	
						char msg;				
						read(client_des,&msg,sizeof(msg)); //reading the res from server
						if(msg == '3')
						{
					 		cout<<"\n\nRegistration Successfull\n"<<endl;
					 		k=1;
					 	}
					}
					break;
					
			default :	{
					foutLog<<"[warning] : Inavlid Enrty"<<endl;
					cout<<"\nInvalid Entry"<<endl;}
		}
		
		if(k==1)
		break;
 	}
 	
 	signal(SIGALRM,sig_handler);
 	signal(SIGINT,signal_handler_for_abnormal_termination);
 	while(1)
 	{
		
		//request to server
		//statement
		
		foutLog<<"[INFO] : Requesting to Server for a Server Time"<<endl;
		string s="Requisting";
		strcpy(buffer,s.c_str());
		cout<<"Requisting to server for Time"<<endl;
		write(client_des,&buffer,sizeof(buffer));
		
		bzero(buffer,sizeof(buffer));
		int n=read(client_des,&buffer,sizeof(buffer));
		//cout<<buffer<<endl;
		
		//epoch from buffer to time_t
		time_t epoch_from_server=(time_t)stol(buffer,nullptr,10);
		//cout<<epoch_from_server<<endl;
		
		//epoch to local time
		tm * epoch_to_local; // decalring variable for localtime()
	
		epoch_to_local = localtime(&epoch_from_server);
		cout<<"\n*****************************************************************************"<<endl;
		cout << "Server Time according to Local Zone "<< asctime(epoch_to_local)<<endl;
		cout<<"*****************************************************************************"<<endl;
		//System hardware Time
		time_t t; // t passed as argument in function time()
   		tm * HW_time; // decalring variable for localtime()
   		time (&t); //passing argument to time() ->epoch
   		HW_time = localtime(&t);
   		cout << "Client Hardarwe Time "<< asctime(HW_time);
   		cout<<"*****************************************************************************\n"<<endl;
   		//HW clock updation of client if Diff of time in HW time and server Time > 0
		if(difftime((time_t)epoch_to_local,(time_t)HW_time) != 0)
		{
			struct timespec stime;
		 	int p=clock_settime( epoch_from_server, &stime);
		 	if(p == -1)
		 	{
		 	perror("error in settting of Hardware clock");
		 	exit(1);
		 	}
		 	
		 	cout<<"Clock is synchronised with server time\n\n"<<endl;
			
		}
		else
		{
		cout<<"Clock is already synchronised\n\n"<<endl;
		}
		
		//for every one hour synchonising
		
	  	alarm(5);
	  	pause();
  	}
  	
	foutLog.close();	
	return 0;
}
//signal Handler
void signal_handler_for_abnormal_termination(int signum)
{
	char msg[]="bye";
	write(client_des,&msg,sizeof(msg));
	
	//socket close
	if(close(client_des) == -1)
	{
		perror("Socket Close error ");
		exit(1);
	}
		exit(1);
}
