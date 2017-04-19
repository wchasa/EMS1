#include "EMS.h"

using namespace std;
EMS::EMS(const char* filename,int l,int d)
{
    mercount =0;
    init();
    int sizeofA = (int)pow(4,l);
    motif_l = l;
    motif_d = d;
    //test char* str = "ACCGTC";
    //int ivalue = convertCharToInt(str);
    //char* re  = convertIntToChar(ivalue);
    //cout<<re<<endl;
   // A1 = new int[sizeofA];
   // A2 = new int[sizeofA];
    //memset(A1,sizeofA,-1);
    //memset(A2,sizeofA,0);
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
        if(StrLine[0]=='>')
            continue;
        StrLine[strlen(StrLine)-2]='\0';// 最后有\r\n;
        int len =strlen(StrLine);
        for(int i =0;i<len+1-l;i++)
        {
            memcpy(l_mer,StrLine+i,l);   
            process(l_mer);
        } 
        int size = oldmap->size();
        cout<<"oldmap size："<<size<<endl;
        hashmap::iterator it2 = oldmap->begin();
        while(it2!=oldmap->end())
        {
           if(it2->first.length()==motif_l && it2->second != -mercount-1 )
           {
               it2->second = -mercount-1;
               A2[it2->first]++;  
           }
           it2++;
        }
       // cout<<it2->first<<","<<it2->second<<endl;
    /*    for( hashmap::iterator it = oldmap->begin();it!=oldmap->end();it++)
        {
           if(it->first.length()==motif_l && it->second !=mercount+1 )
           {
               it->second =mercount+1;
               A2[it->first]++;  
           }
        }
        */
        oldmap->clear();
        mercount++;
    }
    int couttotal =0;
   // cout<<"A2 size :"<<A2.size()<<endl;
      for(hashmap::iterator it = A2.begin();it!=A2.end();it++)
     {
         if(it->second == mercount)
         {
            cout<<"motif:"<<it->first<<endl;
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


void EMS::process(char* lmer)
{
    string strtxt((char*)lmer);
    //(*temp)[] = 1;
    newmap->clear();
    //oldmap->clear();
    newmap->insert(pair<string,int>(strtxt,0));
    //A1.insert(pair<string,int>(strtxt,-1));
    oldmap->insert(pair<string,int>(strtxt,0));
    for(int i =0;i<motif_d;i++)
    {
        editOneTime(i);
    }
    /*int size = A2.size();
    cout<<"A2 size："<<size<<endl;
    for(hashmap::iterator it = A1.begin();it!=A1.end();it++)
    {
        if(it->first.length()==motif_l && it->second !=mercount+1 )
        {
            it->second =mercount+1;
            A2[it->first]++;  
        }
    }*/

}

void EMS::editOneTime(int edittimes)
{
    edittimes++;
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
                if((*oldmap)[temp]<=0||(*oldmap)[temp]>=edittimes)
               {
                    tempmap->insert(pair<string,int>(temp,edittimes));
                  //  (*oldmap)[temp] =edittimes;
             //       cout<<"substitut:"<<temp<<endl;
               }
            }
        }
            //deletess
            if(difd<=motif_d-edittimes)
            {
                temp = itstr;
                temp.erase(i,1);
                if((*oldmap)[temp]<=0||(*oldmap)[temp]>=edittimes)
                {
                    tempmap->insert(pair<string,int>(temp,edittimes));
                   // (*oldmap)[temp] =edittimes;
                //  cout<<"delete:"<<temp<<endl;
                } 
            }  
            //insert
           if(difi<=motif_d-edittimes)
           { 
               for(int i1 = 0;i1<alphabetsize;i1++)
                {
                    temp = itstr;
                    temp.insert(i,1,alphabet[i1]);
                    if((*oldmap)[temp]<=0||(*oldmap)[temp]>=edittimes)
                        {
                    //       cout << "insert:" << temp << endl;
                            tempmap->insert(pair<string,int>(temp,edittimes));
                          //  (*oldmap)[temp] =edittimes;
                        }
                }
             }
        }
        if(difi<=motif_d-edittimes)
        {
            for(int i1 = 0;i1<alphabetsize;i1++)
            {
                temp = itstr;
                temp.insert(i,1,alphabet[i1]);
                if((*oldmap)[temp]<=0||(*oldmap)[temp]>=edittimes)
                    {
                 //       cout << "insert:" << temp << endl;
                        tempmap->insert(pair<string,int>(temp,edittimes));
                        //(*oldmap)[temp] =edittimes;
                    }
            }
        }
    }
    //now element in newmap is become old ,so combine oldmap and newmap
    //and set tempmap as newmap
    for(hashmap::iterator it = newmap->begin();it!=newmap->end();it++)
    {
        (*oldmap)[it->first] = it->second;
        //if(A1[it->first]==0)
        //    A1[it->first]= -1;
        //cout<<"newmap:"<<it->first<<endl;
    }
    newmap->clear();
    for(hashmap::iterator it = tempmap->begin();it!=tempmap->end();it++)
    {
        (*newmap)[it->first] = it->second;
        (*oldmap)[it->first] = it->second;
        //if(A1[it->first]==0)
        //    A1[it->first]= -1;
        //cout<<"tempmap:"<<it->first<<endl;
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