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

// J as weakest card, A as strongest
unordered_map<char, int> all_cards = {
    {'J', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}, {'9', 8}, {'T', 9}, {'Q', 10}, {'K', 11}, {'A', 12}
};

struct hand {
    string cards;
    int value;

    // comparator to sort hands
    bool operator<(const hand& other) {

        vector<int> a_type{}, b_type{};
        vector<int> a_map{}, b_map{};
        int a_wild = 0, b_wild = 0;
        
        // compare types
        for (const auto& c : all_cards) {
            
            // don't count J as card
            if (c.first == 'J') continue;

            int a = 0, b = 0;
            a_wild = 0, b_wild = 0; // avoid multiple count
            for (const auto& c1 : cards) { a_map.push_back(all_cards[c1]); if (c1==c.first) a++; if (c1=='J') a_wild++; }
            for (const auto& c2 : other.cards) { b_map.push_back(all_cards[c2]); if (c2==c.first) b++; if (c2=='J') b_wild++; }

            if (a) { a_type.push_back(a); a = 0; }
            if (b) { b_type.push_back(b); b = 0; }
        }

        sort(a_type.begin(), a_type.end(), greater<int>());
        sort(b_type.begin(), b_type.end(), greater<int>());

        // Avoid 5 'J's, a_type, b_type won't be initialized
        if (a_type.size()) a_type[0] += a_wild; else { a_type.push_back(a_wild); }
        if (b_type.size()) b_type[0] += b_wild; else { b_type.push_back(b_wild); }

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