#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// initialization lambda funtion, 
// do nothing -> call for optimizations
auto init = []()
{ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();


int evaluateInput() {

/// [Parser]
    string line;
    vector<string> input;               // hold all lines

    while (getline(cin, line)) {
        input.push_back(line);
    }
/// [Parser]

/// [Solver]

    bool mt_col = true, mt_row = true;
    vector<int> mt_cols, mt_rows;

    // check for empty rows
    for (int i=0; i<(int)input.size(); i++) {
        for (const char& c : input[i]) { if (c=='#') mt_row=false; }
        if (mt_row) mt_rows.push_back(i);   // no '#' found, empty line;
        mt_row = true;
    }

    // check for empty columns
    for (int i=0; i<(int)input.size(); i++) {
        for (const string& s : input) { if (s[i]=='#') mt_col=false; }
        if (mt_col) mt_cols.push_back(i);   // no '#' found, empty column;
        mt_col = true;
    }

    
    // resize original matrix

    // add rows
    int prev_ins_rows = 0;  // keep track of already inserted rows for offset
    for (const auto& c : mt_rows) { input.insert(input.begin()+c+prev_ins_rows, string(input[0].size(), '.')); prev_ins_rows++; }

    // add columns
    int prev_ins_cols = 0;  // keep track of already inserted columns for offset
    for (const auto& c : mt_cols) {
        for (string& s : input) { s.insert(s.begin()+c+prev_ins_cols, 1, '.'); }
        prev_ins_cols++;
    }


    // read resized matrix for '#' coords
    vector<pair<int, int>> coords;

    for (int i=0; i<(int)input.size(); i++) {
        for (int j=0; j<(int)input[i].size(); j++) {
            if (input[i][j] == '#') coords.push_back({i, j});
        }
    }


    // get distances
    int distance = 0;

    // only do half matrix avoid doing [x, y] and [y, x]
    for (int i=0; i<(int)coords.size(); i++) {
        for (int j=i+1; j<(int)coords.size(); j++) {
            distance += abs(coords[i].first-coords[j].first) + abs(coords[i].second-coords[j].second);
        }
    }

    return distance;

/// [Solver]
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}