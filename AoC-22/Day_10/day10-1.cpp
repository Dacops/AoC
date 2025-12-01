#include <iostream>
#include <cstring>

using namespace std;

int cycle = 0, registr = 1, sum = 0;


void addCycles(int num) {
    for(int i=0; i<num; i++) {
        cycle++;
        if((cycle+20)%40==0) {
            sum += cycle * registr;
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
    cout << sum << endl;

    return 0;
}