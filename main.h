#include "head/cli.h"
using namespace std;

string s;
vector<string> slt;

void cmd(void) {
    if(SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrl_c,1))
    while(s != "quit" && s != "exit") {
            s = run::readline();
            slt = run::spliter(s);
            switch(run::run(slt)) {
                case 1:
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
}

vector<string> rl(string a) {
    ifstream f(a);
    vector<string> rt;
    string s;
    while(getline(f,s)) rt.push_back(s);
    return rt;
}