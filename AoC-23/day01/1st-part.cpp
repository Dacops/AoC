#include <iostream>
#include <vector>
#include <numeric>

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

    string line;
    int answer = 0;

    while (getline(cin, line)) {

        int number = 0, first = 0;
        for (const char& c : line) {
            if (c >= '0' && c <= '9') {
                if (!first) first = (c-'0');
                number = first*10 + (c-'0');
            }
        }
        answer += number;
    }

    return answer;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}