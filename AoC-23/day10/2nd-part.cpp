#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// initialization lambda funtion, 
// do nothing -> call for optimizations
auto init = []()
{ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();


int evaluateInput() {

/// [Parser]
    string line;
    vector<string> input;  // hold all lines

    while (getline(cin, line)) {
        input.push_back(line);
    }
/// [Parser]

/// [Solver]

    // get starting position, 'S'
    int x = 0, y = 0;
    bool over = false;
    for (int i=0; i<(int)input.size(); i++) {
        for (int j=0; j<(int)input[i].size(); j++) {
            if (input[i][j] == 'S') { y=i; x=j; over=true; break; }
        }
        if (over) break;
    }

    // [0]:N, can have pipes '|', '7', 'F'
    // [1]:E, can have pipes '-', 'J', '7'
    // [2]:S, can have pipes '|', 'L', 'J'
    // [3]:W, can have pipes '-', 'L', 'F'
    map <int, string> adj_pipes = {{0, "|7FS"}, {1, "-J7S"}, {2, "|LJS"}, {3, "-LFS"}};

    // reaching pipe from direction; leaves on direction
    map <char, int> pipe_to0 = {{'|', 0}, {'7', 3}, {'F', 1}};
    map <char, int> pipe_to1 = {{'-', 1}, {'J', 0}, {'7', 2}};
    map <char, int> pipe_to2 = {{'|', 2}, {'L', 1}, {'J', 3}};
    map <char, int> pipe_to3 = {{'-', 3}, {'L', 0}, {'F', 2}};

    // part 2 map use this struct + vector to analyze the pipes
    struct node {
        bool taken;     // if given coordinates were taken
        bool up;        // pipe goes up 
        bool down;      // pipe goes down
    };                  // then read row by row, non-taken in-between an up and down, inside               

    vector<vector<node>> survey(input.size(), vector<node>(input[0].size(), node{false, false, false}));

    // get surrounding positions; [0]:N, [1]:E, [2]:S, [3]:W
    int to = 0, from = 0;

    // get first move (check all surrounding pipes), from now onwards only need to follow the pipe
    // get surrounding pipes
    vector<char> surrounding(4, '.');
    if(y>0) surrounding[0] = input[y-1][x];
    if(x<(int)input[y].size()-1) surrounding[1] = input[y][x+1];
    if(y<(int)input.size()-1) surrounding[2] = input[y+1][x];
    if(x>0) surrounding[3] = input[y][x-1];

    // move to next position
    for (int i=0; i<4; i++) {
        if (adj_pipes[i].find(surrounding[i]) != string::npos) {
            if (i==0) { to=pipe_to0[surrounding[i]]; y--; break; }
            if (i==1) { to=pipe_to1[surrounding[i]]; x++; break; }
            if (i==2) { to=pipe_to2[surrounding[i]]; y++; break; }
            if (i==3) { to=pipe_to3[surrounding[i]]; x--; break; }
        }
    }

    // "take" 'S'
    survey[y][x].taken = true;

    for(;;) {

        if (to==0) { from=2; to=pipe_to0[input[y-1][x]]; y--; }
        else if (to==1) { from=3; to=pipe_to1[input[y][x+1]]; x++; }
        else if (to==2) { from=0; to=pipe_to2[input[y+1][x]]; y++; }
        else if (to==3) { from=1; to=pipe_to3[input[y][x-1]]; x--; }

        if (input[y][x] == 'S') break;

        // part 2
        survey[y][x].taken = true;
        if (from==2 || to==0) survey[y][x].up = true;   // comes from the south or goes to the north
        if (from==0 || to==2) survey[y][x].down = true; // comes from the north or goes to the south
    }

    // read the survey map
    int spaces = 0;
    for (int i=0; i<(int)survey.size(); i++) {

        bool line_status = false; // false = down, true = up
        for (int j=0; j<(int)survey[i].size(); j++) {

            if (survey[i][j].taken) {
                if (survey[i][j].up) line_status = true;
                if (survey[i][j].down) line_status = false;
            } else if (line_status) { // space not taken and up
                spaces++;
            }
        }
    }

    return spaces;
/// [Solver]
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}