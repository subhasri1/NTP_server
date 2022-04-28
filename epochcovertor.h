#include<iostream>
#include<time.h>
using namespace std;

void epochcovertor (int &epochserv,int &GMThour,int &GMTmin,int &GMTsec,int &GMTmday,int &GMTmon,int &GMTyear)
{
	struct tm t={0};//initiazlinzing all to zeros
	time_t epochtime;
	t.tm_year=GMTyear-1900;
	t.tm_mon=GMTmon-1;
	t.tm_mday=GMTmday;
	t.tm_hour=GMThour;
	t.tm_min=GMTmin;
	t.tm_sec=GMTsec;
	//t.tm_isdst=-1;                                //Is DST on ? 1 on yes / 0 on no / -1 on unknown
	epochtime = mktime(&t);
	//cout<<"Seconds since the Epoch is "<< (long) t_of_day<<endl;
	epochserv=(long) epochtime;
	return ;
}

