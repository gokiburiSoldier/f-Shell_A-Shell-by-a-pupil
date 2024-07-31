#include "head/cli.h"
using namespace std;

string s;
vector<string> slt;

int main() {
    while(s != "quit" && s != "exit") {
        s = run::readline();
        slt = run::spliter(s);
        switch(run::run(slt)) {
            case 1:
                if(slt[0] == "help") 
                    if(slt.size() >= 2) rw::typing("D:\\fShell\\help\\"+slt[1]+".txt");
                else
                cerr << "f-Shell: Command Not Found\n";
                break;
            case -1:
                cerr << "f-Shell: Too Lower Args or Lost Core Arg\n";
                break;
            case 2:
                cerr << "f-Shell: File or Floder Not Found At [" << run::adr << "]\n";
                break;
        }
    }
    return 0;
}