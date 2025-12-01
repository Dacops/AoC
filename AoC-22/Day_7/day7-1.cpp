#include <iostream>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

map<string, long> _size;                // value of dir
vector<string> _directories;            // hold directories


string pathToString(int offset) {
    string path = "";
    for(int i=0; i<(int)_directories.size()-offset; i++) {
        path.append(_directories[i]);
        path.append("/");
    }
    return path;
}


void sizeContained(int value) {

    // key does not exist in map
    if(_size.find(pathToString(0)) == _size.end()) {
        _size.insert({pathToString(0), value});
    }

    // key exist in map
    else{
        auto it = _size.find(pathToString(0));
        it->second += value;
    }

    // add to parents directory values of child directory
    for(int i=1; i<(int)_directories.size(); i++) {
        if(_size.find(pathToString(i)) == _size.end()) {
            _size.insert({pathToString(i), value});
        } else {
            auto parent = _size.find(pathToString(i));
            parent->second += value;
        }
    }
}


void parseInput() {

    string line, command;

    while(getline(cin,line)) {

        char *ptr;
        char l[line.size() + 1];
        vector <char*> commands;

        strcpy(l, line.c_str());
        ptr = strtok(l, " ");

        while(ptr != NULL) {
            int size = (int)commands.size();
            commands.resize(size+1);
            commands[size] = ptr;
            ptr = strtok(NULL, " ");
        }

        // user command
        if(!strcmp(commands[0],"$")) {
            if(!strcmp(commands[1],"cd")) {

                // remove '\r';
                char dir[strlen(commands[2])-1];
                sscanf(commands[2], "%s\r", dir);

                // go back one level
                if(!strcmp(dir,"..")) {
                    int size = (int) _directories.size();
                    _directories.resize(size - 1);
                }
                // go back to the outermost directory
                else if(!strcmp(dir,"/")) {
                    _directories.resize(1);
                }
                // new directory
                else {
                    int size = (int) _directories.size();
                    _directories.resize(size + 1);
                    _directories[size] = dir;
                }
            }
        }


        // ls
        else {
            // contains file
            if(strcmp(commands[0],"dir")) {
                long value = stoi(commands[0]);
                sizeContained(value);
            }
        }
    }
}

void evaluateInput() {

    long totalSize = 0;

    map<string, long>::iterator it;
    for(it=_size.begin(); it!=_size.end(); it++) {
        if(it->second <= 100000) { totalSize += it->second; }
    }

    cout << totalSize << endl;
}


int main() {
    parseInput();
    evaluateInput();

    return 0;
}