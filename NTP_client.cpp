#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<stdio.h>//gets function
#include<cstring>//strcpy
#define size 256
class newUser
{
	string mobile,name,userId,password,emailId,temp_Password,temp_User;
	public:
	void add_new_User();
	void existing_user();
	string newUserDataInOneString();
	string existingUserCredInOneString();
};
void newUser :: add_new_User()
{
	string re_password;
	cout<<"New User Details "<<endl;
	cout<<"-------------------------"<<endl;
	
	cout<<"\nEnter your Name "<<endl;
	//fgets(name,sizeof(name)-1,stdin);
	getline(cin>>ws,name);
	cout<<"Enter User ID "<<endl;
	cin>>userId;
	cout<<"Enter your Email ID "<<endl;
	cin>>emailId;
	cout<<"Enter your Mobile Number "<<endl;
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
void newUser :: existing_user()
{
	cout<<"Enter your Crediantiels "<<endl;
	cout<<"-------------------------"<<endl;
	
	cout<<"\nEnter Your User ID"<<endl;
	cin>>temp_User;
	cout<<"Enter Your Password"<<endl;
	cin>>temp_Password;
}
string newUser :: newUserDataInOneString()
{
	string sum="2"+userId+","+password+","+emailId+","+mobile+","+name;
	return sum;
}

string newUser :: existingUserCredInOneString()
{
	string sum="1"+temp_User+","+temp_Password;
	return sum;
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
	sock_addr_client.sin_port=9999;
	sock_addr_client.sin_addr.s_addr=inet_addr("127.0.0.1");

	 
	//connecting
	int srever_des=connect(client_des,(struct sockaddr *)&sock_addr_client,sizeof(sock_addr_client));
	if(srever_des == -1)
	{
		perror("Connecting error ");
		exit(1);
	}
	else
	{
	//handshaking with server
 	char msg[size];
 	bzero(msg,sizeof(msg));
 	read(client_des,&msg,sizeof(msg));
 	cout<<msg<<endl;
 	}
	
	
	//class object
 	newUser object;
 	
	cout<<"\nChoose from Menu"<<endl;
	cout<<"--------------------"<<endl;
	cout<<"1 : Existing User"<<endl;
	cout<<"2 : New User"<<endl;
	cout<<"0 : Exit"<<endl;
	int choice;
	cin>>choice;
	switch(choice)
	{
		case 0 :	exit(1);
				
		case 1 :	{
				object.existing_user();
 				string cred=object.existingUserCredInOneString();
 				int len1=cred.length();
			 	char char_cred[len1];
				strcpy(char_cred,cred.c_str());
				//char_cred[len]='\0';
				cout<<char_cred<<endl;
			 	write(client_des,&char_cred,sizeof(char_cred));
			 	
			 	char msg[size];
			 	bzero(msg,sizeof(msg));
			 	read(client_des,&msg,sizeof(msg));
			 	cout<<msg<<endl;
			 	}
				break;
				
		case 2 :	{
				object.add_new_User();
				string data=object.newUserDataInOneString();
				int len2=data.length();
				char char_data[len2];
				strcpy(char_data,data.c_str());
				//char_data[len]='\0';
				cout<<char_data<<endl;
				write(client_des,&char_data,sizeof(char_data));
				
				char msg[size];
				bzero(msg,sizeof(msg));
				read(client_des,&msg,sizeof(msg));
			 	cout<<msg<<endl;
				}
				break;
				
		default :	{cout<<"Invalid Entry"<<endl;}
	}
 	
 	
 	
 	

	
	/*pause();
  	alarm(3600);
  	sleep(3600); */
		
	//socket close
 	if(close(client_des) == -1)
	{
		perror("Clint acceptance error ");
		exit(1);
	}
  	
	return 0;
}


