#include <iostream>
#include <vector>

using namespace std;


vector<int> _calories;                                      // index = elf; value = num of calories;
int elf = 0;

void readInput() {

    string line;
    _calories.resize(sizeof(int));

    while (getline(cin, line)) {

        if (int(line[0])==13 || int(line[0])==10) {         // CR, ASCII code: 13 or LF, ASCII code: 10;
            elf++;
            _calories.resize((elf+1)*sizeof(int));
        }
        else { _calories[elf]+=stoi(line); }
    }
}

int evaluateInput() {

    int max = 0;

    for (int i=0; i<elf; i++) {
        if (max < _calories[i]) { max = _calories[i]; }
    }
    return max;
}


int main() {
    readInput();
    cout << evaluateInput() << endl;

    return 0;
}