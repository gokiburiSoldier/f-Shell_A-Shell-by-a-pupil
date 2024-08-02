/*
 * Read And Write
 */
#ifndef _FSL_RW
#define _FSL_RW

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

namespace rw {
    ofstream fout;
    ifstream fin;
    int typing(string adr) {
        fin.open(adr);
        if(fin.fail()) return 2;
        string line;
        while(getline(fin,line)) cout << line << endl;
        return 0;
    }
    int writing(string adr,vector<string> cnt,string re) {
        fout.open(adr);
        if(fout.fail()) return 2;
        int len = cnt.size();
        for(int i=0;i<len;++ i) {
            if(cnt[i][0] == '-' || cnt[i] == re || cnt[i] == "wt") continue;
            fout << cnt[i] << endl;
        }
        return 0;
    }
    int cp(string sour,string targ) {
        fin.open(sour,ios::binary);
        if(fin.fail()) return 2;
        fout.open(targ,ios::binary);
        if(fout.fail()) return 2;
        fout << fin.rdbuf();
        return 0;
    }
}


#endif