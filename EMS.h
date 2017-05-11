#ifndef _Inarray
#define _Inarray
#include<stdlib.h>
#include<iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <unordered_map>
#include <map>
#include <unistd.h>
#include <vector>
using namespace std;
typedef char i8;
typedef  long long int i64;
//typedef std::map<string,i8> hashmap;
typedef std::map<int,vector<string> > hashmap;
typedef std::pair<int,vector<string> > hashpair;
class mymap
{
public:
    mymap(int motifl);
    void insert(string,i8);

private:
    
    int stelen;
    vector<i8> values;
};

class EMS
{
public:
 //   EMS();
    EMS(const char* filename,i8 l,i8 d);
private:
    hashmap opermap;
    i64 Alength;
    i8 motif_l;
    i8 motif_d;
    i8* A1;
    i8* A2;
//    hashmap A1;
 //   hashmap A2;
    map<char,char> chartoIntMap;
    string convertIntToChar(int input);
    int convertCharToInt(const char *input);
    void init();
    //void process(char* lmer);
    void process(string& strtxt,int edittimes,char oper);
    void newprocess(string& strtxt,int edittimes,string oper);
 //   hashmap* newmap;
  //  hashmap* oldmap;
    //hashmap* tempmap;
    char* alphabet;
    int alphabetsize;
    void editOneTime(i8 edittimes);
    i8 mercount;
    vector<string> gen(int nl);
   // bool eleExist(hashmap map,string key);
};
#endif