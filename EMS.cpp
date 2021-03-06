#include "EMS.h"

using namespace std;
EMS::EMS(const char* filename,int l,int d)
{
    mercount =0;
    init();
    int sizeofA = (int)pow(4,l);
    motif_l = l;
    motif_d = d;
    char *l_mer = new char[l];
    FILE *fp;
    char StrLine[1024],StrLineFM[1024];
    if((fp = fopen(filename,"r")) == NULL)      //判断文件是否存在及可读  
    {   
        cout<<filename<<"Open Failed"<<endl;
        return ;   
    }   
    while (!feof(fp))    
    {
        fgets(StrLine,1024,fp);
        if(StrLine[0]=='>')
            continue;
        StrLine[strlen(StrLine)-2]='\0';// 最后有\r\n;
        int len =strlen(StrLine);
        for(int i =0;i<len+1-l;i++)
        {
            memcpy(l_mer,StrLine+i,l);   
            newmap->insert(pair<string,int>(l_mer,1));
            oldmap->insert(pair<string,int>(l_mer,1));
            //process(l_mer);
        } 
        process();
        int size = oldmap->size();
        cout<<"oldmap size："<<size<<endl;
        hashmap::iterator it2 = oldmap->begin();
        while(it2!=oldmap->end())
        {
           if(it2->first.length()==motif_l)
           {
               A2[it2->first]++;  
           }
           it2++;
        }
        newmap->clear();
        oldmap->clear();
        mercount++;
    }
    int couttotal =0;
    //cout<<"A2 size :"<<A2.size()<<endl;
      for(hashmap::iterator it = A2.begin();it!=A2.end();it++)
     {
         if(it->second == mercount)
         {
        //    cout<<"motif:"<<it->first<<endl;
            couttotal++;
         }
     }
     cout<<couttotal<<endl;
    delete [] l_mer;
    
}
void EMS::init()
{
    newmap = new hashmap();
    oldmap = new hashmap();
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


void EMS::process()
{
    for(int i =0;i<motif_d;i++)
    {
        editOneTime(i);
    }
}

void EMS::editOneTime(int edittimes)
{
    edittimes++;
    int level = edittimes+1;
    hashmap* tempmap = new hashmap();
    string itstr;
    string temp;
    //cout<<"sizeof newmap:"<<newmap->size()<<endl;
    for(hashmap::iterator it = newmap->begin();it!=newmap->end();it++)
    {
        int i =0;
        itstr = it->first;
        int itstrLen = itstr.length();
        int difs = motif_l-itstrLen>0?motif_l-itstrLen:itstrLen-motif_l;
        int difd = motif_l-itstrLen+1>0?motif_l-itstrLen+1:itstrLen-1-motif_l;
        int difi = motif_l-itstrLen-1>0?motif_l-itstrLen-1:itstrLen+1-motif_l;
        for(i = 0;i<itstrLen;i++)
        {

        //substitut
        if(difs<=motif_d-edittimes)
        {
            for(int i1 = 0;i1<alphabetsize;i1++)
            {
                temp = itstr;
                temp.replace(i,1,1,alphabet[i1]);
                if(!eleExist(*oldmap,temp) )
               {
                  // if(strcmp("TTTAGAGA",temp.c_str())==0)
                  //      cout<<"123";
                   (*tempmap)[temp] =level;
                   // (*oldmap)[temp] = level;
               }
            }
        }
            //deletess
            if(difd<=motif_d-edittimes)
            {
                temp = itstr;
                temp.erase(i,1);
                if(!eleExist(*oldmap,temp) )
                {
                   (*tempmap)[temp] =level;
                //    (*oldmap)[temp] = level;
                } 
            }  
            //insert
           if(difi<=motif_d-edittimes)
           { 
               for(int i1 = 0;i1<alphabetsize;i1++)
                {
                    temp = itstr;
                    temp.insert(i,1,alphabet[i1]);
                    if(!eleExist(*oldmap,temp) )
                        {
                   (*tempmap)[temp] =level;
                 //   (*oldmap)[temp] = level;
                        }
                }
             }
        }
        //insert at last pos
        if(difi<=motif_d-edittimes)
        {
            for(int i1 = 0;i1<alphabetsize;i1++)
            {
                temp = itstr;
                temp.insert(i,1,alphabet[i1]);
                if(!eleExist(*oldmap,temp) )
                    {
                   (*tempmap)[temp] =level;
                 //   (*oldmap)[temp] = level;
                    }
            }
        }
    }
    //now element in newmap become old ,so combine oldmap and newmap
    //and set tempmap as newmap

    newmap->clear();
    for(hashmap::iterator it = tempmap->begin();it!=tempmap->end();it++)
    {
        (*newmap)[it->first] = it->second;
        (*oldmap)[it->first] = it->second;
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
bool EMS::eleExist(hashmap map,string key)
{
   hashmap::iterator it = map.find(key);
   if (it != map.end())
    return true;
else
    return false;
}