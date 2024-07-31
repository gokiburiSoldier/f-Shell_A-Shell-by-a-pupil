#ifndef _FS_CLI_H
#define _FS_CLI_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

#include "fsl/cd.h"
#include "fsl/ls.h"
#include "fsl/echo.h"
#include "fsl/rw.h"
using namespace std;

namespace run {
    string prom = "\033[35m $ \033[34m",
           adr = (string)("C:\\Users\\")+getenv("USERNAME"),
           user = getenv("USERNAME");
    string readline(void) {
        string s;
        cout << user << "@" << adr << prom;
        getline(cin,s);
        cout << "\033[0m";
        return s;
    }
    vector<string> spliter(string sent) {
        sent += " ";
        vector<string> rt;
        string t;
        char c;
        int len = sent.length();
        for(int i=0;i<len;++ i) {
            c = sent[i];
            switch(c) {
                case '#':
                    if(t != "") rt.push_back(t);
                    return rt;
                    break;
                case ' ':
                    if(t != "") rt.push_back(t);
                    t = "";
                    break;
                default:
                    t += c;
            }
        }
        if(t != "") rt.push_back(t);
        return rt;
    }

    int run(vector<string> t) {
        if(t.empty()) return 0;
        string fsl = t[0];
        if(fsl == "cd") {
            if(t.size() == 1) return -1;
            if(cd::exist_floder(adr+"\\"+t[1])) {
                if(t[1] == "..") {
                    int len = adr.length(),i;
                    if(len == 2) return 0;
                    for(i=1;adr[len-i] != '\\';++ i) adr = adr.substr(0,len-i);
                    adr = adr.substr(0,len-i);
                }else adr += "\\"+t[1];
            }else return 2;
        } else if(fsl == "ls") ls::ls(adr);
        else if(fsl == "echo") eh::echo(t);
        else if(fsl == "cat") {
            if(t.size() == 1) return -1;
            return rw::typing(adr+"\\"+t[1]);
        } else if(fsl == "cls" || fsl == "clear") system("cls");
        else if(fsl == "quit" || fsl == "exit");
        else if(fsl == "wt") {
            string a;
            int len = t.size();
            for(int i=1;i<len;++i) {
                if(t[i] == "-a") {
                    if(i == len-1) return -1;
                    a = t[i+1];
                    break;
                }
            }
            if(a == "") return -1;
            return rw::writing(adr+"\\"+a,t,a);
        }
        else if(fsl == "prg") {
            if(t.size() == 1) return -1;
            string c;
            int len = t.size();
            for(int i=1;i<len;++ i) c += t[i]+" ";
            system(c.c_str());
        }
        else if(fsl.length() == 2 && fsl[1] == ':') adr = fsl;
        else return 1;
        
        return 0;
    }
} 

#endif