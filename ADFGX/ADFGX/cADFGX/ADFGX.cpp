#include <iostream>
#include <fstream>
#include <string.h>
#include "ADFGX.h"
using namespace std;

const char* encode (char*vhod1, char*vhod2, char*vhod3)
{
	string * s;
	string * k;
	char * izhod=NULL;
	string c="pgcqxbeonrsdaktmlviwfuyzh";
	if (vhod1[0]!='p'&& vhod1[1]!='r' && vhod1[2]!='a' && vhod1[3]!='z' && vhod1[4]!='n' && vhod1[5]!='o' && vhod1[6]!='\n') 
	{
		int i=0;
		ifstream rf;
		rf.open(vhod1);
		if (rf.is_open()){while (!rf.eof() && i<25) {rf>>c[i++];}}
	}
	int n=0;
	while (vhod3[n]!='\0') 
	{
		if ((int)vhod3[n]>=65 && (int)vhod3[n]<=90) {vhod3[n]=(int)vhod3[n]+32;}
		else if (((int) vhod3[n]>=97) && (int)vhod3[n]<=122) {}
		else izhod="Napaka pri vnosu";
		n++;
	}
	int m=0;
	while (vhod2[m]!='\0') 
	{
		if (((int)vhod2[m]>=65 && (int)vhod2[m]<=90) || ((int) vhod2[m]>=97) && (int)vhod2[m]<=122) {}
		else izhod="Napaka pri vnosu";
		m++;
	}
	s=new string [n];
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<25; j++)
		{
			if (vhod3[i]==c[j] || vhod3[i]=='j') 
			{
				if (vhod3[i]=='j') {vhod3[i]='i';}
				switch (j%5)
				{
				case 0: s[i]="A"; break;
				case 1: s[i]="D"; break;
				case 2: s[i]="F"; break;
				case 3: s[i]="G"; break;
				case 4: s[i]="X"; break;
				}
				switch (j/5)
				{
				case 0: s[i]+="A"; break;
				case 1: s[i]+="D"; break;
				case 2: s[i]+="F"; break;
				case 3: s[i]+="G"; break;
				case 4: s[i]+="X"; break;
				}
			}
		}
	}
		k=new string [m];
		for (int i=0; i<m; i++)
		{
			k[i]="";
		}
		int j=0;
		for (int i=0; i<n; i++)
		{
			if (j==m) {j=0;}
			k[j]+=s[i].substr(0, 1);
			j++;
			if (j==m) {j=0;}
			k[j]+=s[i].substr(1, 1);
			j++;
		}
		for (int i=0; i<m; i++)
			for (j=i+1; j<m; j++)
		{
			if (vhod2[i]>vhod2[j])
			{
				string pom=k[i];
				k[i]=k[j];
				k[j]=pom;
			}
		}
		int l=0;
		int ll=0;
		if (izhod==NULL)
		{
			izhod=new char [2*n+1];
			for (int i=0; i<m; i++)
			{
				for (j=0; j<(2*n)/m+1; j++)
				{
					if ( k[i][0]!='\0')
					{
						if  (k[i].length()>j)
						{
							string ss=k[i].substr(j,1);
							izhod[l++]=ss[0];
						}
					}
				}
			}
			izhod[l]='\0';
		}
		return izhod; 
}

const char* decode (char*vhod1, char*vhod2, char*vhod3)
{
	string s;
	string * k;
	char * izhod=NULL;
	string c="pgcqxbeonrsdaktmlviwfuyzh";
	if (vhod1=="")
	{
		int i;
		ifstream rf;
		rf.open(vhod1);
		if (rf.is_open()){while (!rf.eof() && i<25) {rf>>c[i];}}
	}
	int n=0;
	while (vhod3[n]!='\0') 
	{
		if ((int)vhod3[n]>=65 && (int)vhod3[n]<=90) {vhod3[n]=(int)vhod3[n]+32;}
		else if (((int) vhod3[n]>=97) && (int)vhod3[n]<=122) {}
		else izhod="Napaka pri vnosu";
		n++;
	}
	int m=0;
	while (vhod2[m]!='\0')
	{
		if (((int)vhod2[m]>=65 && (int)vhod2[m]<=90) || ((int) vhod2[m]>=97) && (int)vhod2[m]<=122) {}
		else izhod="Napaka pri vnosu";
		m++;
	}

	string sortKey = vhod2;
	for (int i=0; i<m; i++)
			for (int j=i+1; j<m; j++)
		{
			if (sortKey[i]>sortKey[j])
			{
				char pom=sortKey[i];
				sortKey[i]=sortKey[j];
				sortKey[j]=pom;
			}
		}
	k=new string [m];
	int l=0;
	for (int i=0; i<m; i++)
	{
		int j;
		for (j=0; j<n/m; j++)
		{
			k[i]+=vhod3[l++];
		}
		if (i<n%m) 
		{
			k[i]+=vhod3[l++];
		}
	}
	for (int i=0; i<n; i++)
	{
		s+=k[i%m][i/m];
	}
	if (izhod==NULL)
	{
		izhod=new char[n/2+1];
		l=0;
		int i=0;
		while (i<n)
		{	
		switch (s[i])
		{
			case 'a': 
				{
					switch (s[i+1])
					{
					case 'a': izhod[i/2]=c[0]; break;
					case 'd': izhod[i/2]=c[1]; break;
					case 'f': izhod[i/2]=c[2]; break;
					case 'g': izhod[i/2]=c[3]; break;
					case 'x': izhod[i/2]=c[4]; break;
					}	
					break;
				}
			case 'd': 
				{
					switch (s[i+1])
					{
					case 'a': izhod[i/2]=c[5]; break;
					case 'd': izhod[i/2]=c[6]; break;
					case 'f': izhod[i/2]=c[7]; break;
					case 'g': izhod[i/2]=c[8]; break;
					case 'x': izhod[i/2]=c[9]; break;
					}	
					break;
				}
			case 'f': 
				{
					switch (s[i+1])
					{
					case 'a': izhod[i/2]=c[10]; break;
					case 'd': izhod[i/2]=c[11]; break;
					case 'f': izhod[i/2]=c[12]; break;
					case 'g': izhod[i/2]=c[13]; break;
					case 'x': izhod[i/2]=c[14]; break;
					}	
					break;
				}
			case 'g': 
				{
					switch (s[i+1])
					{
					case 'a': izhod[i/2]=c[15]; break;
					case 'd': izhod[i/2]=c[16]; break;
					case 'f': izhod[i/2]=c[17]; break;
					case 'g': izhod[i/2]=c[18]; break;
					case 'x': izhod[i/2]=c[19]; break;
					}	
					break;
				}
			case 'x': 
				{
					switch (s[i+1])
					{
					case 'a': izhod[i/2]=c[20]; break;
					case 'd': izhod[i/2]=c[21]; break;
					case 'f': izhod[i/2]=c[22]; break;
					case 'g': izhod[i/2]=c[23]; break;
					case 'x': izhod[i/2]=c[24]; break;
					}	
					break;
				}
			}
			i+=2;
		}
		izhod[i/2]='\0';
	}
	return izhod;
}