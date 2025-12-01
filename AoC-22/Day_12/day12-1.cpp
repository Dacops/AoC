#include <iostream>
#include <vector>

using namespace std;

struct Node {
    char height;
    bool visited;
    int distance;
};

vector<vector<Node>> _matrix;
vector<pair<int, int>> _generation;
pair<int, int> _endPoint;

void parseInput() {

    string line;
    int y = 0;

    while(getline(cin, line)) {

        line = line.substr(0,line.find('\r'));
        _matrix.resize(y+1);
        _matrix[y].resize(line.length());

        for(int x=0; x<line.length(); x++) {

            if(line[x]=='S') {
                _generation.resize(1);
                _generation[0] = {y, x};
                line[x] = 'a';
            }

            if(line[x]=='E') {
                _endPoint = {y, x};
                line[x] = 'z';
            }

            _matrix[y][x].height = line[x];
            _matrix[y][x].visited = false;
            _matrix[y][x].distance = 0;
        }
        y++;
    }
}

void BFS() {

    vector<pair<int, int>> newGeneration;
    newGeneration.resize(0);

    for(int i=0; i<(int)_generation.size(); i++) {

        int y = _generation[i].first;
        int x = _generation[i].second;
        _matrix[y][x].visited = true;

        // visits nearby nodes
        // 1. check if nearby node is inside matrix.
        // 2. check if nearby node can be visited (next height belong to ['a', current height +1]).
        // 3. check if nearby node is yet to be visited.

        // node upwards
        if ((y - 1) >= 0 && (y - 1) < (int) _matrix.size()) {

            if (_matrix[y - 1][x].height >= 'a' &&
                _matrix[y - 1][x].height <= _matrix[y][x].height + 1 && !_matrix[y - 1][x].visited) {

                _matrix[y - 1][x].visited = true;
                _matrix[y - 1][x].distance = _matrix[y][x].distance + 1;

                pair<int, int> coordinates = {y - 1, x};
                newGeneration.resize((int) newGeneration.size() + 1);
                newGeneration[(int) newGeneration.size() - 1] = coordinates;
            }
        }

        // node to the right
        if ((x + 1) >= 0 && (x + 1) < (int) _matrix[y].size()) {
            if (_matrix[y][x + 1].height >= 'a' &&
                _matrix[y][x + 1].height <= _matrix[y][x].height + 1 && !_matrix[y][x + 1].visited) {

                _matrix[y][x + 1].visited = true;
                _matrix[y][x + 1].distance = _matrix[y][x].distance + 1;

                pair<int, int> coordinates = {y, x + 1};
                newGeneration.resize((int) newGeneration.size() + 1);
                newGeneration[(int) newGeneration.size() - 1] = coordinates;
            }
        }

        // node downwards
        if ((y + 1) >= 0 && (y + 1) < (int) _matrix.size()) {
            if (_matrix[y + 1][x].height >= 'a' &&
                _matrix[y + 1][x].height <= _matrix[y][x].height + 1 && !_matrix[y + 1][x].visited) {

                _matrix[y + 1][x].visited = true;
                _matrix[y + 1][x].distance = _matrix[y][x].distance + 1;

                pair<int, int> coordinates = {y + 1, x};
                newGeneration.resize((int) newGeneration.size() + 1);
                newGeneration[(int) newGeneration.size() - 1] = coordinates;
            }
        }

        // node to the left
        if ((x - 1) >= 0 && (x - 1) < (int) _matrix[y].size()) {
            if (_matrix[y][x - 1].height >= 'a' &&
                _matrix[y][x - 1].height <= _matrix[y][x].height + 1 && !_matrix[y][x - 1].visited) {

                _matrix[y][x - 1].visited = true;
                _matrix[y][x - 1].distance = _matrix[y][x].distance + 1;

                pair<int, int> coordinates = {y, x - 1};
                newGeneration.resize((int) newGeneration.size() + 1);
                newGeneration[(int) newGeneration.size() - 1] = coordinates;
            }
        }
    }

    if(_generation.size()==0) return;

    // check if end point in visited points
    for(int i=0; i<(int)newGeneration.size(); i++) {
        if(newGeneration[i]==_endPoint) {
            cout << _matrix[_endPoint.first][_endPoint.second].distance << endl;
            return;
        }
    }

    // else continue BFS iteration
    _generation.resize((int)newGeneration.size());
    for(int i=0; i<(int)newGeneration.size(); i++) {
        _generation[i] = newGeneration[i];
    }

    BFS();
}


int main() {
    parseInput();
    BFS();

    return 0;
}