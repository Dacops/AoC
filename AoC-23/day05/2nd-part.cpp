#include <iostream>
#include <vector>
#include <string>

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
};

uint64_t evaluateInput() {

    string line;
    int lineNum = 0;
    vector<seed> seeds;
    vector<pair<seed,seed>> mapIntervals;   // 1st seed start interval, 2nd seed end interval, use
    vector<x_to_y_map> rules;               // 1st transformed has interval transformed

    while (getline(cin, line)) {

        // apply mapping
        // added 2 empty lines to the end of input so it can catch the CRLF from the penultimate line
        if (line.size() == 1) {

            // 1st empty line, create huge object to hold everything
            if (lineNum == 1) {

                for (int i=0; i<(int)seeds.size(); i+=2) {
                    
                    seed from{seeds[i].value, false};
                    seed to{seeds[i].value+seeds[i+1].value-1, false};
                    mapIntervals.push_back(make_pair(from, to));
                }
                continue;
            }

            // map with given rule
            for (const auto& rule : rules) {
                
                for (int i=0; i<(int)mapIntervals.size(); i++) {

                    // move entire interval, update current interval
                    if (mapIntervals[i].first.value >= rule.src && mapIntervals[i].second.value <= rule.src+rule.rng && 
                            !mapIntervals[i].first.transformed) {
                        
                        mapIntervals[i].first.value = rule.dest + (mapIntervals[i].first.value-rule.src);
                        mapIntervals[i].first.transformed = true;

                        mapIntervals[i].second.value = rule.dest + (mapIntervals[i].second.value-rule.src);
                    }

                    // move first half of interval, update current interval & create another
                    else if (mapIntervals[i].first.value >= rule.src && mapIntervals[i].first.value <= rule.src+rule.rng && 
                            !mapIntervals[i].first.transformed) {
                        
                        // start & end of moved interval
                        seed from{rule.dest + (mapIntervals[i].first.value-rule.src), true};
                        seed to{rule.dest+rule.rng, false};

                        mapIntervals.push_back(make_pair(from, to));

                        // update new start to not moved interval
                        // start of not moved interval
                        mapIntervals[i].first.value = rule.src+rule.rng;
                        mapIntervals[i].first.transformed = true;

                        // end of not moved interval
                        // not changed
                    }

                    // move second half of interval
                    else if (mapIntervals[i].second.value >= rule.src && mapIntervals[i].second.value <= rule.src+rule.rng && 
                            !mapIntervals[i].first.transformed) {
                        
                        // start of moved interval
                        seed from{rule.dest, true};
                        seed to{rule.dest + (mapIntervals[i].second.value-rule.src), false};
                        mapIntervals.push_back(make_pair(from, to));

                        // start of not moved interval
                        // not changed, but updated
                        mapIntervals[i].first.transformed = true;

                        // end of not moved interval
                        mapIntervals[i].second.value = rule.src-1;                   
                    }
                }
            }

            for (auto& seed : mapIntervals) seed.first.transformed = false;
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

    uint64_t min = UINT64_MAX;
    for (const auto& seed : mapIntervals) {
        if (seed.first.value < min) min = seed.first.value;
    }
    
    return min;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}