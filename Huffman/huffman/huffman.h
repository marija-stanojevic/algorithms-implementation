#include <iostream>
#include "string"
#include <sstream>
using namespace std;

//zakomentirana je koda za shranjevanje zaetnega niza.

struct drevo
{
	int utez;
	int stevilo;
	char znak;
	drevo* levi;
	drevo* desni;
	drevo* oce;
};

string najdi(char znak, string niz,drevo* koren)
{
	if(znak==koren->znak)
		return niz;
	if(koren->levi==NULL)
		return "narobe";
	string levo=niz+"0";
	string desno=niz + "1";
	string pravi=najdi(znak,levo,koren->levi);
	if(pravi=="narobe")
		return najdi(znak,desno,koren->desni);
	else
		return pravi;
}

drevo* najdi_po_mestu(int mesto,drevo* koren)
{
	if(mesto==koren->stevilo)
		return koren;
	if(koren->levi==NULL)
		return NULL;
	drevo* pravi=najdi_po_mestu(mesto,koren->levi);
	if(pravi==NULL)
		return najdi_po_mestu(mesto,koren->desni);
	else
		return pravi;
}

drevo* najdi_po_znaku(char znak,drevo* koren)
{
	if(znak==koren->znak)
		return koren;
	if(koren->levi==NULL)
		return NULL;
	drevo* pravi=najdi_po_znaku(znak,koren->levi);
	if(pravi==NULL)
		return najdi_po_znaku(znak,koren->desni);
	else
		return pravi;
}

char najdi_poKodi(string besedilo, drevo* koren,int mesto)
{
	if(koren->levi==NULL)
		return koren->znak;
	if(mesto==besedilo.length())
		return (char)257;
	char pravi=(char)257;
	if(besedilo[mesto]=='0')
		pravi=najdi_poKodi(besedilo,koren->levi,mesto+1);
	else
		pravi=najdi_poKodi(besedilo,koren->desni,mesto+1);
	return pravi;
}

string decimalnoVbinarno(int decimalno)
{
    string pretvorba="";
    while(decimalno!=0)
    {
        if(decimalno%2==0)
            pretvorba="0"+pretvorba;
        else
            pretvorba="1"+pretvorba;
        decimalno=decimalno/2;
    }
    return pretvorba;
}

string v_Bajt(string pretvorba)
{
    while(pretvorba.size()<8)
        pretvorba="0"+pretvorba;
	return pretvorba;
}

int binarnoVdecimalno(string pretvorba)
{
    int decimalno=0;
	int stevilo=1;
    for(int x=7;x>=0;x--)
    {
        if(pretvorba[x]=='1')
            decimalno=decimalno+stevilo;
        stevilo=stevilo*2;
    }
    return decimalno;
}

