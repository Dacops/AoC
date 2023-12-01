#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


int evaluateInput() {

    string line;
    int answer = 0;

    while (getline(cin, line)) {

        int number = 0, first = 0;
        for (const char& c : line) {
            if (c >= 49 && c <= 57) {
                if (!first) first = (c-48);
                number = first*10 + (c-48);
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