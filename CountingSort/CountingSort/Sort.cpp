#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include "Sort.h"
using namespace std;
const char* counting (char* vhod)
{
	const char*aaa;
	const char* aa;
	aaa=strstr(vhod, " ");
	aa=strstr(aaa+1, " ");
	char bbb[15];
	strncpy(bbb, vhod, aaa-vhod);
	int n=atoi(bbb);
	strncpy(bbb, aaa+1, aa-aaa);
	int br=atoi(bbb);
	int *a= new int[n];
	int *count = new int [br];
	int *out = new int[n];
	string *s=new string[10*n];
	ostringstream ostr;
	int i=0, k=0, j=0, b=0;
	ostr<<"1.korak: štetje\n";
	srand((unsigned)time(NULL));
	for (i=0; i<n; i++) {a[i]=(int)(((double)rand()/(RAND_MAX+1))*br);}
	for (i=0; i<br; i++) {count[i]=0;}
	for (i=0; i<n; i++) {out[i]=0;}
	for (i=0; i<n; i++) 
	{
		(count[a[i]])++;
	}
	ostr<<"indeksi: ";
	for (i=0; i<n; i++)
	{
		ostr<<i;
		ostr<<" ";
	}
	ostr<<"\n";
	ostr<<"polje: ";
	for (i=0; i<n; i++)
	{
		ostr<<a[i];
		ostr<<" ";
	}
	ostr<<"\n";
	ostr<<"števci: ";
	for (i=0; i<br; i++)
	{
		ostr<<count[i];
		ostr<<" ";
	}
	ostr<<"\n\n";
	for (i=0; i<br; i++)
	{
		k=count[i]+k;
		count[i]=k;
	}
	ostr<<"2. korak: seštevanje vrednosti v polju števcev";
	ostr<<"indeksi: ";
	for (i=0; i<n; i++)
	{
		ostr<<i;
	    ostr<<" ";
	}
	ostr<<"\n";
	ostr<<"števci: ";
	for (i=0; i<br; i++)
	{
		ostr<<count[i];
	    ostr<<" ";
	}
	ostr<<"\n\n";

	ostr<<"3. korak: urejenje";
	for (i=0; i<n; i++)
	{
		ostr<<"indeksi: ";
		for (j=0; j<n; j++)
		{
			ostr<<i; 
			ostr<<" ";
		}
		ostr<<"\n";
		ostr<<"polje: ";
		for (j=0; j<n; j++)
		{
			if (j==i) {ostr<<"->"; ostr<<a[j]; ostr<<"<- ";}
			ostr<<a[j];
		}
		ostr<<"\n";
		ostr<<"polje2: ";
		k=count[a[i]];
		k--;
		out[k]=a[i];
		(count[a[i]])--;
		for (j=0; j<n; j++)
		{
			if (j==i) {ostr<<"->"; ostr<<out[j]; ostr<<"<- ";}
			ostr<<out[j];
		}
		ostr<<"\n";
		ostr<<"števci: ";
		for (j=0; j<br; j++)
		{
			ostr<<count[j]; ostr<<" ";
		}
		ostr<<"\n";
		for (j=0; j<80; j++) {ostr<<"_";}
		ostr<<"\n";
	}
	delete[]a;
	delete[]count;
	delete[]out;
	(*s)+=ostr.str();
	return s->c_str();
}