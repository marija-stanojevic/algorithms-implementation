#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "LZW.h"
#include <cmath>
using namespace std;

class Elem{
public: 
	unsigned char zn;
	int kod;
	Elem*poc;
	Elem*brat;
};

vector<bool> bitVector;
int newSize=0;
Elem* el;
int kk=128;

bool dodaj(Elem*e, string s)
{
		string pom=s.substr(1, s.length()-1);
		Elem* tek=e->poc;
		bool c=false;
		if (e->poc!=NULL)
		{
			while (tek->brat!=NULL && !c)
			{
				if (s[0]!=tek->zn){tek=tek->brat;}
				else {c=true;}
			}
			if (tek!=NULL && tek->zn==s[0]){c=true;}
			if (c==true) 
			{
				if (pom.length()==0)
				{
					return true;
				}
				else
				{
					if (pom.length()>0) return dodaj(tek, pom);
				}
			}
			else 
			{
				tek->brat=new Elem(); 
				tek=tek->brat; 
				tek->kod=kk++; 
				tek->zn=s[0]; 
				if (pom.length()>0)	return dodaj(tek, pom);
				return false;
			}
		}
		else 
		{
			e->poc=new Elem();
			tek=e->poc; tek->kod=kk++; tek->zn=s[0]; 
			if (pom.length()>0) return dodaj(tek, pom);
			return false;
		}
}

void ispisi ()
{
	if (newSize%8!=0)
	{
		for (int i=0; i<4; i++)
		bitVector.push_back(0);
		newSize+=4;
	}
	ofstream fout;
	fout.open("kodirano.bin", ios::binary);
	if (fout.is_open()) 
	{
		int p=128;
		unsigned char zn=0;
		for (int i=0; i<bitVector.size(); i++)
		{
			if (p>0)
			{
				zn+=p*bitVector[i];
				p/=2;
				if (p==0) {if (zn==32) zn=255; fout<<zn; zn=0; p=128;}
			}
		}
	}
	fout.close();
}

const char* zip (char*vhod1)
{
	unsigned char* c;
	int n;
	newSize=0;
	string pom="";
	bitVector.clear();
	c= new unsigned char [10000];
	int i=0;
	bool b;
	ifstream rf;
	rf.open(vhod1);
	if (rf.is_open()){while (!rf.eof()) {rf>>c[i++];}}
	rf.close();
	n=i-1;
	el=new Elem();
	el->zn=NULL;
	el->kod=0;
	el->poc=new Elem();
	el->brat=NULL;
	Elem* tek=el->poc;
	for (int i=1; i<128; i++)
	{
		tek->zn=(char)i;
		tek->kod=i;
		tek->poc=NULL;
		if (i!=127) 
		{
			tek->brat=new Elem(); 
			tek=tek->brat;
		}
	}
	b=true;
	bool bb=true;
	pom=c[0];
	for (int i=1; i<=n; i++)
	{	
		bb=dodaj(el, pom);
		if (b==true && bb==true) 
		{
			if (i!=n) pom+=c[i];
		}
		if (bb==false)
		{
			int r=0;
			Elem*tek=el;
			while (r<pom.length()-1)
			{
				tek=tek->poc;
				while (tek->zn!=pom[r])
				{
					tek=tek->brat;
				}
				r++; 
			}
			int ppom=tek->kod;
			int j=0;
			while (ppom!=0)
			{
				j++; ppom/=2;
			}
			for (int i=0; i<12-j; i++)
			{
				bitVector.push_back(0); newSize++;
			}
			ppom=tek->kod;
			for (int i=12-j; i<12; i++)
			{
				bitVector.push_back(ppom / (int)pow(2.0, 12-i-1)); newSize++;
				if (bitVector[newSize-1]==1) {ppom=ppom-(int)pow(2.0, 12-i-1);}
			}
			int rr=pom.length()-1;
			unsigned char rrr=pom[rr];
			pom=rrr;
			if (i!=n) pom+=c[i];
			b=bb;
		}
		if (b==false && bb==true)
		{
			if (i!=n) pom+=c[i];
			b=true;
		}
	}
	if (pom.length()>0)
	{
		tek=el;
		int r=0;
		while (r<pom.length())
			{
				tek=tek->poc;
				while (tek->zn!=pom[r])
				{
					tek=tek->brat;
				}
				r++; 
			}
			int ppom=tek->kod;
			int j=0;
			while (ppom!=0)
			{
				j++; ppom/=2;
			}
			for (int i=0; i<12-j; i++)
			{
				bitVector.push_back(0); newSize++;
			}
			ppom=tek->kod;
			for (int i=12-j; i<12; i++)
			{
				bitVector.push_back(ppom / (int)pow(2.0, 12-i-1)); newSize++;
				if (bitVector[newSize-1]==1) {ppom=ppom-(int)pow(2.0, 12-i-1);}
			}
	}
	ispisi();
	int d=((double)newSize/(n*8))*100;
	char*buf=new char[5];
	new string(itoa(d, buf, 10));
	return buf;
}

void ispisi1 (string s)
{
	ofstream fout;
	fout.open("razsireno.txt");
	if (fout.is_open()) 
	{
		for (int i=0; i<s.length(); i++)
		{
			{fout<<s[i];}
		}
	}
	fout.close();
}

string trazi(Elem* e, int kod)
{
	string s="";
	bool bo=false;
	Elem*tek;
	if (e!=NULL)
	{
	if (e->kod==kod) {s=e->zn; return s;}
	else 
	{
		tek=e->poc;
		if (tek!=NULL)
		{
		if (tek->kod==kod) {s+=tek->zn; s+=e->zn; return s;}
		string p=trazi(tek, kod);
		if (p.compare("")) {s+=trazi(tek, kod);}
		while (tek!=NULL)
		{
			tek=tek->brat;
			p=trazi(tek, kod);
			if (p.compare("")) {s+=trazi(tek, kod);}
		}
		}
	}
		return s;
	}
	else return "";
}

const char* unzip (char*vhod1)
{
	newSize=0;
	int n=0;
	string izhod="";
	bitVector.clear();
	unsigned char* ci= new unsigned char [10000];
	bool b;
	ifstream rf;
	rf.open(vhod1, ios::binary);
	int k=0;
	if (rf.is_open())
	{while (!rf.eof()) 
	{
		rf>>ci[k++];
		if (ci[k-1]==255) ci[k-1]=32;
	}
	}
	k--;
	if (k>0)
	{
	for (int i=0; i<k; i++)
	{
		int p=128;
		for (int j=0; j<8; j++)
		{
			bitVector.push_back(ci[i]/p);
			ci[i]=ci[i]-p*bitVector[newSize++];
			p=p/2;
		}
	}
	if (k%3!=0) {for (int i=0; i<4; i++) bitVector.pop_back(); newSize-=4;}
	}
	int r=newSize/12;
	for (int i=0; i<r; i++)
	{
		int kod=0;
		int dec=1;
		for (int j=0; j<12; j++)
		{
			kod+=dec*bitVector[--newSize];
			bitVector.pop_back();
			dec*=2;
		}
		izhod+=trazi(el, kod);
	}
	int br=izhod.length();
	for (int i=0; i<br/2; i++)
	{
		char pc=izhod[i];
		izhod[i]=izhod[br-i-1];
		izhod[br-i-1]=pc;
	}
	ispisi1(izhod);
	int d=((double)100*k/izhod.length());
	char*buf=new char [5];
	new string(itoa(d, buf, 10));
	return buf;
}