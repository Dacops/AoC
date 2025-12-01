#include <iostream>
#include <vector>

using namespace std;


vector<pair<string, string>> _entries;  // all entries
vector<int> _wrong;                     // wrong entries

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

bool isRight(string left, string right) {

    // int = depth, vector = bucket
    vector<pair<int, int>> leftmap;
    vector<pair<int, int>> rightmap;

    int depth = 0, bucket = 0, num = 0;
    for(int i=0; i<left.length(); i++) {

        if(left[i]=='[') depth++;
        if(left[i]==']') {
            // empty list
            if(left[i-1]=='[') {
                int size = (int)leftmap.size();
                leftmap.resize(size+1);
                leftmap[bucket].first = depth;
                leftmap[bucket].second = -1;
                bucket++;
            }
            depth--;
        }

        // needed for cases like [],[] (compare offset with comma)
        if(left[i]==',') {
            int size = (int)leftmap.size();
            leftmap.resize(size+1);
            leftmap[bucket].first = depth;
            leftmap[bucket].second = -2;
            bucket++;
        }

        // numbers
        if(left[i]>='0' && left[i]<='9') {
            num = left[i]-'0';
            // numbers > 9
            if(left[i+1]>='0' && left[i+1]<='9') {
                num = num * 10 + left[i + 1]-'0';
                i++;
            }
            int size = (int)leftmap.size();
            leftmap.resize(size+1);
            leftmap[bucket].first = depth;
            leftmap[bucket].second = num;
            bucket++;
        }
    }

    depth = 0, bucket = 0, num = 0;
    for(int i=0; i<right.length(); i++) {

        if(right[i]=='[') depth++;
        if(right[i]==']') {
            // empty list
            if(right[i-1]=='[') {
                int size = (int)rightmap.size();
                rightmap.resize(size+1);
                rightmap[bucket].first = depth;
                rightmap[bucket].second = -1;
                bucket++;
            }
            depth--;
        }

        // needed for cases like [],[] (compare offset with comma)
        if(right[i]==',') {
            int size = (int)rightmap.size();
            rightmap.resize(size+1);
            rightmap[bucket].first = depth;
            rightmap[bucket].second = -2;
            bucket++;
        }

        // numbers
        if(right[i]>='0' && right[i]<='9') {
            num = right[i]-'0';
            // numbers > 9
            if(right[i+1]>='0' && right[i+1]<='9') {
                num = num * 10 + right[i + 1]-'0';
                i++;
            }
            int size = (int)rightmap.size();
            rightmap.resize(size+1);
            rightmap[bucket].first = depth;
            rightmap[bucket].second = num;
            bucket++;
        }
    }

    int smallestSet = min((int)leftmap.size(), (int)rightmap.size());
    for(int i=0; i<smallestSet; i++) {

        // don't run on ',' entries, only needed to verify offset
        if(leftmap[i].second!=-2 && rightmap[i].second!=-2) {
            // empty lists
            if (leftmap[i].second == -1 && rightmap[i].second == -1) {
                if (leftmap[i].first < rightmap[i].first) return true;
                if (leftmap[i].first > rightmap[i].first) return false;
            }

            // different offsets, normalize
            if (leftmap[i].first != rightmap[i].first) {

                // left offset is larger
                if (leftmap[i].first > rightmap[i].first) {
                    int *rightOffset = &rightmap[i].first;
                    *rightOffset = leftmap[i].first;
                }

                    // right offset is larger
                else {
                    int *leftOffset = &leftmap[i].first;
                    *leftOffset = rightmap[i].first;
                }
            }

            // equal offsets, compare values.
            if (leftmap[i].first == rightmap[i].first) {
                if (leftmap[i].second < rightmap[i].second) return true;
                if (leftmap[i].second > rightmap[i].second) return false;
            }

            // compare next integers offset (smaller = subset has ended) do nothing if both end
            if ((leftmap[i+1].first < leftmap[i].first) && (rightmap[i+1].first < rightmap[i].first)) {}
            else if (leftmap[i + 1].first < leftmap[i].first) return true;
            else if (rightmap[i + 1].first < rightmap[i].first) return false;
        }
    }

    // left / right list is larger than left / right list
    if((int)leftmap.size() < (int)rightmap.size()) return true;
    if((int)leftmap.size() > (int)rightmap.size()) return false;
    return 0;
}

int evaluateInput() {
    for(int i=0; i<(int)_entries.size(); i++) {

        string left = _entries[i].first;
        string right = _entries[i].second;

        if(isRight(left, right)) {
            int size = (int)_wrong.size();
            _wrong.resize(size+1);
            _wrong[size] = i+1;
        }
    }
    int sum = 0;
    for(int i=0; i<(int)_wrong.size(); i++) {
        sum+=_wrong[i];
    }
    return sum;
}


int main() {
    parseInput();
    cout << evaluateInput() << endl;

    return 0;
}