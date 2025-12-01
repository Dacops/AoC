#include <iostream>
#include <vector>
#include <string>

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


struct NumberInfo {
    pair<int, int> location;
    int length;
    int value;
};

int evaluateInput() {

    string line;
    int number = 0, length = 0;

    int x = 0, y = 0;
    vector<NumberInfo> numberLocations;
    vector<pair<int, int>> gearLocations;

    // Save number / symbol locations
    while (getline(cin, line)) {

        x = 0;
        for (const char& c : line) {
            if (c>='0' && c<='9') {
                length++;
                number = number*10 + (c-'0');
            } else {
                // input in CRLF instead of LF, getline doesn't remove CR, still can check EOL

                // add gear
                if (c == '*') gearLocations.push_back(make_pair(x, y));

                // number found, save location
                if (number) numberLocations.push_back({make_pair(x-length, y), length, number});
                number = 0, length = 0;
            }
            x++;
        }
        y++;
    }

    // Check if gear is near numbers
    int answer = 0, nearNumsCnt = 0;
    vector<int> nearNums;
    for (auto& coords : gearLocations) {
        for (auto& number : numberLocations) {
            
            if ( (coords.first >= number.location.first-1 && coords.first <= number.location.first+number.length) &&
                abs(number.location.second-coords.second) <= 1) {
                
                nearNums.push_back(number.value);
                nearNumsCnt++;
            }
        }
        if (nearNumsCnt == 2) answer += nearNums[0] * nearNums[1];
        nearNumsCnt = 0;
        nearNums.clear();
    }

    return answer;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}