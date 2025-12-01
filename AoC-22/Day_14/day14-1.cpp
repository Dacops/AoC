#include <iostream>
#include <vector>

using namespace std;


vector<vector<bool>> _occupied;     // save occupied spots
vector<string> _data;               // unaltered lines read
int maxX = 0, maxY = 0,             // maximum X and Y values, smaller matrix
    minX = 500;                     // minimum X value, minimum Y = 0

void parseInput() {

    string line;
    while(getline(cin, line)) {

        // do not edit saved vector
        line.append(".");
        string newline = line;
        _data.push_back(newline);

        bool isNum = false;     // currently reading num
        int num = 0;            // current num
        int counter = 0;        // even: num is x, odd: num is y

        for(int i=0; i<line.length(); i++) {
            if(line[i]>='0' && line[i]<='9') {
                if(isNum) {
                    num = num * 10 + line[i]-'0';
                } else {
                    num = line[i]-'0';
                    isNum = true;
                }
            } else {
                if(isNum) {     // save num
                    if(counter%2==0) {
                        if(minX>num) minX = num;
                        if(maxX<num) maxX = num;
                    } else {
                        if(maxY<num) maxY = num;
                    }
                }
                if(line[i]==',' || line[i]=='>') counter++;
                isNum = false;
            }
        }
    }
}

void buildMatrix() {

    _occupied.resize(maxY+1);
    for(int i=0; i<(int)_occupied.size(); i++) _occupied[i].resize((maxX-minX)+1);

    for(int i=0; i<(int)_data.size(); i++) {

        string line = _data[i];
        vector<pair<int, int>> _coordinates;
        _coordinates.resize(0);

        bool isNum = false;     // currently reading num
        int num = 0;            // current num
        int counter = 0;        // even: num is x, odd: num is y

        // create coordinates vector
        for(int j=0; j<line.length(); j++) {
            if(line[j]>='0' && line[j]<='9') {
                if(isNum) {
                    num = num * 10 + line[j]-'0';
                } else {
                    num = line[j]-'0';
                    isNum = true;
                }
            } else {
                if(isNum) {     // save num
                    if(counter%2==0) {
                        _coordinates.resize((int)_coordinates.size()+1);
                        _coordinates[counter/2].first = num;
                    } else {
                        _coordinates[counter/2].second = num;
                    }
                }
                if(line[j]==',' || line[j]=='>') counter++;
                isNum = false;
            }
        }

        for(int j=0; j<(int)_coordinates.size()-1; j++) {

            int x1 = _coordinates[j].first;
            int y1 = _coordinates[j].second;
            int x2 = _coordinates[j+1].first;
            int y2 = _coordinates[j+1].second;


            // difference in Y range
            if(x1==x2) {
                int diff = abs(y1-y2);
                int smallest = (y1<y2)? y1 : y2;
                for(int k=smallest; k<=smallest+diff; k++) {
                    _occupied[k][x1-minX] = true;
                }
            }
            // difference in X range
            else {

                int diff = abs(x1-x2);
                int smallest = (x1<x2)? x1 : x2;
                for(int k=smallest; k<=smallest+diff; k++) {
                    _occupied[y1][k-minX] = true;
                }
            }
        }
    }
}

bool addUnit(int x, int y) {

    x = x-minX;
    if(_occupied[y][x]) return false;           // starting point is full

    while(1) {                                  // drop sand

        if (!_occupied[y+1][x]) {               // drop downwards
            y++;
            if(y+1>maxY) return false;          // falls off board
        }
        else if (!_occupied[y+1][x-1]) {        // drop downwards left
            y++, x--;
            if ((x+1>maxX-minX) || (y+1>maxY)) return false;    // falls off board
        }
        else if (!_occupied[y+1][x+1]) {        // drop downwards right
            y++, x++;
            if ((x+1>maxX-minX) || (y+1>maxY)) return false;    // falls off board
        }

        // no free space, lock current position;
        else {
            _occupied[y][x] = true;
            break;
        }
    }
    return true;
}

int addSand() {

    int sandCount = 0;
    while(addUnit(500, 0)) {
        sandCount++;
    }

    return sandCount;
}



int main() {
    parseInput();
    buildMatrix();
    cout << addSand() << endl;

    return 0;
}