#include <iostream>
#include <set>
#include <string>
#include <vector>

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


struct ScartchCard {
    int got;
    int value;
};

int evaluateInput() {

    string line;
    int answer = 0;
    vector<ScartchCard> cards;

    while (getline(cin, line)) {

        
        set<int> winNums = {};
        int number = 0, mode = 0, wins = 0;
        for (const char& c : line) {
            if (c>='0' && c<='9') {
                number = number*10 + (c-'0');
            } else if (c == '|') {
                mode = 1;               // switch to check mode
            } else if (c == ':') {
                number = 0;             // avoid counting card number
            } else if (c == ' '  || c == '\r') {    // CRLF to catch '\r (getline() strips '\n)
                if (!mode && number) {
                    // add value to winNums set
                    winNums.insert(number);
                } else if (number) {
                    // check if number is in winNums set
                    if (winNums.find(number) != winNums.end()) {
                        wins++;
                    }
                }
                number = 0;
            }
        }

        cards.push_back({1, wins});
    }

    // post-processing

    // get all cards & count scratchcards
    for (int i=0; i<(int)cards.size(); i++) {
        for (int j=0; j<cards[i].value; j++) {
            cards[i+j+1].got += cards[i].got;
        }
        answer += cards[i].got;
    }

    return answer;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}