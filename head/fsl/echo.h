#ifndef _FSL_ECHO_H
#define _FSL_ECHO_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

namespace eh {
    string str_no_quot(string s) {
        string rt;
        for(int i=0;s[i] != '\0';++ i) {
            if(i == '\'' || i == '"') continue;
            rt += i;
        }
        return rt;
    }
    bool is_str(string s) {
        char h = s[0],t = s[s.length()-1];
        return h == '"' && t == '"' || h == '\'' && t == '\'';
    }
    void echo(vector<string> v) {
        int len = v.size();
        for(int i=0;i<len;++ i) {
            if(v[i] == "echo") continue;
            if(is_str(v[i])) cout << str_no_quot(v[i]) << endl;
            else             cout << v[i] << endl;
        }
        return;
    }
}


#endif