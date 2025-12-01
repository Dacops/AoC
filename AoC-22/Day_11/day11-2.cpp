#include <iostream>
#include <vector>

using namespace std;

struct Monkey {
    vector<long> _startIt;
    long _plus = 0;              // default = 0
    long _times = 1;             // default = 1, =0 -> squared
    long _div;
    long _otc1;
    long _otc2;
    long inspected = 0;
};

vector<Monkey> _monkeys;
long divs = 1;

void parseInput() {

    long counter = 0;            // 7 line loops
    long monkey = -1;
    string line;
    while(getline(cin, line)) {
        if(!(counter%7)) {      // new monkey
            monkey++;
            Monkey curr;
            _monkeys.resize((long)_monkeys.size()+1);
            _monkeys[monkey]=curr;
        }
        if(!((counter-1)%7)) {  // starting items
            line = line.substr(line.find(": ")+1,line.size()-1);
            long curr = 0;
            long value = 0;

            for(long i=0; i<(long)line.length(); i++) {
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
                long value = 0;
                for(long i=0; i<(long)line.length(); i++) {
                    if (line[i] >= '0' && line[i] <= '9') {
                        value = value * 10 + (line[i] - '0');
                    }
                }
                _monkeys[monkey]._times = value;
            }
            else if (line[6]=='+') {
                long value = 0;
                for(long i=0; i<(long)line.length(); i++) {
                    if (line[i] >= '0' && line[i] <= '9') {
                        value = value * 10 + (line[i] - '0');
                    }
                }
                _monkeys[monkey]._plus = value;
            }
        }
        if(!((counter-3)%7)) {  // test
            long value = 0;
            for(long i=0; i<(long)line.length(); i++) {
                if (line[i] >= '0' && line[i] <= '9') {
                    value = value * 10 + (line[i] - '0');
                }
            }
            _monkeys[monkey]._div = value;
            divs *= value;
        }
        if(!((counter-4)%7)) {  // test
            long value = 0;
            for(long i=0; i<(long)line.length(); i++) {
                if (line[i] >= '0' && line[i] <= '9') {
                    value = value * 10 + (line[i] - '0');
                }
            }
            _monkeys[monkey]._otc1 = value;
        }
        if(!((counter-5)%7)) {  // test
            long value = 0;
            for(long i=0; i<(long)line.length(); i++) {
                if (line[i] >= '0' && line[i] <= '9') {
                    value = value * 10 + (line[i] - '0');
                }
            }
            _monkeys[monkey]._otc2 = value;
        }
        counter++;
    }
}

void throwMonkey(long otc, long newValue) {
    Monkey *add = &_monkeys[otc];

    // add to receiver monkey
    long size = add->_startIt.size();
    add->_startIt.resize(size+1);
    add->_startIt[size] = newValue;
}


void monkeyInspector() {

    for(long i=0; i<(long)_monkeys.size(); i++) {
        for(long j=0; j<(long)_monkeys[i]._startIt.size(); j++) {
            long newValue;
            long value = _monkeys[i]._startIt[j];
            long times = _monkeys[i]._times;
            long plus = _monkeys[i]._plus;
            long div = _monkeys[i]._div;
            long otc1 = _monkeys[i]._otc1;
            long otc2 = _monkeys[i]._otc2;
            _monkeys[i].inspected++;
            (times) ? newValue = (value+plus)*times : newValue = (value+plus)*value;
            newValue %= divs;    // manage anger levels
            (newValue%div) ? throwMonkey(otc2, newValue) : throwMonkey(otc1, newValue);
        }
        _monkeys[i]._startIt.resize(0);
    }
}

long inspectMonkeys() {
    long max1=0, max2=0;
    for(long i=0; i<(long)_monkeys.size(); i++) {
        if(_monkeys[i].inspected>max1) { max2=max1; max1=_monkeys[i].inspected; }
        else if(_monkeys[i].inspected>max2) max2 = _monkeys[i].inspected;
    }
    return max1*max2;
}

int main() {
    parseInput();
    for(long i=0; i<10000; i++) monkeyInspector();
    cout << inspectMonkeys() << endl;

    return 0;
}