#ifndef _FSL_LS
#define _FSL_LS

#include <string>
#include <stdio.h>
#include <io.h>
#include <time.h>
using namespace std;

string convet_date(time_t timeStamp){
    struct tm *timeinfo = nullptr;
    char buffer[80];
    timeinfo = localtime(&timeStamp);
    strftime(buffer,80,"%Y-%m-%d",timeinfo);
    return (string)(buffer);
}

namespace ls {
    void ls(string adr) {
        adr += "\\*";
        long handle;
        _finddata_t fileinfo;
        printf("time\t\t\tsize\t\tname\n");
        printf("----\t\t\t----\t\t----\n");
        handle = _findfirst(adr.c_str(),&fileinfo);
        do {
            string name = fileinfo.name;
            if(fileinfo.size == 0) name = "\033[33m"+name+"/\033[0m";
            printf("%s %18ld\t\t%s\n",convet_date(fileinfo.time_write).c_str(),fileinfo.size,name.c_str());
        } while(!_findnext(handle,&fileinfo));
        _findclose(handle);
    }
} 

#endif