#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include "kmpmain.h"
using namespace std;

const char* kmpmain (char* vhod1, char* vhod2)
{
	int m=0, i=0, n=0, b=0, sub=0, j=0, l=0;
	int* T;
	char* s1=vhod1;
	ostringstream ostr;
	string *s=new string[100];
	//naivni pristop
	while (*s1!='\0')
	{
		m++;
		s1++;
	}
	T=new int[m];
	for (i=0; i<m; i++) {*(T+i)=0;}
	s1=vhod2;
	while (*s1!='\0')
	{
		n++;
		s1++;
	}
	ostr<<"Naivni pristop \n";
	b=0;
	s1=vhod2;
	while (*s1!='\0' && b==0)
	{
		i=(s1-vhod2+1);
		ostr<<i;
		ostr<<". korak:\n";
		ostr<<vhod2;
		ostr<<"\n";
		for (i=0; i<s1-vhod2; i++)
		{
			ostr<<"  ";
			if ((i-1)%3==0){ostr<<" ";}
		}
		ostr<<vhod1;
		ostr<<"\n";
		if (memcmp(vhod1,s1,m)==0) {b=1;}
		s1++;
	}
	
	//Knuth-Moris-Pratt
	ostr<<"\n Knuth-Morish-Prat algoritem \n";
	ostr<<"Predprocesiranje vzorca\n";
	//predprocesiranje
	(*T)=-1; *(T+1)=0;
	i=2;
	sub=0;
	while (i<m)
	{
		if (*(vhod1+i-1)==*(vhod1+sub))
		{
			sub++;
			*(T+i)=sub;
			i++;
		}
		else if (sub>0)
		{
			sub=*(T+sub);
		}
		else 
		{
			*(T+i)=0;
			i++;
		}
	}
	for (i=2; i<=m; i++)
	{
		ostr<<i-1;
		ostr<<". korak \n";
		ostr<<"i         ";
		for (j=0; j<m; j++)
		{
			ostr<<j;
			ostr<<"  ";
			if (j%3==0) {ostr<<" ";}
		}
		ostr<<"\n";
		ostr<<"p        ";
		s1=vhod1;
		for (j=0; j<m; j++)
		{
			ostr<<*s1;
			s1++;
			ostr<<"  ";
		}
		ostr<<"\n";
		ostr<<"kmp  ";
		ostr<<"-1  0  ";
		for (j=2; j<i; j++)
		{
				ostr<<*(T+j);
				ostr<<"  ";
				if ((j-2)%3==0) ostr<<" ";
		}
		ostr<<"\n\n";
	}
	//iskanje niza znakov
	ostr<<"2. Iskanje niza znakov v tekstu:\n\n";
	i=0; j=0; b=0;  l=1;
	//ostali koraci
	while (j+i<n && b==0)
	{
		if (*(vhod1+i)==*(vhod2+j+i))
		{
			if (i==m-1) 
			{
				b=1;
				ostr<<l++;
				ostr<<". korak:\n";
				ostr<<vhod2;
				ostr<<"\n";
				for (int k=0; k<j; k++)
				{
					ostr<<"  ";
					if ((k-1)%3==0) {ostr<<" ";}
				}
				ostr<<vhod1;
				ostr<<"\n";
			}
			i=i+1;
		}
		else 
		{
			ostr<<l++;
			ostr<<". korak:\n";
			ostr<<vhod2;
			ostr<<"\n";
			for (int k=0; k<j; k++)
			{
				ostr<<"  ";
				if ((k-1)%3==0) {ostr<<" ";}
			}
			ostr<<vhod1;
			ostr<<"\n";
			ostr<<"=> premik = ";
			ostr<<i;
			if (*(T+i)<0){ostr<<" - (";ostr<<*(T+i); ostr<<")";}
			else{ostr<<" - ";ostr<<*(T+i);}
			ostr<<" = ";
			ostr<<i-*(T+i);
			ostr<<"\n";
			j=j+i-*(T+i);
			if (*(T+i)>-1){i=*(T+i);}
			else {i=0;}
		}
	}
	

	delete[]T;
	(*s)+=ostr.str();
	return s->c_str();
}