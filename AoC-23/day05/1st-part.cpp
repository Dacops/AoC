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


struct x_to_y_map {
    uint64_t dest;
    uint64_t src;
    uint64_t rng;
}; 

struct seed {
    uint64_t value;
    bool transformed;

    // to get min value
    bool operator<(const seed& other) const {
        return value < other.value;
    }
};

uint64_t evaluateInput() {

    string line;
    int lineNum = 0;
    vector<seed> seeds;
    vector<x_to_y_map> rules;

    while (getline(cin, line)) {

        // apply mapping
        // added 2 empty lines to the end of input so it can catch the CRLF from the penultimate line
        if (line.size() == 1) {

            // 1st empty line, no mapping
            if (lineNum == 1) continue;

            // map with given rule
            for (const auto& rule : rules) {
                for (auto& seed : seeds) {
                    if (seed.value >= rule.src && seed.value <= rule.src+rule.rng && !seed.transformed) {
                        seed.value = rule.dest + (seed.value-rule.src);
                        seed.transformed = true;
                    }
                }
            }

            for (auto& seed : seeds) seed.transformed = false;

            rules.clear();
            continue;
        } 

        x_to_y_map temp;
        uint64_t number = 0, arg_count = 0;
        for (const char& c : line) {
            
            if (c>='0' && c<='9') {
                number = number*10 + (c-'0');
            } else if (c==' ' || c=='\r') {
                // get seeds
                if (!lineNum && number) seeds.push_back({number, false});
                
                // get seed transformation
                else {
                    switch(arg_count) {
                        case 0: temp.dest = number; break;
                        case 1: temp.src = number; break;
                        case 2: temp.rng = number; break;
                    }

                    arg_count++;
                }

                if (arg_count == 3) rules.push_back(temp);
                number = 0;
            }
        }

        lineNum++;
    }

    return min_element(seeds.begin(), seeds.end())->value;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}