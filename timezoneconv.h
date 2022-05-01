#include<iostream>
#include<time.h>
#define fsize 256

using namespace std;

void timezoneconv(long &tot , char buf[size])
{
	time_t xepoch_time=tot;
	
	/*CONVERT To Struct tm */
	struct tm *converted_time;
	converted_time = localtime(&xepoch_time);
	
	tzset();//setting time
	
	strftime(buf,26,"%Y-%m-%d %H:%M:%S",converted_time);
	cout<<"TIME STAMP ACCORDING TO SYSTEM TIMEZONE=>"<<tzname[converted_time->tm_isdst]<<endl;
	//timezonetime=buffer+" "+tzname[converted_time->tm_isdst];

	return ;
}
