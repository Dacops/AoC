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

void moveCrate(int from, int to) {

    char crate = _crates[from][0];

    // remove crate from "from" stack.
    int newSize = (int)_crates[from].size()-1;
    for(int i=0; i<newSize; i++) {
        _crates[from][i] = _crates[from][i+1];
    }
    _crates[from].resize(newSize);

    // add crate to "to" stack.
    newSize = (int)_crates[to].size()+1;
    _crates[to].resize(newSize);
    for(int i=newSize-1; i>0; i--) {
        _crates[to][i] = _crates[to][i-1];
    }
    _crates[to][0] = crate;
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
        for(int i=0; i<constraints[0]; i++) {
            moveCrate(constraints[1]-1, constraints[2]-1);
        }
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