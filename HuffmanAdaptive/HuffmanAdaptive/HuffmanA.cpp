#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "HuffmanA.h"
using namespace std;

class Elem{
public: 
	unsigned char zn;
	int tez;
	Elem*levi;
	Elem*desni;
};

vector<bool> bitVector;
int newSize;
Elem* el;
unsigned char* c;
int n;

bool dodaj1(Elem*e, bool b)
{
	unsigned char ch=0;
	if (e->levi==NULL && e->desni==NULL && b==false && e->zn==NULL)
	{
	if (newSize>=8)
	{
		int p=128;
		for (int i=1; i<=8; i++)
		{
			ch+=p*bitVector[newSize-i];
			p/=2;
		}
	}
		newSize-=8;
		for (int i=0; i<8; i++){bitVector.pop_back();}
		e->levi=new Elem ();
		e->levi->tez=NULL; e->levi->zn=NULL;
		e->desni=new Elem ();
		e->desni->tez=1;
		e->desni->zn=ch;
		c[n++]=ch;
		b=true;
		e->tez=1;
		return true;
	}
		else if (b==false && bitVector.size()>0)
	{
		bool cc=bitVector[newSize-1];
		if (e->desni!=NULL && cc==1) 
		{			
			newSize--;
			bitVector.pop_back();
			b=dodaj1(e->desni, b);
			if (b==false) {newSize++; bitVector.push_back(1);} 
			else 
			{
				e->tez++;
			}
		}
		if (newSize>0)
		{
		cc=bitVector[newSize-1];
		if (e->levi!=NULL && cc==0 && b==false)
		{
			newSize--;
			bitVector.pop_back();
			b=dodaj1(e->levi, b);
			if (b==false) {newSize++; bitVector.push_back(0);} 
			else 
			{
				e->tez++;
			}	
		}
		}
	}
	return b;
}


bool dodaj(Elem*e, unsigned char c, bool b)
{
	if (e->levi==NULL && e->desni==NULL && b==false && e->zn==NULL)
	{
		e->levi=new Elem ();
		e->levi->tez=NULL; e->levi->zn=NULL;
		e->desni=new Elem ();
		e->desni->tez=1; e->desni->zn=c;
		b=true;
		e->tez=1;
		newSize+=8;
		int p=128;
		for (int i=0; i<8; i++)
		{
			bitVector.push_back(c/p);
			c=c-p*(c/p); p=p/2;
		}
		return true;
	}
	else if (b==false)
	{
		if (e->desni!=NULL) 
		{
			bitVector.push_back(1);
			b=dodaj(e->desni, c, b);
			if (b==false) {bitVector.pop_back();} 
			else 
			{
				newSize++;
				e->tez++;
			}
		}
		if (e->levi!=NULL && b==false)
		{
			bitVector.push_back(0);
			b=dodaj(e->levi, c, b);
			if (b==false) {bitVector.pop_back();} 
			else 
			{
				newSize++;
				e->tez++;
			}
		}
		return b;
	}
}

bool huf1 (Elem*e, bool b)
{
	unsigned char ch=0;
	if (b==true) return true;
	else if (newSize>=8)
	{
		int p=128;
		for (int i=1; i<=8; i++)
		{
			ch+=p*bitVector[newSize-i];
			p/=2;	
		}
	}
	if (e->levi==NULL && e->desni==NULL && e->zn!=NULL)
	{
		bool bc=false;
		for (int i=0; i<n; i++)
		{
			if (e->zn==c[i]) {bc=true;}
		}
		if (bc==true)
		{
			e->tez++;
			c[n++]=e->zn;
			return true;
		}
	}
	else if (b==false && bitVector.size()>0)
	{
		bool cc=bitVector[newSize-1];
		if (e->desni!=NULL && cc==1) 
		{	
			newSize--;
			bitVector.pop_back();
			b=huf1(e->desni, b);
			if (b==false) {newSize++; bitVector.push_back(1);} 
			else 
			{
				e->tez++;
			}}
		if (newSize>0) 
		{
			cc=bitVector[newSize-1];
		if (e->levi!=NULL && cc==0 && b==false)
		{
			newSize--;
			bitVector.pop_back();
			b=huf1(e->levi, b);
			if (b==false) {newSize++; bitVector.push_back(0);} 
			else 
			{
				e->tez++;
			}	
		}
		}
	}
	return b;
}
bool huf (Elem*e, unsigned char c, bool b)
{
	if (e->levi==NULL && e->desni==NULL)
	{
		if (c==e->zn) {e->tez++; return true;}
		else return false;
	}
	else 
	{
		if (b==false)
		{
		if (c==e->zn) return true;
		if (e->desni!=NULL) 
		{
			bitVector.push_back(1);
			b=huf(e->desni, c, b);
			if (b==false) {bitVector.pop_back();} 
			else 
			{
				newSize++;
				e->tez++;
			}}
		if (e->levi!=NULL && b==false)
		{
			bitVector.push_back(0);
			b=huf(e->levi, c, b);
			if (b==false) {bitVector.pop_back();} 
			else 
			{
				newSize++;
				e->tez++;
			}	
		}
		return b;
		}
		else if (b==true)
		{
			e->tez=e->levi->tez+e->desni->tez;
			return true;
		}
	}
}

