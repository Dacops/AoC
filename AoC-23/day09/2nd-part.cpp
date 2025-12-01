#include <iostream>
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


int evaluateInput() {

/// [Parser]
    string line;
    vector<vector<int>> input;  // hold all lines

    while (getline(cin, line)) {

        int number = 0;         // hold current number
        bool negative = false;  // flag for negative numbers
        vector<int> temp;       // hold current line
        for (const char& c : line) {

            // parse negative numbers
            if (c=='-') negative = true;
            if (c>='0' && c<='9') {
                number = number*10 + (c-'0');
            } else if (c==' ' || c=='\r') {
                if (negative) { number *= -1; negative = false;}
                temp.push_back(number);
                number = 0;
            }
        }
        input.push_back(temp);
    }
/// [Parser]

/// [Solver]

    int answer = 0;
    for (int i=0; i<(int)input.size(); i++) {

        int lineSize = (int)input[i].size();

        for (int j=1; j<lineSize; j++) {

            int done = 1;
            for (int k=lineSize-1; k>=j; k--) {

                // compact the array; 2nd line takes lineSize-1 elements of original array;
                // 3rd line takes lineSize-2 elements of original array; etc. Values needed
                // for recursion are kept on the not used space of previous line
                input[i][k] = input[i][k] - input[i][k-1];
                if (input[i][k] != 0) done = 0;
            }

            // current line recursion is done, get next element
            if (done) {
                for (int k=j; k>=1; k--) {
                    input[i][k-1] -= input[i][k];
                }
                answer += input[i][0];
                break;  // skip to next line
            }
        }
    }

    return answer;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}