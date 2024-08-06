#include "main.h"

int main(int argc,char* argv[]) {
    chdir(run::adr.c_str());
    if(isAdministor()) SetConsoleTitle(("Administor: f-Shell"));
    else               SetConsoleTitle(("f-Shell"));
    if(argc < 2) cmd();
    else {
        vector<string> doc = rl(argv[1]);
        for(string ln : doc) 
            swt(run::run(run::spliter(ln)));
        system("pause");
    }
    return 0;
}