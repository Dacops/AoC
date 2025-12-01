#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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


struct race {
    uint64_t time;
    uint64_t record;
};

int evaluateInput() {

    string line;
    int lineNum = 0;
    vector<race> data;

    while (getline(cin, line)) {

        uint64_t number = 0;
        for (const char& c : line) {
            
            if (c>='0' && c<='9') {
                number = number*10 + (c-'0');
            } else if (c=='\r' && number) {

                // get times
                if (!lineNum) data.push_back({number, 0});

                else data[0].record = number;

                number = 0;
            }
        }
        lineNum++;
    }

    // given n time, boat can travel for p * (n-p) distance, being p time pressed; n<=p
    // function is a symetric parabola, by finding first number above record we can get
    // total ways to beat the record as n - 2*p 

    int answer = 1;
    for (const auto& pair : data) {

        // only need to iterate until middle of parabola, if not found there's no possible
        // way to beat the record
        int record = 0;
        for (int p=0; p<(int)pair.time/2; p++) {
            
            record = p;
            if (p * (pair.time-p) > pair.record) break;
            record = 0;
        }

        answer *= (pair.time - 2*record + 1);
    }

    return answer;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}