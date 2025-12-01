#include <iostream>
#include <vector>

using namespace std;


vector<string> _trees;


void parseInput() {

    string line;

    while(getline(cin, line)) {

        // remove EOF character
        line = line.substr(0, line.find('\r'));
        int size = (int)_trees.size();

        _trees.resize(size+1);
        _trees[size] = line;
    }
}

int getScore(int i, int j) {    // row i, column j

    int score = 1;              // base score
    int multiplier = 0;

    // check trees above
    for(int a=i-1; a>=0; a--) {
        multiplier++;
        if(_trees[a][j]>=_trees[i][j]) break;
    }
    score*=multiplier;
    multiplier=0;

    // check trees below
    for(int a=i+1; a<(int)_trees.size(); a++) {
        multiplier++;
        if(_trees[a][j]>=_trees[i][j]) break;
    }
    score*=multiplier;
    multiplier=0;

    // check trees to the left
    for(int a=j-1; a>=0; a--) {
        multiplier++;
        if(_trees[i][a]>=_trees[i][j]) break;
    }
    score*=multiplier;
    multiplier=0;

    // check trees to the left
    for(int a=j+1; a<(int)_trees[i].length(); a++) {
        multiplier++;
        if(_trees[i][a]>=_trees[i][j]) break;
    }
    score*=multiplier;

    return score;
}


int getHighestScore() {

    int maxScore = 0;

    for(int i=0; i<(int)_trees.size(); i++) {
        for(int j=0; j<(int)_trees[i].length(); j++) {
            if(getScore(i,j)>maxScore) { maxScore=getScore(i,j); }
        }
    }
    return maxScore;
}

int main() {
    parseInput();
    cout << getHighestScore() << endl;
    return 0;
}