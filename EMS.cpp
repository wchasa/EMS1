#include "EMS.h"
#include<stdlib.h>
#include<iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
EMS::EMS(const char* filename,int l,int d)
{
    int n =0;
    init();
    int sizeofA = (int)pow(4,l);
    motif_l = l;
    motif_d = d;
    //test char* str = "ACCGTC";
    //int ivalue = convertCharToInt(str);
    //char* re  = convertIntToChar(ivalue);
    //cout<<re<<endl;
    A1 = new int[sizeofA];
    A2 = new int[sizeofA];
    char *l_mer = new char[l];
    FILE *fp;
    char StrLine[1024],StrLineFM[1024];
    if((fp = fopen(filename,"r")) == NULL)      //判断文件是否存在及可读  
    {   
        //cout<<filename2<<"Open Failed"<<endl;
        return ;   
    }   
    while (!feof(fp))    
    {
        fgets(StrLine,1024,fp);
        if(StrLine[0]=='#')
            continue;
        StrLine[strlen(StrLine)-1]='\0';
        int len =strlen(StrLine);
        for(int i =0;i<len+1-l;i++)
        {
            memcpy(l_mer,StrLine+i,l);
            process(l_mer);
        }  
        n++;
    }
    for(int i =0;i<pow(4,l);i++)
        {
            if(n==A2[i])
            {
                    cout<<convertIntToChar(i)<<endl;
            }
        }
    delete [] l_mer;
    
}
void EMS::init()
{
    chartoIntMap.insert(pair<char,char>(0,'A'));
    chartoIntMap.insert(pair<char,char>(1,'C'));
    chartoIntMap.insert(pair<char,char>(2,'G'));
    chartoIntMap.insert(pair<char,char>(3,'T'));
    chartoIntMap.insert(pair<char,char>('A',0));
    chartoIntMap.insert(pair<char,char>('C',1));
    chartoIntMap.insert(pair<char,char>('G',2));
    chartoIntMap.insert(pair<char,char>('T',3));
}
char * EMS::convertIntToChar(int input)
{
    char value =0;
    char * p =new char[motif_l];
    for(int i=0;i<motif_l;i++)
    {
        value =  input&0x03;
        p[motif_l-i-1]  =  chartoIntMap[(char)value];
        input = input>>2;
    }
    return p;
    //delete [] p;
    //p=NULL;
}

int EMS::convertCharToInt(char *input)
{
    int value = 0;
    for(int i =0;i<motif_l;i++)
    {
      value += chartoIntMap[input[i]];
      value = value<<2;
    }
    return value>>2;
}

void EMS::process(char* lmer)
{
    string strtxt((char*)lmer);
    oldhashmap.insert(pair<string,int>(strtxt,0));
    for(int i =0;i<motif_d;i++)
    {
        editOneTime();
    }
}

void EMS::editOneTime()
{

}