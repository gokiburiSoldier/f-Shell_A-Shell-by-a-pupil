#ifndef _FSL_CALC
#define _FSL_CALC

#include <algorithm>
#include <string>
using namespace std;

namespace cl {

string add(string a,string b) {
    int lena = a.length(),lenb = b.length();
    if(lena < lenb) {
        swap(lena,lenb);
        swap(a,b);
    }
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    while(lena-lenb) {
        b += "0";
        ++ lenb;
    }
    for(int i=0;i<lena;++i) {
        a[i] += b[i]-'0';
        if(a[i] > '9') {
            if(i != lena-1) a[i+1] += 1;
            else            a += "1";
            a[i] -= 10;
        }
    }
    reverse(a.begin(),a.end());
    return a;
}

string subtra(string a,string b) {
    int lena=a.length(),lenb=b.length();
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    while(lena-lenb) {
        b += "0";
        ++ lenb;
    }
    for(int i=0;i<lena;++ i) {
        a[i] -= b[i]-'0';
        if(a[i] < '0') {
            a[i] += 10;
            a[i+1] -= 1;
        }
    }
    reverse(a.begin(),a.end());
    while(a[0] == '0' && a[1] != '\0') a = a.substr(1,lena-1);
    return a;
}

bool compare(string a,string b) {
    int lena = a.length(),lenb = b.length();
    if(lena != lenb) return lena < lenb;
    for(int i=0;i<lena;++i) if(a[i] != b[i]) return a[i] < b[i];
    return false;
}

}
#endif