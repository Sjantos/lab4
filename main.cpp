#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
using std::string;

const   string ones[10] = {"", " jeden", " dwa", " trzy", " cztery", " piec", " szesc", " siedem", " osiem", " dziewiec"};
const   string teens[10] = {" dziesiec", " jedenascie", " dwanascie", " trzynascie", " czternascie", " pietnascie", " szesnascie", " siedemnascie", " osiemnascie", " dziewietnascie"};
const   string tens[10] ={"", " dziesiec", " dwadziescia", " trzydziesci", " czterdziesci", " piecdziesiat", " szescdziesiat", " siedemdziesiat", " osiemdziesiat", " dziewiecdziesiat"};
const   string hundreds[10] = {"", " sto", " dwiescie", " trzysta", " czterysta", " piecset", " szescset", " siedemset", " osiemset", " dziewiecset"};
const   string x[7] = {"", " tys", " mln.", " mld.", " bln.", " bld."};
const   string thousends[9] = {" tysiac", " tysiace", " tysiace", " tysiace", " tysiecy", " tysiecy", " tysiecy", " tysiecy", " tysiecy"};
//tablica moglaby byc duzo mniejsza, sprawdzalem tylko szybkosc programu
unsigned long long int tab[131072];

string verballynumber(unsigned long long int number);
void filltab();
unsigned long long int searchk(unsigned long long int n);

int main(int argc, char **argv)
{
    filltab();
    unsigned long long int n=atoi(argv[1]);
    unsigned long long int k=searchk(n);
    cout<<"Liczba n "<<verballynumber(n)<<endl;
    cout<<"Liczba k "<<verballynumber(k)<<endl;
    cout<<"Liczba 0/1 "<<verballynumber(n*k)<<endl;

    return 0;
}

string verballynumber(unsigned long long int number)
{
    string verbally=" ";
    unsigned long int ending, multi=0, j=0, tys;

    if (number==0) verbally="zero";
    tys=(number/1000)%1000;

    while (number>0)
    {
        ending=(number%10);
        number/=10;
        if ((j==0)&&(number%100!=0 || ending!=0)) verbally.insert(0, multi==1? thousends[tys<9? tys-1 : 8] : x[multi]);
        if ((j==0)&&(number%10!=1)) verbally.insert(0, ones[ending]);
        if ((j==0)&&(number%10==1))
        {
            verbally.insert(0, teens[ending]);
            number/=10;
            j+=2;
            continue;
        }
        if (j==1) verbally.insert(0, tens[ending]);
        if (j==2)
        {
            verbally.insert(0, hundreds[ending]);
            j=-1;
            multi++;
        }
        j++;
    }
    return verbally;
}

void filltab()
{
    tab[0]=0; tab[1]=1;
    int index1;
    for(int i=2; i<131072; i++)
    {
        int index, bit=0, j=i;
        while(j>1){j=j>>1; bit++;}
        index=pow(2, bit);
        if(i==index)
        {
            tab[i]=1;
            for(int z=0; z<bit; z++) tab[i]*=10;
            index1=1;
        }
        else
        {
            tab[i]=tab[index]+tab[index1];
            index1++;
        }
    }
}

unsigned long long int searchk(unsigned long long int n)
{
    unsigned long long int k;
    for(int i=1; i<131072; i++)
    {
        if(tab[i]%n==0) 
        { 
        	//cout<<tab[i]<<endl; 
        	return tab[i]/n;
        }
    }
}