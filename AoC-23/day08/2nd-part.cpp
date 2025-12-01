#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

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


struct node {
    string value;
    node* right;
    node* left;
};

uint64_t evaluateInput() {

/// [Parser]
    string line;
    string moves;
    unordered_map<string, node*> used_nodes;   // check if given L/R node exists

    int mode = 0;
    while (getline(cin, line)) {
        
        // blank line, start collecting nodes
        if (line.empty()) { mode = 1; continue; }

        int argcount = 0;
        string curr, left, right;
        for (const auto& c : line) {

            // get moves
            if (!mode) {
                if (c=='L' || c=='R') moves+=c;

            // get nodes
            } else {

                if (c=='=' || c==',') { argcount++; continue; }

                // add [0,9] to parser aswell to pass example aswell
                switch (argcount) {

                    // current node
                    case 0: {
                        if ( (c>='A' && c<='Z') || (c>='0' && c<='9') ) curr += c;
                        break;
                    }

                    // left node
                    case 1: {
                        if ( (c>='A' && c<='Z') || (c>='0' && c<='9') ) left += c;
                        break;
                    }

                    // right node
                    case 2: {
                        if ( (c>='A' && c<='Z') || (c>='0' && c<='9') ) right += c;
                        break;
                    }
                }
            }
        }

        if (!mode) continue;                                    // 1st line, no nodes

        node *temp, *temp_left, *temp_right;

        // check if current node exists
        auto it = used_nodes.find(curr);
        if (it != used_nodes.end()) temp = it->second;          // node already exists
        else {
            temp = new node{curr, nullptr, nullptr};            // create new node
            used_nodes.insert({curr, temp});                    // insert current node to used_nodes
        }

        // check if left node exists
        it = used_nodes.find(left);
        if (it != used_nodes.end()) temp->left = it->second;    // L node already exists
        else {
            temp_left = new node{left, nullptr, nullptr};       // create new L node
            used_nodes.insert({left, temp_left});               // insert created L node to used_nodes
            temp->left = temp_left;                             // link created L node to current node
        }

        // check if right node exists
        it = used_nodes.find(right);
        if (it != used_nodes.end()) temp->right = it->second;   // R node already exists
        else {
            temp_right = new node{right, nullptr, nullptr};     // create new R node
            used_nodes.insert({right, temp_right});             // insert created R node to used_nodes
            temp->right = temp_right;                           // link created R node to current node
        }
    }
/// [Parser]

/// [Solver]
    vector<node*> start_nodes;

    // get all starting nodes
    for (const auto& node : used_nodes) {
        if (node.first[2] == 'A') start_nodes.push_back(node.second);
    }

    mode = 1;
    vector<int> answers(start_nodes.size(), 0);
    
    for (int i=0; i<(int)start_nodes.size(); i++) {
        
        int answer = 0;
        while (mode) {
            for (const auto& c : moves) {

                if (start_nodes[i]->value[2] == 'Z') {
                    answers[i] = answer;
                    mode = 0;
                }

                if (c=='L') start_nodes[i] = start_nodes[i]->left;
                else start_nodes[i] = start_nodes[i]->right;
                answer++;
            }
        }
        mode = 1;
    }

    // get minimum common multiple of given values
    mode = 1;
    uint64_t res = 1;
    int prime = 2, used = 0;
    while (mode) {

        mode = 0, used = 0;
        for (int i=0; i<(int)answers.size(); i++) {
            
            // cout << answers[i] << " & " << prime << endl;
            if (answers[i] != 1) mode = 1;
            if (answers[i] % prime == 0) { answers[i] /= prime; used++; }
        }

        if (!used) prime++;
        else res*=prime;
    }

    return res;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}