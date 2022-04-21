#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip

class newUser
{
	long mobile;
	string userId,password,emailId;
	public:
	
	void enterDetails();
	void display();
};
void newUser :: enterDetails()
{
	string re_password;
	cout<<"New User Details "<<endl;
	cout<<"-------------------------"<<endl;
	
	cout<<"\nEnter User ID "<<endl;
	cin>>userId;
	cout<<"Enter Email ID "<<endl;
	cin>>emailId;
	cout<<"Enter Mobile Number "<<endl;
	cin>>mobile;
	while(1)
	{
		cout<<"Enter Password "<<endl;
		cin>>password;
		cout<<"Enter Re-Password "<<endl;
		cin>>re_password;
		if(password == re_password)
		{
			break;
		}
		else
		{
			cout<<"Password and Re-Password are not same ! \nPlease Enter again"<<endl;
		}
	
	}
}
void newUser :: display()
{
	cout<<userId<<" "<<emailId<<" "<<mobile<<" "<<password<<endl;
}

void enterCrediantiels(string &user,string &password)
{
	cout<<"Enter your Crediantiels "<<endl;
	cout<<"-------------------------"<<endl;
	
	cout<<"\nEnter Your User ID"<<endl;
	cin>>user;
	cout<<"Enter Your Password"<<endl;
	cin>>password;
}

int main()
{
	// socket_creation
	int client_des=socket(AF_INET,SOCK_STREAM,0); //-1
	if(client_des == -1)
	{
		perror("Socket creation error ");
		exit(1);
	}


	//sockaddr of sockaddr_in initialization
	struct sockaddr_in sock_addr_client;
	sock_addr_client.sin_family=AF_INET;//donmain ipv4
	sock_addr_client.sin_port=8088;
	sock_addr_client.sin_addr.s_addr=inet_addr("127.0.0.1");

	 
	//connecting
	socklen_t len =sizeof(sock_addr_client);
	int srever_des=connect(client_des,(struct sockaddr *)&sock_addr_client,len);
	if(srever_des == -1)
	{
		perror("Connecting error ");
		exit(1);
	}
	
	
	//handshaking with client
 	char msg[100];
 	read(client_des,&msg,sizeof(msg));
 	cout<<msg<<endl;


 	/*string temp_UserId,temp_Password;
	enterCrediantiels(temp_UserId,temp_Password);
	cout<<temp_UserId<<" "<<temp_Password<<endl;
	
	write(client_des,&temp_UserId,sizeof(temp_UserId));
	write(client_des,&temp_Password,sizeof(temp_Password));*/
	
	
 	//class object
 	
 	/*newUser object;
 	object.enterDetails();
 	object.display();*/
	
 	//send data for server
 	/*char buff[]="Hello how are you";
 	write(client_des,&buff,sizeof(buff));*/
 	
 	//ssize_t  send(int socket, const void *buffer, size_t length, int flags);
 	string buff="Hello how are you";
 	size_t len1=buff.length();
 	ssize_t  l=send(client_des,(const void *)&buff,len1,0);
 	cout<<l<<endl;
	

	//socket close
 	if(close(client_des) == -1)
	{
		perror("Clint acceptance error ");
		exit(1);
	}
  	 
	return 0;
}


