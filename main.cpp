#include<stdlib.h>
#include<string.h>
#include<ctime>
#include<fstream>
#include<iostream>
#include<iomanip>
#include"EMS.h"
int main(int argc,char* argv[])
{
    if(argc !=4)
    {
        cout<<"need three args;<filename> <l> <d>";
        return 0;
    }   
    EMS em(argv[1],atoi(argv[2]),atoi(argv[3]));    
    return 0;
}