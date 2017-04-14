#ifndef _Inarray
#define _Inarray
#include<stdlib.h>
#include<iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <unordered_map>
#include <map>
using namespace std;

typedef std::unordered_map<string,int> hashmap;
typedef std::pair<string,int> hashpair;
class EMS
{
    public:
 //   EMS();
    EMS(const char* filename,int l,int d);
    private:
    int motif_l;
    int motif_d;
    hashmap A1;
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
    void editOneTime(int edittimes);
    int mercount;
};
#endif