extern "C" __declspec (dllexport) char* Sifriraj1(char* besedilo1)
{
	string besedilo(besedilo1);
	//(char) 257 - brez znaka
	//(char) 256 - NYT znak
	int st_crk=0;
	string zakodirano="";
	drevo *trenutni; //zaèasni kazalec za premikanje
	int naprej=0;
	drevo *koren=new drevo();
	drevo *zacetni_znak=new drevo();
	zacetni_znak->desni=NULL;
	zacetni_znak->oce=NULL;
	zacetni_znak->utez=0;
	zacetni_znak->znak=(char) 256;
	zacetni_znak->levi=NULL;
	zacetni_znak->stevilo=0;
	koren->oce=NULL;
	koren->utez=0;
	koren->znak=(char) 257;
	koren->desni=NULL;
	koren->levi=NULL;
	koren->stevilo=0;
	int tabela[256];
	for(int x=0;x<256;x++)
		tabela[x]=0;
	int dolzina_besedila=besedilo.length();
	for(int x=0;x<dolzina_besedila;x++)
	{
		naprej=0;
		if(koren->levi==NULL)
		{
			koren->levi=zacetni_znak;
			zacetni_znak->oce=koren;
			koren->utez=1;
			drevo* naslednji=new drevo();
			naslednji->znak=besedilo[x];
			naslednji->utez=1;
			naslednji->desni=NULL;
			naslednji->levi=NULL;
			naslednji->oce=koren;
			naslednji->stevilo=-1;
			koren->desni=naslednji;
			zacetni_znak->stevilo=-2;
			zakodirano=v_Bajt(decimalnoVbinarno((int)besedilo[x]));
			tabela[(int)besedilo[x]]=1;
			st_crk++;
		}
		else if(tabela[(int)besedilo[x]]==0)
		{
			naprej=1;
			st_crk++;
			string vrni=najdi((char)256,"",koren);
			zakodirano=zakodirano + vrni + v_Bajt(decimalnoVbinarno((int)besedilo[x]));
			//novo vstavljeni element
			drevo* nov1=new drevo();
			drevo* nov=new drevo();
			nov1->utez=1;
			nov1->znak=besedilo[x];
			nov1->levi=NULL;
			nov1->desni=NULL;
			nov1->oce=nov;
			nov1->stevilo=zacetni_znak->stevilo-1;
			tabela[(int)besedilo[x]]=1;
			//element nad NYT in na novo vstavljenim
			nov->utez=0;
			nov->znak=(char)257;
			nov->levi=zacetni_znak;
			nov->desni=nov1;
			nov->oce=zacetni_znak->oce;
			nov->stevilo=zacetni_znak->stevilo;
			zacetni_znak->oce->levi=nov;
			zacetni_znak->oce=nov;
			zacetni_znak->stevilo=zacetni_znak->stevilo-2;
			trenutni=nov1->oce;
		}
		else
		{
			naprej=1;
			string vrni=najdi(besedilo[x],"",koren);
			zakodirano=zakodirano+vrni;
			trenutni=najdi_po_znaku(besedilo[x],koren);
		}
		if(naprej==1)
		{
			while(trenutni->oce!=NULL)//dokler nismo pri korenu
				{
					int vrednost=trenutni->stevilo;
					drevo *prejsnji=najdi_po_mestu(vrednost+1,koren); //najdemo naslednjega
					vrednost++;
					if(prejsnji->utez==trenutni->utez) //èe ima enako vrednost uteži, gremo naprej iskat zadnjega z enako vrednostjo uteži
					{
						while(vrednost<-1)//najdemo zadnjega z enako vrednostjo
						{
							drevo* zamenjaj=najdi_po_mestu(vrednost+1,koren);
							if(zamenjaj->utez==trenutni->utez)
								prejsnji=zamenjaj;
							else
								break;
							vrednost++;
						}
						if(prejsnji!=trenutni->oce)//èe zadnji ni oèe 
						{
							int stevilo_temp=trenutni->stevilo; //zamenjamo mesti
							trenutni->stevilo=prejsnji->stevilo;
							prejsnji->stevilo=stevilo_temp;
							if(prejsnji->oce->levi==prejsnji)//èe je 1.levi sin
							{
								if(prejsnji->oce==trenutni->oce)//èe imata istega oèeta
								{
									prejsnji->oce->levi=trenutni;
									prejsnji->oce->desni=prejsnji;
								}
								else{
								drevo* oce_temp=trenutni->oce;
								prejsnji->oce->levi=trenutni;
								trenutni->oce=prejsnji->oce;
								prejsnji->oce=oce_temp;
								if(oce_temp->levi==trenutni)//èe je 2.levi sin
									oce_temp->levi=prejsnji;
								else //èe je 2. desni sin
									oce_temp->desni=prejsnji;
								}
							}
							else //èe je 1.desni sin
							{
								if(prejsnji->oce==trenutni->oce)//èe imata istega oèeta
								{
									prejsnji->oce->desni=trenutni;
									prejsnji->oce->levi=prejsnji;
								}
								else{
								drevo* oce_temp=trenutni->oce;
								prejsnji->oce->desni=trenutni;
								trenutni->oce=prejsnji->oce;
								prejsnji->oce=oce_temp;
								if(oce_temp->levi==trenutni)//èe je 2.levi sin
									oce_temp->levi=prejsnji;
								else //èe je 2. desni sin
									oce_temp->desni=prejsnji;}
							}
						}
					}
					trenutni->utez++;//poveèamo utež
					trenutni=trenutni->oce;
				}
		}
	}
	/*int ostanek=zakodirano.length()%8;
	if(ostanek==0)
		ostanek=8;
	string polno=v_Bajt(decimalnoVbinarno(8-ostanek));
	zakodirano=polno+zakodirano;*/
	char *buf = new char[zakodirano.length()+1];
	for(int i = 0; i < zakodirano.length(); i++)
	{
		buf[i] = zakodirano[i];
	}
	buf[zakodirano.length()]='\0';
	return buf;
}
extern "C" __declspec (dllexport) char* Desifriraj1(char* kljuc)
{
	string besedilo(kljuc);
	//(char) 257 - brez znaka
	//(char) 256 - NYT znak
	string zakodirano="";
	drevo *koren=new drevo();
	drevo *zacetni_znak=new drevo();
	zacetni_znak->desni=NULL;
	zacetni_znak->oce=NULL;
	zacetni_znak->utez=0;
	zacetni_znak->znak=(char) 256;
	zacetni_znak->levi=NULL;
	zacetni_znak->stevilo=0;
	koren->oce=NULL;
	koren->utez=0;
	koren->znak=(char) 257;
	koren->desni=NULL;
	koren->levi=NULL;
	koren->stevilo=0;
	int tabela[256];
	for(int x=0;x<256;x++)
		tabela[x]=0;
	string iskanje="";
	char vrni;
	//string taprvi1=besedilo.substr(0,8);
	//int konec=besedilo.length()-binarnoVdecimalno(taprvi1);
	//for(int x=8;x<konec;x++)
	for(int x=0;x<besedilo.length();x++)
	{
		iskanje=iskanje+besedilo[x];
		if(koren->levi==NULL)
		{
			//string taprvi=besedilo.substr(8,8);
			string taprvi=besedilo.substr(0,8);
			char znakec=(char)binarnoVdecimalno(taprvi);
			koren->levi=zacetni_znak;
			zacetni_znak->oce=koren;
			koren->utez=1;
			drevo* naslednji=new drevo();
			naslednji->znak=znakec;
			naslednji->utez=1;
			naslednji->desni=NULL;
			naslednji->levi=NULL;
			naslednji->oce=koren;
			naslednji->stevilo=-1;
			koren->desni=naslednji;
			zacetni_znak->stevilo=-2;
			zakodirano=znakec;
			tabela[(int)znakec]=1;
			iskanje="";
			//x=15;
			x=7;
		}
		else if((vrni=najdi_poKodi(iskanje,koren,0))==(char)256)
		{
			char nov_vstavi=(char)binarnoVdecimalno(besedilo.substr(x+1,8));
			if(tabela[(int)nov_vstavi]==0)
			{
				zakodirano=zakodirano + nov_vstavi;
				x=x+8;
				//novo vstavljeni element
				drevo* nov1=new drevo();
				drevo* nov=new drevo();
				nov1->utez=1;
				nov1->znak=nov_vstavi;
				nov1->levi=NULL;
				nov1->desni=NULL;
				nov1->oce=nov;
				nov1->stevilo=zacetni_znak->stevilo-1;
				tabela[(int)nov_vstavi]=1;
				//element nad NYT in na novo vstavljenim
				nov->utez=0;
				nov->znak=(char)257;
				nov->levi=zacetni_znak;
				nov->desni=nov1;
				nov->oce=zacetni_znak->oce;
				nov->stevilo=zacetni_znak->stevilo;
				zacetni_znak->oce->levi=nov;
				zacetni_znak->oce=nov;
				zacetni_znak->stevilo=zacetni_znak->stevilo-2;
				drevo* temp=nov1;
				iskanje="";
				while(temp->oce->oce!=NULL)//dokler nismo pri korenu
				{
					temp=temp->oce;
					int vrednost=temp->stevilo;
					drevo *prejsnji=najdi_po_mestu(vrednost+1,koren); //najdemo naslednjega
					vrednost++;
					if(prejsnji->utez==temp->utez) //èe ima enako vrednost uteži, gremo naprej iskat zadnjega z enako vrednostjo uteži
					{
						while(vrednost<-1)//najdemo zadnjega z enako vrednostjo
						{
							drevo* zamenjaj=najdi_po_mestu(vrednost+1,koren);
							if(zamenjaj->utez==temp->utez)
								prejsnji=zamenjaj;
							else
								break;
							vrednost++;
						}
						if(prejsnji!=temp->oce)//èe zadnji ni oèe 
						{
							int stevilo_temp=temp->stevilo; //zamenjamo mesti
							temp->stevilo=prejsnji->stevilo;
							prejsnji->stevilo=stevilo_temp;
							if(prejsnji->oce->levi==prejsnji)//èe je 1.levi sin
							{
								if(prejsnji->oce==temp->oce)//èe imata istega oèeta
								{
									prejsnji->oce->levi=temp;
									prejsnji->oce->desni=prejsnji;
								}
								else{
								drevo* oce_temp=temp->oce;
								prejsnji->oce->levi=temp;
								temp->oce=prejsnji->oce;
								prejsnji->oce=oce_temp;
								if(oce_temp->levi==temp)//èe je 2.levi sin
									oce_temp->levi=prejsnji;
								else //èe je 2. desni sin
									oce_temp->desni=prejsnji;}
							}
							else //èe je 1.desni sin
							{
								if(prejsnji->oce==temp->oce)//èe imata istega oèeta
								{
									prejsnji->oce->desni=temp;
									prejsnji->oce->levi=prejsnji;
								}
								else{
								drevo* oce_temp=temp->oce;
								prejsnji->oce->desni=temp;
								temp->oce=prejsnji->oce;
								prejsnji->oce=oce_temp;
								if(oce_temp->levi==temp)//èe je 2.levi sin
									oce_temp->levi=prejsnji;
								else //èe je 2. desni sin
									oce_temp->desni=prejsnji;}
							}
						}
					}
					temp->utez++;//poveèamo utež
				}
			}
		}
		else
		{
			if(vrni!=(char)257){
				iskanje="";
			zakodirano=zakodirano+vrni;
			drevo *trenutni=najdi_po_znaku(vrni,koren); //najdemo naslednjega
			while(trenutni->oce!=NULL)//dokler nismo pri korenu
			{
				int vrednost=trenutni->stevilo;
				drevo *prejsnji=najdi_po_mestu(vrednost+1,koren); //najdemo naslednjega
				vrednost++;
				if(prejsnji->utez==trenutni->utez) //èe ima enako vrednost uteži, gremo naprej iskat zadnjega z enako vrednostjo uteži
				{
					while(vrednost<-1)//najdemo zadnjega z enako vrednostjo
					{
						drevo* zamenjaj=najdi_po_mestu(vrednost+1,koren);
						if(zamenjaj->utez==trenutni->utez)
							prejsnji=zamenjaj;
						else
							break;
						vrednost++;
					}
					if(prejsnji!=trenutni->oce)//èe zadnji ni oèe 
					{
						int stevilo_temp=trenutni->stevilo; //zamenjamo mesti
						trenutni->stevilo=prejsnji->stevilo;
						prejsnji->stevilo=stevilo_temp;
						if(prejsnji->oce->levi==prejsnji)//èe je 1.levi sin
						{
							if(prejsnji->oce==trenutni->oce)//èe imata istega oèeta
							{
								prejsnji->oce->levi=trenutni;
								prejsnji->oce->desni=prejsnji;
							}
							else{
							drevo* oce_temp=trenutni->oce;
							prejsnji->oce->levi=trenutni;
							trenutni->oce=prejsnji->oce;
							prejsnji->oce=oce_temp;
							if(oce_temp->levi==trenutni)//èe je 2.levi sin
								oce_temp->levi=prejsnji;
							else //èe je 2. desni sin
								oce_temp->desni=prejsnji;
							}
						}
						else //èe je 1.desni sin
						{
							if(prejsnji->oce==trenutni->oce)//èe imata istega oèeta
							{
								prejsnji->oce->desni=trenutni;
								prejsnji->oce->levi=prejsnji;
							}
							else{
							drevo* oce_temp=trenutni->oce;
							prejsnji->oce->desni=trenutni;
							trenutni->oce=prejsnji->oce;
							prejsnji->oce=oce_temp;
							if(oce_temp->levi==trenutni)//èe je 2.levi sin
								oce_temp->levi=prejsnji;
							else //èe je 2. desni sin
								oce_temp->desni=prejsnji;}
						}
					}
				}
				trenutni->utez++;//poveèamo utež
				trenutni=trenutni->oce;
			}
		}
	}
	}
	char *buf = new char[zakodirano.length()+1];
	for(int i = 0; i < zakodirano.length(); i++)
	{
		buf[i] = zakodirano[i];
	}
	buf[zakodirano.length()]='\0';
	return buf;
}