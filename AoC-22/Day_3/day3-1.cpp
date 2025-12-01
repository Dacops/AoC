#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


vector<int> _items;
vector<int> _repItems;

void readInput() {

    string line;
    int numItems = 0;
    _repItems.resize(53*sizeof(int));       // indexs = values of a,b,c,...X,Y,Z;
    _items.resize(sizeof(int));

    while(getline(cin,line)) {

        int linesize = (int)line.size();
        memset(_repItems.data(), 0, 53*sizeof(int));

        for(int i=0; i<linesize; i++) {

            // int('a') = 97 (97-96=1), int('A') = 65 (65-38=27)
            int value = (int(line[i])-97>0) ? int(line[i])-96 : int(line[i])-38;

            if (i<linesize/2) { _repItems[value]++; }
            if (i>=linesize/2 && _repItems[value]!=0) {
                _items[numItems] = value;
                numItems++;
                _items.resize((numItems+1)*sizeof(int));
                break;
            }
        }
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