#include <iostream>
#include <vector>

using namespace std;

struct Monkey {
    vector<int> _startIt;
    int _plus = 0;              // default = 0
    int _times = 1;             // default = 1, =0 -> squared
    int _div;
    int _otc1;
    int _otc2;
    int inspected = 0;
};

vector<Monkey> _monkeys;

void parseInput() {

    int counter = 0;            // 7 line loops
    int monkey = -1;
    string line;
    while(getline(cin, line)) {
        if(!(counter%7)) {      // new monkey
            monkey++;
            Monkey curr;
            _monkeys.resize((int)_monkeys.size()+1);
            _monkeys[monkey]=curr;
        }
        if(!((counter-1)%7)) {  // starting items
            line = line.substr(line.find(": ")+1,line.size()-1);
            int curr = 0;
            int value = 0;

            for(int i=0; i<(int)line.length(); i++) {
                if(line[i]>='0' && line[i]<='9') {
                    value = value*10 + (line[i]-'0');
                }
                else if(line[i]==',') {
                    _monkeys[monkey]._startIt.resize(curr+1);
                    _monkeys[monkey]._startIt[curr] = value;
                    value = 0;
                    curr++;
                }
            }
            // get last value
            _monkeys[monkey]._startIt.resize(curr+1);
            _monkeys[monkey]._startIt[curr] = value;
        }
        if(!((counter-2)%7)) { // operation
            line = line.substr(line.find('='),line.size()-1);
            // line -> = old <op>
            if(line[6]=='*') {
                int value = 0;
                for(int i=0; i<(int)line.length(); i++) {
                    if (line[i] >= '0' && line[i] <= '9') {
                        value = value * 10 + (line[i] - '0');
                    }
                }
                _monkeys[monkey]._times = value;
            }
            else if (line[6]=='+') {
                int value = 0;
                for(int i=0; i<(int)line.length(); i++) {
                    if (line[i] >= '0' && line[i] <= '9') {
                        value = value * 10 + (line[i] - '0');
                    }
                }
                _monkeys[monkey]._plus = value;
            }
        }
        if(!((counter-3)%7)) {  // test
            int value = 0;
            for(int i=0; i<(int)line.length(); i++) {
                if (line[i] >= '0' && line[i] <= '9') {
                    value = value * 10 + (line[i] - '0');
                }
            }
            _monkeys[monkey]._div = value;
        }
        if(!((counter-4)%7)) {  // test
            int value = 0;
            for(int i=0; i<(int)line.length(); i++) {
                if (line[i] >= '0' && line[i] <= '9') {
                    value = value * 10 + (line[i] - '0');
                }
            }
            _monkeys[monkey]._otc1 = value;
        }
        if(!((counter-5)%7)) {  // test
            int value = 0;
            for(int i=0; i<(int)line.length(); i++) {
                if (line[i] >= '0' && line[i] <= '9') {
                    value = value * 10 + (line[i] - '0');
                }
            }
            _monkeys[monkey]._otc2 = value;
        }
        counter++;
    }
}

void throwMonkey(int otc, int newValue) {
    Monkey *add = &_monkeys[otc];

    // add to receiver monkey
    int size = add->_startIt.size();
    add->_startIt.resize(size+1);
    add->_startIt[size] = newValue;
}


void monkeyInspector() {
    for(int i=0; i<(int)_monkeys.size(); i++) {
        for(int j=0; j<(int)_monkeys[i]._startIt.size(); j++) {
            int newValue;
            int value = _monkeys[i]._startIt[j];
            int times = _monkeys[i]._times;
            int plus = _monkeys[i]._plus;
            int div = _monkeys[i]._div;
            int otc1 = _monkeys[i]._otc1;
            int otc2 = _monkeys[i]._otc2;
            _monkeys[i].inspected++;
            (times) ? newValue = (value+plus)*times : newValue = (value+plus)*value;
            newValue /= 3;      // monkey bored
            (newValue%div) ? throwMonkey(otc2, newValue) : throwMonkey(otc1, newValue);
        }
        _monkeys[i]._startIt.resize(0);
    }
}

int inspectMonkeys() {
    int max1, max2;
    for(int i=0; i<(int)_monkeys.size(); i++) {
        if(_monkeys[i].inspected>max1) { max2=max1; max1=_monkeys[i].inspected; }
        else if(_monkeys[i].inspected>max2) max2 = _monkeys[i].inspected;
    }
    return max1*max2;
}

int main() {
    parseInput();
    for(int i=0; i<20; i++) monkeyInspector();
    cout << inspectMonkeys() << endl;

    return 0;
}