#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

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


unordered_map<char, int> all_cards = {
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4}, {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12}
};

struct hand {
    string cards;
    int value;

    // comparator to sort hands
    bool operator<(const hand& other) {

        vector<int> a_type{}, b_type{};
        vector<int> a_map{}, b_map{};
        
        // compare types
        for (const auto& c : all_cards) {
            
            int a = 0, b = 0;
            for (const auto& c1 : cards) { a_map.push_back(all_cards[c1]); if (c1==c.first) a++; }
            for (const auto& c2 : other.cards) { b_map.push_back(all_cards[c2]); if (c2==c.first) b++; }

            if (a) { a_type.push_back(a); a = 0; }
            if (b) { b_type.push_back(b); b = 0; }
        }

        sort(a_type.begin(), a_type.end(), greater<int>());
        sort(b_type.begin(), b_type.end(), greater<int>());

        // type comparison is not enough, compare values
        if (a_type == b_type) return a_map < b_map;

        // type comparison is enough
        return a_type < b_type;
    }
};

int evaluateInput() {

    string line;
    vector<hand> hands;

    while (getline(cin, line)) {

        string temp{};
        int number = 0, argcount = 0;
        for (const char& c : line) {
            
            if (!argcount && c!=' ') temp += c;
            if (c>='0' && c<='9' && argcount) {
                number = number*10 + (c-'0');
            } else if (c==' ' || c=='\r') {
                
                // save hand
                if (argcount) hands.push_back({temp, number});
                argcount++;
            }
        }
    }

    // sort hands
    sort(hands.begin(), hands.end());

    int answer = 0;
    for (auto i=0; i<(int)hands.size(); i++) {
        answer += hands[i].value * (i+1);
    }

    return answer;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}