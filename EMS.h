#ifndef _Inarray
#define _Inarray
#include <math.h>
#include <unordered_map>
#include <map>
using namespace std;

class EMS
{
    public:
 //   EMS();
    EMS(const char* filename,int l,int d);
    private:
    int motif_l;
    int motif_d;
    int* A1;
    int* A2;
    map<char,char> chartoIntMap;
    char * convertIntToChar(int input);
    int convertCharToInt(char *input);
    void init();
    void process(char* lmer);
    unordered_map<string,int> newhashmap;
    unordered_map<string,int> oldhashmap;

};
#endif