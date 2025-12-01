#include <iostream>
#include <cstring>

using namespace std;

int cycle = 0, registr = 1;


void addCycles(int num) {
    for(int i=0; i<num; i++) {
        (cycle%40>=registr-1 && cycle%40<=registr+1) ? cout<<"#" : cout<<".";
        cycle++;
        if((cycle%40)==0) {
            cout << endl;
        }
    }
}


void parseInput() {

    string command;
    int value;

    while(cin>>command) {
        if(!strcmp(command.c_str(),"addx")) {

            // get addx value
            cin.ignore(), cin>>value;

            addCycles(2);
            registr += value;
        }
        if(!strcmp(command.c_str(),"noop")) {
            addCycles(1);
        }
    }
}


int main() {
    parseInput();
    cout << endl;
    return 0;
}