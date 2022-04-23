#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<stdio.h>//gets function
#include<cstring>//strcpy
class newUser
{
	string mobile,name,userId,password,emailId,temp_Password,temp_User;
	public:
	void enterDetails();
	void enterCrediantiels();
	string addAllInOneString();
	string crediantils_AddAllInOneString();
};
void newUser :: enterDetails()
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
void newUser :: enterCrediantiels()
{
	cout<<"Enter your Crediantiels "<<endl;
	cout<<"-------------------------"<<endl;
	
	cout<<"\nEnter Your User ID"<<endl;
	cin>>temp_User;
	cout<<"Enter Your Password"<<endl;
	cin>>temp_Password;
}
string newUser :: addAllInOneString()
{
	string sum=userId+","+password+","+emailId+","+mobile+","+name;
	return sum;
}

string newUser :: crediantils_AddAllInOneString()
{
	string sum=temp_User+","+temp_Password;
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
	sock_addr_client.sin_port=99999;
	sock_addr_client.sin_addr.s_addr=inet_addr("127.0.0.1");

	 
	//connecting
	int srever_des=connect(client_des,(struct sockaddr *)&sock_addr_client,sizeof(sock_addr_client));
	if(srever_des == -1)
	{
		perror("Connecting error ");
		exit(1);
	}
	
	
	//handshaking with server
 	char msg[100];
 	read(client_des,&msg,sizeof(msg));
 	cout<<msg<<endl;
	
	
 	//class object
 	newUser object;
 	
 	object.enterCrediantiels();
 	string cred=object.crediantils_AddAllInOneString();
 	
 	int len=cred.length();
 	char char_cred[len];
	strcpy(char_cred,cred.c_str());
	char_cred[len]='\0';
 	write(client_des,&char_cred,sizeof(char_cred));
 	cout<<char_cred;
 	
 	/*object.enterDetails();
	string data=object.addAllInOneString();
	char char_data[data.length()];
	strcpy(char_data,data.c_str());
	//cout<<char_data;
	write(client_des,&char_data,sizeof(char_data));*/
	
	
	
		
	//socket close
 	if(close(client_des) == -1)
	{
		perror("Clint acceptance error ");
		exit(1);
	}
  	/*pause();
  	alarm(3600);
  	sleep(3600); */
  	
	return 0;
}


