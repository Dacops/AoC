#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


vector<vector<char>> _crates;
int columns = 0;


void evaluateLine(string line) {

    for(int i=0; i<columns; i++) {

        if( !((int)line[4*i]==32) ) {           // crate in this position;
            int size = (int)_crates[i].size();
            _crates[i].resize(size+1);          // space for new char;
            _crates[i][size]=line[4*i+1];       // [letter];
        }
    }
}

void moveCrate(int from, int to, int num) {

    vector<char> crates;
    crates.resize(num);
    for(int i=0; i<num; i++) { crates[i]=_crates[from][i]; }

    // remove crate from "from" stack.
    int newSize = (int)_crates[from].size()-num;
    for(int i=0; i<newSize; i++) {
        _crates[from][i] = _crates[from][i+num];
    }
    _crates[from].resize(newSize);

    // add crate to "to" stack.
    newSize = (int)_crates[to].size()+num;
    _crates[to].resize(newSize);
    for(int i=newSize-1; i>num-1; i--) {
        _crates[to][i] = _crates[to][i-num];
    }

    for(int i=0; i<num; i++) { _crates[to][i]=crates[i]; }
}

void moveCrates() {

    string line;

    getline(cin, line); // empty line;
    while(getline(cin, line)) {

        // Bootleg text splitter:
        // int numCrates, from, to;
        vector<int> constraints = {0,0,0};
        int current = 0, flag = 0;
        for (int i=0; i<(int)line.length(); i++) {
            if( int(line[i])>='0' && int(line[i])<='9' ) {
                constraints[current] = constraints[current]*10 + (int(line[i])-48);
                flag++;
            }
            else if (flag) { current++; flag=0; }
        }

        // "numCrates" crates go from "from" to "to";
        moveCrate(constraints[1]-1, constraints[2]-1, constraints[0]);
    }
}

void readInput() {

    string line;

    // 1st line, .length()/4 = number of columns.
    getline(cin, line);
    columns = line.length()/4;
    _crates.resize(columns);
    evaluateLine(line);

    while(getline(cin, line)) {

        // starts 2nd part of input;
        if(line[1]=='1') break;

        // crates
        evaluateLine(line);
    }
    moveCrates();
}

int main() {
    readInput();
    for(int i=0; i<(int)_crates.size(); i++) { cout << _crates[i][0]; }
    cout << endl;
    return 0;
}