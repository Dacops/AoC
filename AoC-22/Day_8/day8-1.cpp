#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


vector<string> _trees;
vector<int> _tallestTree;
vector<vector<bool>> _visible;


void parseInput() {

    string line;

    while(getline(cin, line)) {

        // remove EOF character
        line = line.substr(0, line.find('\r'));
        int size = (int)_trees.size();

        _trees.resize(size+1);
        _visible.resize(size+1);

        _visible[size].resize(line.length());
        _trees[size] = line;
    }
}

void createMatrix() {

    // resize with number of columns
    _tallestTree.resize(_trees[0].length()-1);

    // Start from top
    for(int i=0; i<(int)_trees.size(); i++) {           // Y
        for(int j=0; j<(int)_trees[i].length(); j++) {  // X
            // first line is always visible
            if(i==0) {
                _visible[i][j] = true;
                _tallestTree[j] = _trees[i][j];
            }
            // line is taller than previous
            else if(_trees[i][j]>_tallestTree[j]) {
                _visible[i][j] = true;
                _tallestTree[j] = _trees[i][j];
            }
        }
    }

    // Start from bottom
    for(int i=(int)_trees.size()-1; i>=0; i--) {        // Y
        for(int j=0; j<(int)_trees[i].length(); j++) {  // X
            // first line is always visible
            if(i==(int)_trees.size()-1) {
                _visible[i][j] = true;
                _tallestTree[j] = _trees[i][j];
            }
            // line is taller than previous
            else if(_trees[i][j]>_tallestTree[j]) {
                _visible[i][j] = true;
                _tallestTree[j] = _trees[i][j];
            }
        }
    }

    // resize with number of rows
    _tallestTree.resize(_trees.size()-1);

    // Start from left
    for(int i=0; i<(int)_trees.size(); i++) {           // Y
        for(int j=0; j<(int)_trees[i].length(); j++) {  // X
            // first line is always visible
            if(j==0) {
                _visible[i][j] = true;
                _tallestTree[i] = _trees[i][j];
            }
            // line is taller than previous
            else if(_trees[i][j]>_tallestTree[i]) {
                _visible[i][j] = true;
                _tallestTree[i] = _trees[i][j];
            }
        }
    }

    // Start from right
    for(int i=0; i<(int)_trees.size(); i++) {               // Y
        for(int j=(int)_trees[i].length()-1; j>=0; j--) {   // X
            // first line is always visible
            if(j==(int)_trees[i].length()-1) {
                _visible[i][j] = true;
                _tallestTree[i] = _trees[i][j];
            }
            // line is taller than previous
            else if(_trees[i][j]>_tallestTree[i]) {
                _visible[i][j] = true;
                _tallestTree[i] = _trees[i][j];
            }
        }
    }
}

int evaluateMatrix() {

    int visible = 0;
    for(int i=0; i<(int)_visible.size(); i++) {
        for (int j=0; j<(int) _visible[i].size(); j++) {
            if(_visible[i][j]) visible++;
        }
    }
    return visible;
}


int main() {
    parseInput();
    createMatrix();
    cout << evaluateMatrix() << endl;
    return 0;
}