#include<iostream>//system call, data types
using namespace std;
#include<sys/socket.h>//socket
#include<unistd.h>//read & write
#include<arpa/inet.h>//ip
#include<fstream>//filehandling
#include<map>//map STL
#include<cstring>//strcpy
#include<stdlib.h>//atoi

#include<ctime>

void user_cred_file_to_map(map<string, string> &user_cred);//key,value--->userid,password

void login_and_registration_of_user(int cli_des,map<string, string> userCred);

char user_cred_authentication(map<string, string> user_cred, char data[],int n);

void user_cred_addition(map<string, string> &user_cred,char new_user_info[],int k);

time_t gettimefromLocalMachine();

time_t gettimefromserver(char* hname );

time_t GmT_to_epoch_coversion(tm *best_time_gmt);


