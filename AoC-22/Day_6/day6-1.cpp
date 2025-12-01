#include <iostream>
#include <vector>

using namespace std;


const int distinct = 4;

int diff(vector<char> chars) {
    for(int j=0; j<(int)chars.size(); j++) {
        for (int i=0; i < (int) chars.size(); i++) {
            if (i!=j && chars[j]==chars[i]) return 0;
        }
    }
    return 1;
}


int readInput() {

    vector<char> chars;
    chars.resize(distinct);
    char curr;
    int i=0;

    while(cin>>curr) {
        chars[i%distinct]=curr;
        i++;

        if(i>distinct && diff(chars))  break;
    }
    return i;
}



int main() {
    cout << readInput() << endl;

    return 0;
}