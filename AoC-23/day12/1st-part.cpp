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


struct row {
    string springs;
    vector<int> springs_num;
};

int fits(row r, int offset) {

    if (r.springs_num.size() == 0) return 0;

    cout << r.springs << " > " << r.springs_num[0] << " w/ " << offset << endl;

    int to_insert = r.springs_num[0];
    for (char& c : r.springs) {
        cout << c << " & " << to_insert << endl;
        if (c=='.' && to_insert) return 0;
        if (offset && c=='?') { offset--; continue; }
        if (c=='#' || c=='?') { c='.'; to_insert--; }
        if (!to_insert) break;
    }
    cout << ">>>>>> " << r.springs << endl;

    if (to_insert) return 0;
    if (r.springs_num.size() == 1) return 1;
    r.springs_num.erase(r.springs_num.begin());

    int answer = 0;
    for (int i=0; i<r.springs_num.size(); i++) {
        answer += fits(r, i);
    }

    return answer;
}



int evaluateInput() {

/// [Parser]
    string line;
    vector<row> rows;

    while (getline(cin, line)) {
        
        row temp_row;
        string temp_line;
        vector<int> temp_snums;

        int number = 0;
        for (const char& c : line) {

            if (c=='.' || c=='#' || c=='?') {
                temp_line += c;
            } else if (c>='0' && c<='9') {
                number += number*10 + (c - '0');
            } else if (c==',' || c=='\r'){
                temp_snums.push_back(number);
                number = 0;
            }
        }
        temp_row.springs = temp_line;
        temp_row.springs_num = temp_snums;
        rows.push_back(temp_row);
    }
/// [Parser]

/// [Solver]

    int answer = 0;

    for (const auto& r : rows) {
        for (int i=0; i<(int)r.springs.size(); i++) {
            answer += fits(r, i);
        }
    }

    return answer;

/// [Solver]
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}