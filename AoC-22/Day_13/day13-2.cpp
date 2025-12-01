#include <iostream>
#include <vector>

using namespace std;


vector<pair<string, string>> _entries;          // all entries
vector<vector<pair<int, int>>> _sortedEntries;  // sort the entries
vector<int> _wrong;                             // wrong entries

void parseInput() {

    int num = 0;
    string line;
    while(getline(cin, line)) {
        if(num%3==0) {
            _entries.resize(num/3+1);
            _entries[num/3].first = line;
        }
        if(num%3==1) _entries[num/3].second = line;
        num++;
    }
}

// map2 = map to insert
bool wrongOrder(vector<pair<int, int>> map1, vector<pair<int, int>> map2) {

    int smallest = min((int)map1.size(), (int)map2.size());
    for(int i=0; i<smallest; i++) {

        // 1st compare values
        if(map1[i].second < map2[i].second) return false;
        if(map1[i].second > map2[i].second) return true;


        // if values are equal, compare offsets
        if(map1[i].first < map2[i].first) return false;
        if(map1[i].first > map2[i].first) return true;

    }
    if((int)map1.size() < (int)map2.size()) return false;
    if((int)map1.size() > (int)map2.size()) return true;

    // equal entries
    return true;
}

int sort(string entry, bool getIndex) {

    // int = depth, vector = bucket
    vector<pair<int, int>> entrymap;

    // create comparable vector for current entry
    int depth = 0, num = 0;
    for(int i=0; i<entry.length(); i++) {

        if(entry[i]=='[') depth++;
        if(entry[i]==']') {
            // empty list
            if(entry[i-1]=='[') {
                entrymap.push_back({depth, -1});
            }
            depth--;
        }

        // needed for cases like [],[] (compare offset with comma)
        if(entry[i]==',') {
            entrymap.push_back({depth, -2});
        }

        // numbers
        if(entry[i]>='0' && entry[i]<='9') {
            num = entry[i]-'0';
            // numbers > 9
            if(entry[i+1]>='0' && entry[i+1]<='9') {
                num = num * 10 + entry[i + 1]-'0';
                i++;
            }
            entrymap.push_back({depth, num});
        }
    }

    int size = (int)_sortedEntries.size();

    // 1st entry
    if (size==0) _sortedEntries.push_back(entrymap);

    // compare current entry to the entries already in the vector
    else {
        // if not in wrong order, place it in last position
        int index = size;

        for(int i=0; i<size; i++) {
            if (wrongOrder(_sortedEntries[i], entrymap)) {
                index=i;
                break;
            }
        }
        // pushback vector and add entry
        _sortedEntries.emplace(_sortedEntries.begin()+index, entrymap);

        // return index for requested entries
        if(getIndex) return index+1;
    }
    return 1;
}


int evaluateInput() {
    for(int i=0; i<(int)_entries.size(); i++) {

        sort(_entries[i].first, false);
        sort(_entries[i].second, false);
    }

    return sort("[[2]]", true)*sort("[[6]]", true);
}


int main() {
    parseInput();
    cout << evaluateInput() << endl;

    return 0;
}