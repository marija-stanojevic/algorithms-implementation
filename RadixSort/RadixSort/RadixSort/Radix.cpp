#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cmath>
#include "Radix.h"
using namespace std;
const char* radix (char* vhod)
{
	//namesti n i br
	const char*aaa;
	const char* aa;
	aaa=strstr(vhod, " ");
	aa=strstr(aaa+1, " ");
	char bbb[15];
	strncpy(bbb, vhod, aaa-vhod);
	int n=atoi(bbb);
	strncpy(bbb, aaa+1, aa-aaa);
	int br=atoi(bbb); //preveriti da li dobro dela
	int *a= new int[n];
	int *bucket = new int [10];
	int *b = new int[n];
	string *s=new string[10*n];
	ostringstream ostr;
	int i=0, m, exp=1;
	ostr<<"1.korak: sezam stevila";
	srand((unsigned)time(NULL));
	for (i=0; i<n; i++) 
	{
		a[i]=(int)(((double)rand()/(RAND_MAX+1))*br);
		a[i]++;
	}
	for (i=0; i<n; i++) {b[i]=0;}

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
	ostr<<"\n\n";
	m=a[0];
	for (i = 0; i < n; i++)
  {
    if (a[i] > m)
      m = a[i];
  }
  while (m / exp > 0)
  {
    int bucket[10] =
    {  0 };
    for (i = 0; i < n; i++)
      bucket[a[i] / exp % 10]++;
    for (i = 1; i < 10; i++)
      bucket[i] += bucket[i - 1];
    for (i = n - 1; i >= 0; i--)
      b[--bucket[a[i] / exp % 10]] = a[i];
    for (i = 0; i < n; i++)
      a[i] = b[i];
    exp *= 10;
	ostr<<"2. korak: sortiranje";
	ostr<<"indeksi: ";
	for (i=0; i<n; i++)
	{
		ostr<<i;
	    ostr<<" ";
	}
	ostr<<"\n";
	ostr<<"polja ";
	for (i=0; i<n; i++)
	{
		ostr<<a[i];
	    ostr<<" ";
	}
	ostr<<"\n\n";		
	}
	delete[]a;
	delete[]b;
	delete[]bucket;
	(*s)+=ostr.str();
	return s->c_str();
}