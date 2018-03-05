#include <iostream>
#include "string"
using namespace std;
void najdi(int &a,int &b, char** matrika,char znak)
{
	if(znak=='j')
		znak='i';
	for (int x = 0; x < 5; x++)
	{
		for (int w = 0; w < 5; w++)
		{
			if(znak==matrika[x][w])
			{
				a=x;
				b=w;
				break;
			}
		}
	}
}

extern "C" __declspec (dllexport) char* Sifriraj1(char* kljuc,int dolzina_kljuc,char* besedilo, int dolzina_besedilo)
{
	char** matrika=new char*[5];
	for(int x=0;x<5;x++)
		matrika[x]=new char[5];
	for (int x = 0; x < 5; x++)
		for (int y = 0; y < 5; y++)
			matrika[x][y] = '\0';
    int* AdoZ = new int[26];
    for (int x = 0; x < 26; x++)
		AdoZ[x] = 0;
    int y = 0, z = 0;
	//vnesemo kljuè v matriko
    for (int x = 0; x < dolzina_kljuc; x++)
    {
		if (AdoZ[kljuc[x]-97] == 0)
        {
			if (kljuc[x] - 97 == 9 || kljuc[x] - 97 == 8)
            {
				matrika[y][z] = 'i';
                AdoZ[9] = 1;
                AdoZ[8] = 1;
            }
            else
			{
				matrika[y][z] = kljuc[x];
                AdoZ[kljuc[x] - 97] = 1;
            }
            z++;
            if (z == 5)
            {
				z = 0;
                y++;
            }
		}
	}
	AdoZ[9]=1;
	//matriko napolnimo s preostalimi èrkami
    for (int x = 0; x < 26; x++)
    {
		if (AdoZ[x] == 0)
        {
			matrika[y][z] = (char)(x+97);
            z++;
            if (z == 5)
            {
				z = 0;
                y++;
            }
        }
    }
	string r2sifriranje="";
	int vrinjeno=0;
	//kjer so dve zaporedni enaki èrki med njiju damo x
	for(int x=0;x<dolzina_besedilo-1;x++)
	{
		if(besedilo[x]==besedilo[x+1])
		{
			r2sifriranje=r2sifriranje+besedilo[x]+"x";
			vrinjeno++;
		}
		else
		{
			r2sifriranje=r2sifriranje+besedilo[x]+besedilo[x+1];
			x++;
		}
	}
	//èe zadnja èrka nima para, dodamo x
	if((dolzina_besedilo+vrinjeno)%2!=0)
		r2sifriranje=r2sifriranje+besedilo[dolzina_besedilo-1]+"x";
	string zasifrirano="";
	//jemljemo po 2 èrki, ravnamo se po 3 pravilih
	for(int x=0;x<r2sifriranje.length();x=x+2)
	{
		int x1,y1,x2,y2;
		najdi(x1,y1,matrika,r2sifriranje[x]);
		najdi(x2,y2,matrika,r2sifriranje[x+1]);
		if(x1==x2)
			zasifrirano=zasifrirano+matrika[x1][(y1+1)%5]+matrika[x1][(y2+1)%5];
		else if(y1==y2)
			zasifrirano=zasifrirano+matrika[(x1+1)%5][y1]+matrika[(x2+1)%5][y2];
		else
			zasifrirano=zasifrirano+matrika[x1][y2]+matrika[x2][y1];
	}
	char *buf = new char[zasifrirano.length()+1];
	for(int i = 0; i < zasifrirano.length(); i++)
	{
		buf[i] = zasifrirano[i];
	}
	buf[zasifrirano.length()]='\0';
	return buf;
}
extern "C" __declspec (dllexport) char* Desifriraj1(char* kljuc,int dolzina_kljuc,char* besedilo, int dolzina_besedilo)
{
	char** matrika=new char*[5];
	for(int x=0;x<5;x++)
		matrika[x]=new char[5];
	for (int x = 0; x < 5; x++)
		for (int y = 0; y < 5; y++)
			matrika[x][y] = '\0';
    int* AdoZ = new int[26];
    for (int x = 0; x < 26; x++)
		AdoZ[x] = 0;
    int y = 0, z = 0;
	//zapišemo kljuè v matriko
    for (int x = 0; x < dolzina_kljuc; x++)
    {
		if (AdoZ[kljuc[x]-97] == 0)
        {
			if (kljuc[x] - 97 == 9 || kljuc[x] - 97 == 8)
            {
				matrika[y][z] = 'i';
                AdoZ[9] = 1;
                AdoZ[8] = 1;
            }
            else
			{
				matrika[y][z] = kljuc[x];
                AdoZ[kljuc[x] - 97] = 1;
            }
            z++;
            if (z == 5)
            {
				z = 0;
                y++;
            }
		}
	}
	AdoZ[9]=1;
	//zapolnimo matriko
    for (int x = 0; x < 26; x++)
    {
		if (AdoZ[x] == 0)
        {
			matrika[y][z] = (char)(x+97);
            z++;
            if (z == 5)
            {
				z = 0;
                y++;
            }
        }
    }
	//jemljemo po 2 èrki, ravanmo se po 3 pravilih
	string zasifrirano="";
	for(int x=0;x<dolzina_besedilo;x=x+2)
	{
		int x1,y1,x2,y2;
		najdi(x1,y1,matrika,besedilo[x]);
		najdi(x2,y2,matrika,besedilo[x+1]);
		if(x1==x2)
		{
			if(y1-1<0)
				zasifrirano=zasifrirano+matrika[x1][4];
			else
				zasifrirano=zasifrirano+matrika[x1][y1-1];
			if(y2-1<0)
				zasifrirano=zasifrirano+matrika[x2][4];
			else
				zasifrirano=zasifrirano+matrika[x1][y2-1];
		}
		else if(y1==y2)
		{
			if(x1-1<0)
				zasifrirano=zasifrirano+matrika[4][y1];
			else
				zasifrirano=zasifrirano+matrika[x1-1][y1];
			if(x2-1<0)
				zasifrirano=zasifrirano+matrika[4][y2];
			else
				zasifrirano=zasifrirano+matrika[x2-1][y2];
		}
		else
			zasifrirano=zasifrirano+matrika[x1][y2]+matrika[x2][y1];
	}
	char *buf = new char[zasifrirano.length()+1];
	for(int i = 0; i < zasifrirano.length(); i++)
	{
		buf[i] = zasifrirano[i];
	}
	buf[zasifrirano.length()]='\0';
	return buf;
}