#include <iostream>
#include <vector>

using namespace std;

vector<char> _directions;
vector<int> _distances;
vector<vector<bool>> _matrix;

// hold head/tail coordinates
vector<int> _head = {0, 0};
vector<int> _tail = {0, 0};

void parseInput() {

    char direction;
    int distance;

    while(cin>>direction, cin.ignore(), cin>>distance) {

        int size = (int)_directions.size();

        _directions.resize(size+1);
        _distances.resize(size+1);
        _directions[size] = direction;
        _distances[size] = distance;
    }

    // default matrix
    _matrix.resize(1);
    _matrix[0].resize(1);
    _matrix[0][0] = true;
}

void trackHead() {
    if(abs(_head[1]-_tail[1])<=1 && abs(_head[0]-_tail[0])<=1) return;

    if(abs(_head[1]-_tail[1])>1 && abs(_head[0]-_tail[0])==0 ) {
        // move vertically
        _head[1]>_tail[1] ? _tail[1]++ : _tail[1]--;
    } else if(abs(_head[1]-_tail[1])==0 && abs(_head[0]-_tail[0])>1 ) {
        // move horizontally
        _head[0]>_tail[0] ? _tail[0]++ : _tail[0]--;
    } else {
        // move diagonal
        _head[1]>_tail[1] ? _tail[1]++ : _tail[1]--;
        _head[0]>_tail[0] ? _tail[0]++ : _tail[0]--;
    }
    _matrix[_tail[1]][_tail[0]] = true;
}

void createMatrix() {
    for(int i=0; i<(int)_directions.size(); i++) {
        for(int n=0; n<_distances[i]; n++) {
            if (_directions[i] == 'U') {
                // Resize and push back
                if(_head[1]-1<0) {
                    int size = (int)_matrix.size();
                    _matrix.resize(size+1);
                    // push back
                    for(int j=size; j>0; j--) {
                        _matrix[j] = _matrix[j-1];
                    }
                    // row 0 on 0's
                    for(int j=0; j<(int)_matrix[0].size(); j++) {
                        _matrix[0][j] = false;
                    }
                    _tail[1]++;
                } else {
                    _head[1]--;
                }

            } else if (_directions[i] == 'D') {
                // Resize Downwards
                _head[1]++;
                int size = (int) _matrix.size();
                if(_head[1]+1>size) {
                    _matrix.resize(size+1);
                    for (int j=_head[1]; j < (int) _matrix.size(); j++) {
                        _matrix[j].resize((int) _matrix[0].size());
                    }
                }

            } else if (_directions[i] == 'R') {
                // Resizes Rightwards
                _head[0]++;
                int size = (int)_matrix[0].size();
                if(_head[0]+1>size) {
                    for (int j=0; j<(int)_matrix.size(); j++) {
                        _matrix[j].resize(size+1);
                    }
                }

            } else if (_directions[i] == 'L') {
                // Resize Leftwards and push back
                if(_head[0]-1<0) {
                    int size = (int)_matrix[0].size();
                    // push back
                    for(int j=0; j<(int)_matrix.size(); j++) {
                        _matrix[j].resize(size+1);
                        for(int n=size; n>0; n--) {
                            _matrix[j][n] = _matrix[j][n-1];
                        }
                        // column 0 on 0
                        _matrix[j][0] = false;
                    }
                    _tail[0]++;
                } else {
                    _head[0]--;
                }
            }
            trackHead();
        }
    }
}

int countMatrix() {

    int count = 0;
    for(int i=0; i<(int)_matrix.size(); i++) {
        for(int j=0; j<(int)_matrix[0].size(); j++) {
            if(_matrix[i][j]) count++;
        }
    }
    return count;
}

int main() {
    parseInput();
    createMatrix();
    cout << countMatrix() << endl;

    return 0;
}