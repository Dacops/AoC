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


uint64_t evaluateInput() {

/// [Parser]
    string line;
    vector<string> input;               // hold all lines
    vector<pair<int, int>> coords;      // hold all '#' coords

    int y = 0;
    while (getline(cin, line)) {
        
        for (int x=0; x<(int)line.size(); x++) {
            if (line[x] == '#') coords.push_back({y, x});
        }

        y++;
        input.push_back(line);
    }
/// [Parser]

/// [Solver]

    bool mt_col = true, mt_row = true;

    // check for empty rows
    for (int i=0; i<(int)input.size(); i++) {
        for (const char& c : input[i]) { if (c=='#') mt_row=false; }
        if (mt_row) { for (char& c : input[i]) c = '+'; }
        mt_row = true;
    }

    // check for empty columns
    for (int i=0; i<(int)input.size(); i++) {
        for (const string& s : input) { if (s[i]=='#') mt_col=false; }
        if (mt_col) { for (string& s : input) s[i] = '+';}
        mt_col = true;
    }

    
    // get distances
    uint64_t distance = 0;

    // move to place step by step; check if '.'(1) or '+'(1e6)
    for (int i=0; i<(int)coords.size(); i++) {
        for (int j=i+1; j<(int)coords.size(); j++) {

            int begin = 0, end = 0;

            // get vertical distance
            (coords[i].first > coords[j].first) ? (begin=coords[j].first, end=coords[i].first) : (begin=coords[i].first, end=coords[j].first);
            for (int y=begin; y<end; y++) {
                if (input[y][coords[i].second] == '+') distance += 1e6;
                else distance++;                           
            }

            // get horizontal distance
            (coords[i].second > coords[j].second) ? (begin=coords[j].second, end=coords[i].second) : (begin=coords[i].second, end=coords[j].second);
            for (int x=begin; x<end; x++) {    
                if (input[coords[i].first][x] == '+') distance += 1e6;
                else distance++;
            }
        }
    }

    return distance;

/// [Solver]
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}