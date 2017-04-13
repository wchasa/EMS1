#include<stdlib.h>
#include<string.h>
#include<ctime>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<time.h>
#include"EMS.h"
int main(int argc,char* argv[])
{
    double t1,t2;
    if(argc !=4)
    {
        cout<<"need three args;<filename> <l> <d>";
        return 0;
    }
    t1 = clock();   
    EMS em(argv[1],atoi(argv[2]),atoi(argv[3]));    
    t2 = clock();
    cout<<"处理时间："<<double(t2-t1)/CLOCKS_PER_SEC<<"s"<<endl;
    return 0;
}