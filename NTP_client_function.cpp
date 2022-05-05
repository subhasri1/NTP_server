#include "NTP_client_header.h"


//for testing only
newUser :: newUser()
{

}

newUser :: newUser(string mobile,string name,string userId,string password,string emailId,string temp_Password)
{
	this -> mobile = mobile;
	this -> name = name;
	this -> userId = userId;
	this -> password = password;
	this -> emailId = emailId;
	this -> temp_Password = temp_Password;
}

//end testing


//#define size 256
void choice_and_port_set_on_cmd_line_argument(int argc,char *argv[],int &port,int &choice)
{
	int temp_port;
	
	if(argc == 1)
	{	
		choice = 2;//creating a new user
	}
	else if(argc == 2 )
	{
		
		choice = 1; //taking the password of existing user
		
	}
	else
	{	
		cout<<"Invalid Entry !"<<endl;
		exit(1);
	}
}

// registering a new user
void newUser :: add_new_User()
{
	string re_password;
	cout<<"\n\nNew User Details "<<endl;
	cout<<"-------------------------------"<<endl;
	
	cout<<"\nEnter your Name :"<<endl<<"=> ";
	//fgets(name,sizeof(name)-1,stdin);
	getline(cin>>ws,name);
	cout<<"Enter User ID :"<<endl<<"=> ";
	cin>>userId;
	cout<<"Enter your Email ID :"<<endl<<"=> ";
	cin>>emailId;
	cout<<"Enter your Mobile Number :"<<endl<<"=> ";
	cin>>mobile;
	while(1)
	{
		cout<<"Enter Password :"<<endl<<"=> ";
		cin>>password;
		cout<<"Enter Re-Password :"<<endl<<"=> ";
		cin>>re_password;
		
		//password validation for correct password
		if(password == re_password)
		{
			break;
		}
		else
		{
			cout<<"\n\nPassword and Re-Password are not same ! \nPlease Enter again\n"<<endl;
		}
	
	}
}

//asking a password of existing user
void newUser :: existing_user(string user,int cnt)
{
	if(cnt==3)
	{
	cout<<"\n\nExisting User"<<endl;
	cout<<"------------------------------------"<<endl;
	cout<<"User Id : "<<user<<endl;
	cout<<"Enter Your Password :"<<endl<<"=> ";
	cin>>temp_Password;
	}
	else
	{
	cout<<"\nLogin Credentials are Invalid !"<<endl;
	cout<<"Only "<<cnt<<" Attempts Left !"<<endl;
	cout<<"Please enter your Correct Password :"<<endl<<"=> ";
	cin>>temp_Password;
	}
}

//converting all data of new user in to one string
string newUser :: newUserDataInOneString()
{
	string sum="2"+userId+","+password+","+emailId+","+mobile+","+name;
	return sum;
}

//converting userid and password of exixting user in to one string
string newUser :: existingUserCredInOneString(string user)
{
	string sum="1"+user+","+temp_Password;
	return sum;
}

void sig_handler(int signum)
{	 
  
}





	
	
	
	
	
