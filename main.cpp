#include "main.h"

int main(int argc,char* argv[]) {
    if(argc < 2) cmd();
    else {
        vector<string> doc = rl(argv[1]);
        for(string ln : doc) 
            swt(run::run(run::spliter(ln)));
        system("pause");
    }
    return 0;
}