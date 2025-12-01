#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <string>
#include <climits>

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
    unordered_map<string, int> dict = {
        {"one", 1}, {"two", 2}, {"three", 3}, 
        {"four", 4}, {"five", 5}, {"six", 6}, 
        {"seven", 7}, {"eight", 8}, {"nine", 9}
    };

    while (getline(cin, line)) {

        // get min/max pos num to compare with min/max pos word
        int index = 0;
        pair<int, int> minNum = {INT_MAX, 0}, maxNum = {INT_MIN, 0};
        for (const char& c : line) {
            if (c >= '0' && c <= '9') {
                if (index < minNum.first) {
                    minNum.first = index;
                    minNum.second = c-'0';
                }
                if (index > maxNum.first) {
                    maxNum.first = index;
                    maxNum.second = c-'0';
                }
            }
            index++;
        }

        // get min/max pos word to compare with min/max pos num
        pair<int, int> minWord = {INT_MAX, 0}, maxWord = {INT_MIN, 0};
        for (const auto& entry : dict) {
            int pos = line.find(entry.first);
            while (pos != (int)string::npos) {
                if (pos < minWord.first) {
                    minWord.first = pos;
                    minWord.second = entry.second;
                }
                if (pos > maxWord.first) {
                    maxWord.first = pos;
                    maxWord.second = entry.second;
                }
                pos = line.find(entry.first, pos+1);
            }
        }
        
        int number = 0;
        (minNum.first < minWord.first) ? number = minNum.second*10 : number = minWord.second*10;
        (maxNum.first > maxWord.first) ? number += maxNum.second : number += maxWord.second;;

        answer += number;
    }

    return answer;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}