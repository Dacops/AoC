#include <iostream>

using namespace std;


int readInput() {

    int b1, e1, b2, e2, overlaps=0;
    // inputs received as: b1-e1,b2-e2
    while(cin>>b1, cin.ignore(), cin>>e1, cin.ignore(),
            cin>>b2, cin.ignore(), cin>>e2) {
        if( (b1<=b2 && e1>=e2) || (b1>=b2 && e1<=e2) ) overlaps++;
    }
    return overlaps;
}

int main() {
    cout << readInput() << endl;
    return 0;
}