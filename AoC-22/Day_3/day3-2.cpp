#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


int _numItems = 0;
vector<int> _items;
vector<int> _repItems;


void saveData() {

    _items.resize((_numItems+1)*sizeof(int));
    for(int i=0; i<(int)_repItems.size(); i++) {
        if(_repItems[i] == 3) {
            _items[_numItems] = i;
            _numItems++;
            break;
        }
    }
    // clear vector;
    memset(_repItems.data(), 0, 53*sizeof(int));
}

void readInput() {

    string line;
    int numLines = 0;
    // indexs = values of a,b,c,...X,Y,Z;
    _repItems.resize(53*sizeof(int));
    memset(_repItems.data(), 0, 53*sizeof(int));

    while(getline(cin,line)) {

        int linesize = (int)line.size();

        for(int i=0; i<linesize; i++) {

            // int('a') = 97 (97-96=1), int('A') = 65 (65-38=27);
            int value = (int(line[i])-97>0) ? int(line[i])-96 : int(line[i])-38;

            // only increases counter once per loop;
            if(_repItems[value] == numLines%3) {
                _repItems[value]++;
            }
        }
        // splits lines in 3-groups;
        numLines++;
        if(!(numLines%3)) saveData();
    }
}

int evaluateInput() {

    int sum = 0;

    for(int i=0; i<(int)_items.size(); i++) {
        sum+=_items[i];
    }
    return sum;
}


int main() {
    readInput();
    cout << evaluateInput() << endl;
    return 0;
}