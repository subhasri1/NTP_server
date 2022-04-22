#include<iostream>
#include<time.h>
using namespace std;

void gmtcovertor(int &GMThour,int &GMTmin,int &GMTsec)
{
	time_t curr_time;
	curr_time = time(NULL);
	tm *X = gmtime (&curr_time);
	//cout<<"Current time : "<< X->tm_hour  <<":"<<X->tm_min <<":"<<X->tm_sec<<" GMT"<<endl;
	GMThour=X->tm_hour;
	GMTmin=X->tm_min;
	GMTsec=X->tm_sec;
	//cout<<GMThour<<endl;
	return ;
}

