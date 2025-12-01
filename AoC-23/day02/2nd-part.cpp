#include <iostream>
#include <vector>
#include <string>
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


unordered_map<string, int> colours = { {"blue", 14}, {"red", 12}, {"green", 13} };

int evaluateGame(const string& game) {

    unordered_map<string, int> maxColour = { {"blue", 0}, {"red", 0}, {"green", 0} };

    for (const auto& colour : colours) {
        int pos = game.find(colour.first);
        while (pos != (int)string::npos) {
            
            int number = 0;
            if (game[pos-3] >= '0' && game[pos-3] <= '9') {
                number = (game[pos-3] - '0')*10;
            }
            number += game[pos-2] - '0';
            
            if (number > maxColour[colour.first]) {
                maxColour[colour.first] = number;
            }

            pos = game.find(colour.first, pos+1);
        }
    }

    return maxColour["blue"] * maxColour["red"] * maxColour["green"];
}

int evaluateInput() {

    string line;
    int answer = 0, game = 0;

    while (getline(cin, line)) {

        game++;
        answer += evaluateGame(line);    
    }

    return answer;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}