bool sredi (Elem* e, bool b)
{
	if (e->levi==NULL && e->desni==NULL && b==false && e->zn==NULL)
	{
		b=true;
	}
	if (b==false)
	{
		bool c=false;
		if (e->desni!=NULL) 
		{
			b=sredi(e->desni, false);
		}
		if (e->levi!=NULL)
		{
			c=sredi(e->levi, false);
		}
		if (b==true)
		{
			if (e->desni->desni!=NULL)
				if (e->levi->tez<e->desni->desni->tez) 
				{
					Elem* pom=e->levi; 
					e->levi=e->desni->desni;
					e->desni->desni=pom;
					if (e->levi->levi>e->levi->desni) 
					{
						Elem* pom=e->desni->desni; 
						e->desni->desni=e->desni->levi;
						e->desni->levi=pom;
					}
					e->desni->tez=e->desni->levi->tez+e->desni->desni->tez;
				}
				if (e->levi->tez>e->desni->tez) 
					{
						Elem* pom=e->levi; 
						e->levi=e->desni;
						e->desni=pom;
					}
				e->tez=e->levi->tez+e->desni->tez;
		}
		if (c==true)
		{
			if (e->levi->desni!=NULL)
				if (e->desni->tez<e->levi->desni->tez) 
				{
					Elem* pom=e->desni; 
					e->desni=e->levi->desni;
					e->levi->desni=pom;
					if (e->desni->levi>e->desni->desni) 
					{
						Elem* pom=e->levi->desni; 
						e->levi->desni=e->levi->levi;
						e->levi->levi=pom;
					}
					e->levi->tez=e->levi->levi->tez+e->levi->desni->tez;
				}
				if (e->levi->tez>e->desni->tez) 
					{
						Elem* pom=e->levi; 
						e->levi=e->desni;
						e->desni=pom;
					}
				e->tez=e->levi->tez+e->desni->tez;
		}
		if (b==false && c==false && e->levi!=NULL && e->desni!=NULL) 
		{
			if (e->levi->tez>e->desni->tez) 
					{
						Elem* pom=e->levi; 
						e->levi=e->desni;
						e->desni=pom;
					}
		}
		if (c==true) return c;
		else return b;
	}
	if (e->levi->tez>e->desni->tez)
	{
				
	}
}

void ispisi ()
{
	if (newSize%8==0)
	{
		bitVector.push_back(0);
		newSize++;
	}
	else
	{
		bool* bb=new bool[newSize%8];
		for (int i=newSize%8-1; i>=0; i--)
		{
			bb[i]=bitVector[(newSize/8)*8+i];
			bitVector.pop_back();
		}
		for (int i=0; i<8-newSize%8-1; i++)
		{
			bitVector.push_back(1);
		}
		bitVector.push_back(0);
		for (int i=0; i<newSize%8; i++)
		{
			bitVector.push_back(bb[i]);
		}
		newSize=bitVector.size();
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
				if (p==0) {fout<<zn; zn=0; p=128;}
			}
		}
	}
	fout.close();
}

void ispisi1 ()
{
	ofstream fout;
	fout.open("razsireno.txt");
	if (fout.is_open()) 
	{
		for (int i=0; i<n-1; i++)
		{
			{fout<<c[i];}
		}
	}
	fout.close();
}
const char* zip (char*vhod1)
{
	n=0;
	c=new unsigned char[10000];
	newSize=0;
	bitVector.clear();
	string* izhod;
	int i=0;
	bool b;
	ifstream rf;
	rf.open(vhod1);
	if (rf.is_open()){while (!rf.eof()) {rf>>c[i++];}}
	rf.close();
	n=i-1;
	el=new Elem();
	el->zn=NULL;
	el->tez=0;
	for (int i=0; i<n; i++)
	{
		b=false;
		b=huf (el, c[i], b);
		if (b==false) dodaj(el, c[i], b);
		sredi (el, false);
	}
	ispisi();
	int d=(50*newSize/(n*4));
	char*buf=new char[5];
	new string(itoa(d, buf, 10));
	return buf;
}

const char* unzip (char*vhod1)
{
	newSize=0;
	n=0;
	c=new unsigned char[10000];
	bitVector.clear();
	unsigned char* ci= new unsigned char [10000];
	bool b;
	ifstream rf;
	rf.open(vhod1);
	int k=0;
	if (rf.is_open()){while (!rf.eof()) {rf>>ci[k++];}}
	k=k-1;
	if (k>0)
	{
	for (int i=1; i<k-1; i++)
	{
		int p=128;
		for (int j=0; j<8; j++)
		{
			bitVector.push_back(ci[i]/p);
			ci[i]=ci[i]-p*bitVector[newSize++];
			p=p/2;
		}
	}
	bool d=false; 
	int l=128;
	while (l>0)
	{		
		if ((ci[k-1]/l)==0 && d==false)
		{	d=true;
			l/=2;
		}
		if (d==true){bitVector.push_back(ci[k-1]/l);}
		ci[k-1]=ci[k-1]-bitVector[bitVector.size()-1]*l;
		l/=2;
	}
	newSize=bitVector.size();
	for (int i=0; i<newSize/2; i++)
	{
		bool pom=bitVector[i];
		bitVector[i]=bitVector[newSize-i-1];
		bitVector[newSize-i-1]=pom;
	}
	el=new Elem();
	el->zn=NULL;
	el->tez=1;
	el->levi=new Elem();
	el->levi->tez=0;
	el->levi->zn=NULL;
	el->desni=new Elem();
	el->desni->tez=1;
	el->desni->zn=ci[0];
	c[n++]=ci[0];
	while (bitVector.size()>0)
	{
		b=false;
		b=huf1 (el, b);
		if (b==false) dodaj1(el, b);
		sredi (el, false);
	}
	c[n++]='\0';
	ispisi1();
	}
	int d=(100*k/((--n)));
	char*buf=new char [5];
	new string(itoa(d, buf, 10));
	return buf;
}