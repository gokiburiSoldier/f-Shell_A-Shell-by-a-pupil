#ifndef _FS_CLI_H
#define _FS_CLI_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <map>

#include "fsl/cd.h"
#include "fsl/ls.h"
#include "fsl/echo.h"
#include "fsl/rw.h"
#include "admin.h"
#include "fsl/calc.h"
#include "get_code.h"
using namespace std;

bool ctrl_c(DWORD signal) {
    return 0;
}


namespace run {
    map<string,string> vars;
    string prom = (isAdministor() ? "\033[35m # \033[34m" : "\033[35m $ \033[34m"),
           adr = (string)("C:\\Users\\")+getenv("USERNAME"),
           user = getenv("USERNAME"),
           hostname = getenv("COMPUTERNAME");
    string readline(void) {
        string s;
        cout << "\033[32m" << user << "@" << hostname << "\033[33m " << adr << prom;
        getline(cin,s);
        cout << "\033[0m";
        return s;
    }
    bool isVar(string s) {
        int len = s.length();
        return s[0] == '$' && s[len-1] == '$' || s[0] == '@' && s[len-1] == '@';
    }
    vector<string> spliter(string sent) {
        sent += " ";
        vector<string> rt;
        string t;
        char c,sign;
        bool isSt=false;
        int len = sent.length();
        for(int i=0;i<len;++ i) {
            c = sent[i];
            if(isSt) {
                t += c;
                if(c == sign) {
                    isSt = false;
                    rt.push_back(t);
                }
                continue;
            }
            switch(c) {
                case '#':
                    if(t != "") rt.push_back(t);
                    return rt;
                    break;
                case ' ':
                    if(t != "") rt.push_back(t);
                    t = "";
                    break;
                case '$':
                case '@':
                    if(t != "") rt.push_back(t);
                    t = "";
                    sign = c;
                    do {
                        t += sent[i];
                        ++ i;
                    } while(sent[i] != sign && i < len);
                    ++ i;
                    t += sign;
                    rt.push_back(t);
                    t = "";
                    break;
                case '\'':
                case '"':
                    sign = c;
                    isSt = true;
                default:
                    t += c;
            }
        }
        if(t != "") rt.push_back(t);
        int len2 = rt.size();
        for(int i=1;i<len2;++i) 
            if(rt[0] != "rd" && 
               rt[0] != "df" && 
               isVar(rt[i])  && 
               vars.count(rt[i])
            )  rt[i] = vars[rt[i]];
        return rt;
    }

    int run(vector<string> t) {
        if(t.empty()) return 0;
        string fsl = t[0],adr2,a,c;
        int len;
        switch(getcode(fsl)) {
            case fff::cd:
                if(t.size() == 1) return -1;
                adr2 = adr+'\\'+(eh::is_str(t[1]) ? eh::str_no_quot(t[1]) : t[1]);
                if(cd::exist_floder(adr2)) {
                    if(t[1] == "..") {
                        int len = adr.length(),i;
                        if(len == 2) return 0;
                        for(i=1;adr[len-i] != '\\';++ i) adr = adr.substr(0,len-i);
                        adr = adr.substr(0,len-i);
                    }else if(t[1] == "/") {
                        adr = adr.substr(0,2);
                    }else adr = adr2;
                    chdir(adr.c_str());
                }else return 2;
                break;
            case fff::ls: 
                ls::ls(adr);
                break;
            case fff::echo: 
                eh::echo(t);
                break;
            case fff::cat:
                if(t.size() == 1) return -1;
                return rw::typing(adr+"\\"+t[1]);
                break;
            case fff::cls:
            case fff::clear:
                system("cls");
                break;
            case fff::quit:
            case fff::exit:
                break;
            case fff::wt: 
                len = t.size();
                for(int i=1;i<len;++i) {
                    if(t[i] == "-a") {
                        if(i == len-1) return -1;
                        a = t[i+1];
                        break;
                    }
                }
                if(a == "") return -1;
                return rw::writing(adr+"\\"+a,t,a);
                break;
            case fff::sd:
            case fff::shutdown: 
                c = "shutdown ";
                len = t.size();
                for(int i=1;i<len;++ i) c += t[i]+" ";
                system(c.c_str());
                break;
            case fff::help: 
                if(t.size() < 2) return -1;
                return rw::typing("D:\\fShell\\help\\"+t[1]+".txt");
                break;
            case fff::s_add: 
                if(t.size() < 3) return -1;
                else             cout << cl::add(t[1],t[2]) << endl;
                break;
            case fff::s_sub: 
                if(t.size() < 3) return -1;
                if(cl::compare(t[1],t[2])) cout << "-" << cl::subtra(t[2],t[1]) << endl;
                else                       cout << cl::subtra(t[1],t[2]) << endl;
                break;
            case fff::df: 
                if(t.size() < 3) return -1;
                vars[t[1]] = t[2];
                break;
            case fff::rd: 
                if(t.size() < 2) return -1;
                else if(!vars.count(t[1])) return 3;
                cout << vars[t[1]] << endl;
                break;
            case fff::cp: 
                if(t.size() < 3) return -1;
                rw::cp(t[1],t[2]);
                break;
            case fff::s_mul: 
                if(t.size() < 3) return -1;
                cout << cl::mul(t[1],t[2]) << endl;
                break;
            default:
                if(fsl.length() == 2 && fsl[1] == ':') adr = fsl;
                else return 1;
                break;
        }
        if(fsl != "cls" && fsl != "clear") cout << "\n";
        return 0;
    }
} 

#endif