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

    alphabetsize = 4;
    alphabet = new char[alphabetsize];
    alphabet[0] ='A';
    alphabet[1] ='C';
    alphabet[2] ='G';
    alphabet[3] ='T';
    for(int i = 0;i<alphabetsize;i++)
    {
        chartoIntMap.insert(pair<char,char>((char)i,alphabet[i]));
        chartoIntMap.insert(pair<char,char>(alphabet[i],(char)i));
    }
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
    oldmap->insert(hashpair(strtxt,1));
    for(int i =0;i<motif_d;i++)
    {
        editOneTime();
    }
}

void EMS::editOneTime()
{
    string itstr;
    string temp;
    for(hashmap::iterator it = newmap->begin();it!=newmap->end();it++)
    {
        int i =0;
        itstr = it->first;
        int itstrLen = itstr.length();
        for(i = 0;i<itstrLen;i++)
        {

        //substitut
            for(int i1 = 0;i1<alphabetsize;i1++)
            {
                temp = itstr;
                temp.replace(i,1,1,alphabet[i1]);
                if((*oldmap)[temp]!=1)
                    tempmap->insert(hashpair(temp,1));
            }
            //delete
            temp = itstr;
            temp.erase(i);
            if((*oldmap)[temp]!=1)
            {
                tempmap->insert(hashpair(temp,1));
            }   
            //insert
            for(int i1 = 0;i1<alphabetsize;i1++)
            {
                temp = itstr;
                itstr.insert(i,1,alphabet[i1]);
                if((*oldmap)[temp]!=1)
                    tempmap->insert(hashpair(temp,1));
            }
        }
        for(int i1 = 0;i1<alphabetsize;i1++)
        {
                temp = itstr;
                itstr.insert(i,i,alphabet[i1]);
                if((*oldmap)[temp]!=1)
                    tempmap->insert(hashpair(temp,1));
        }
    }
    //now element in newmap is become old ,so combine oldmap and newmap
    //and set tempmap as newmap
    
}