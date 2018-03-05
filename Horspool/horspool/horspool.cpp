#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <fstream>
#include <string.h>
#include "horspool.h"
using namespace std;
const char* horspool (char* x, char* y, char*z)
{
	char * izhod=NULL;
	int n, m=0, kon=0;
	char* s1=x;
	int * st=new int [1000];
	string* c=new string [1000];
	if (z[0]!='p'&& z[1]!='r' && z[2]!='a' && z[3]!='z' && z[4]!='n' && z[5]!='o' && z[6]!='\n') 
	{
		int i=0;
		ifstream rf;
		rf.open(z);
		if (rf.is_open()){while (!rf.eof() && i<1000) {getline (rf, c[i++]);}}
		n=i;
	}
	else { c[0]= y; n=1;}
	for (int i=0; i<n; i++)
	{
		kon+=c[i].length();

	}
	kon+=1000;
	izhod=new char[kon];
	while (*s1!='\0')
	{
		m++;
		s1++;
	}
	int* occ=new int[255];
	s1=y;
	for (int j=0; j<255; j++)
	{
		occ[j]=m;
	}
	for (int j=0; j<m-1; j++)
	{
		occ[*(x+j)]=m-j-1;
	}
	kon=0;
	int pp=0;
	for (int i=0; i<n; i++)
	{
		int j=0;
		while (j+m<=c[i].length())
		{
			string pod;
			int duz=m-1;
			bool b=true;
			while (b==true) 
			{//c[i][j+duz]!=x[duz]
				char cc=(c[i]).substr(j+duz,1)[0];
				if (cc!=x[duz]) {b=false;}
				duz--;
			}
			if (duz>=0) {duz++; j+=occ[(c[0].substr(duz,1)[0])];}
			else 
			{
				st[pp++]=i; st[pp++]=j;
				for (int broj=0; broj<j; broj++) {izhod[kon++]=c[i][broj];}
				izhod[kon++]='`';
				for (int broj=0; broj<m; broj++) {izhod[kon++]=c[i][broj+j]; //napraviti podstring za krajnji deo niza pod=substr()}
				izhod[kon++]='`';
				j=j+m-1;
			}
		}
			//dodati da se ubaci niz jer u slucaju da nije bilo nicega u nizu, on se ne ispise
	}
	izhod[kon++]='~';
	for (int i=0; i<pp; i++)
	{
		while (st[pp]!=0) {izhod[kon++]=(char)((st[i]%10)+48);}
		izhod[kon++]=','; izhod[kon++]=' ';
	}
	return izhod;
}