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
using namespace std;
typedef char i8;
typedef std::unordered_map<string,i8> hashmap;
typedef std::pair<string,i8> hashpair;
class EMS
{
    public:
 //   EMS();
    EMS(const char* filename,i8 l,i8 d);
    private:
    i8 motif_l;
    i8 motif_d;
//    hashmap A1;
    hashmap A2;
    map<char,char> chartoIntMap;
    char * convertIntToChar(int input);
    int convertCharToInt(char *input);
    void init();
    void process(char* lmer);
    hashmap* newmap;
    hashmap* oldmap;
    //hashmap* tempmap;
    char* alphabet;
    int alphabetsize;
    void editOneTime(i8 edittimes);
    i8 mercount;
    bool eleExist(hashmap map,string key);
};
#endif