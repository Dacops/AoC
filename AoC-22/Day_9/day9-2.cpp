#include <iostream>
#include <vector>

using namespace std;

vector<char> _directions;
vector<int> _distances;
vector<vector<bool>> _matrix;

// hold pieces coordinates
vector<vector<int>> _coords = { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                               {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} };

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

void trackHead(int head, bool track) {
    if(abs(_coords[head][1]-_coords[head+1][1])<=1 && abs(_coords[head][0]-_coords[head+1][0])<=1) return;

    if(abs(_coords[head][1]-_coords[head+1][1])>1 && abs(_coords[head][0]-_coords[head+1][0])==0 ) {
        // move vertically
        _coords[head][1]>_coords[head+1][1] ? _coords[head+1][1]++ : _coords[head+1][1]--;
    } else if(abs(_coords[head][1]-_coords[head+1][1])==0 && abs(_coords[head][0]-_coords[head+1][0])>1 ) {
        // move horizontally
        _coords[head][0]>_coords[head+1][0] ? _coords[head+1][0]++ : _coords[head+1][0]--;
    } else {
        // move diagonal
        _coords[head][1]>_coords[head+1][1] ? _coords[head+1][1]++ : _coords[head+1][1]--;
        _coords[head][0]>_coords[head+1][0] ? _coords[head+1][0]++ : _coords[head+1][0]--;
    }
    if (track) _matrix[_coords[head+1][1]][_coords[head+1][0]] = true;
}

void createMatrix() {
    for(int i=0; i<(int)_directions.size(); i++) {
        for(int n=0; n<_distances[i]; n++) {
            if (_directions[i] == 'U') {
                // Resize and push back
                if (_coords[0][1] - 1 < 0) {
                    int size = (int) _matrix.size();
                    _matrix.resize(size + 1);
                    // push back
                    for (int j = size; j > 0; j--) {
                        _matrix[j] = _matrix[j - 1];
                    }
                    // row 0 on 0's
                    for (int j = 0; j < (int) _matrix[0].size(); j++) {
                        _matrix[0][j] = false;
                    }
                    for(int c=1; c<(int)_coords.size(); c++) {
                        _coords[c][1]++;
                    }
                } else {
                    _coords[0][1]--;
                }

                } else if (_directions[i] == 'D') {
                    // Resize Downwards
                    _coords[0][1]++;
                    int size = (int) _matrix.size();
                    if (_coords[0][1] + 1 > size) {
                        _matrix.resize(size + 1);
                        for (int j = _coords[0][1]; j < (int) _matrix.size(); j++) {
                            _matrix[j].resize((int) _matrix[0].size());
                        }
                    }

                } else if (_directions[i] == 'R') {
                    // Resizes Rightwards
                    _coords[0][0]++;
                    int size = (int) _matrix[0].size();
                    if (_coords[0][0] + 1 > size) {
                        for (int j = 0; j < (int) _matrix.size(); j++) {
                            _matrix[j].resize(size + 1);
                        }
                    }

                } else if (_directions[i] == 'L') {
                    // Resize Leftwards and push back
                    if (_coords[0][0] - 1 < 0) {
                        int size = (int) _matrix[0].size();
                        // push back
                        for (int j = 0; j < (int) _matrix.size(); j++) {
                            _matrix[j].resize(size + 1);
                            for (int n = size; n > 0; n--) {
                                _matrix[j][n] = _matrix[j][n - 1];
                            }
                            // column 0 on 0
                            _matrix[j][0] = false;
                        }
                        for(int c=1; c<(int)_coords.size(); c++) {
                            _coords[c][0]++;
                        }
                    } else {
                        _coords[0][0]--;
                    }
                }
            trackHead(0, false);
            for(int c=1; c<(int)_coords.size()-1; c++) {
                bool track;

                (c == (int) _coords.size() - 2) ? track = true : track = false;
                trackHead(c, track);
            }
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