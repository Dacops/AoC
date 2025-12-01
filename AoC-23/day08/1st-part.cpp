#include <iostream>
#include <string>
#include <unordered_map>

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

int evaluateInput() {

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

                switch (argcount) {

                    // current node
                    case 0: {
                        if (c>='A' && c<='Z') curr += c;
                        break;
                    }

                    // left node
                    case 1: {
                        if (c>='A' && c<='Z') left += c;
                        break;
                    }

                    // right node
                    case 2: {
                        if (c>='A' && c<='Z') right += c;
                        break;
                    }
                }
            }
        }

        if (!mode) continue;

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
        if (it != used_nodes.end()) temp->left = it->second;   // L node already exists
        else {
            temp_left = new node{left, nullptr, nullptr};       // create new L node
            used_nodes.insert({left, temp_left});               // insert created L node to used_nodes
            temp->left = temp_left;                             // link created L node to current node
        }

        // check if right node exists
        it = used_nodes.find(right);
        if (it != used_nodes.end()) temp->right = it->second;  // R node already exists
        else {
            temp_right = new node{right, nullptr, nullptr};     // create new R node
            used_nodes.insert({right, temp_right});             // insert created R node to used_nodes
            temp->right = temp_right;                           // link created R node to current node
        }
    }
/// [Parser]

/// [Solver]

    int answer = 0;

    node* curr_node = used_nodes.find("AAA")->second;

    for (;;) {
        for (const auto& c : moves) {
        
            if (curr_node->value == "ZZZ") return answer;
            if (c=='L') curr_node = curr_node->left;
            else curr_node = curr_node->right;
            answer++;
        }
    }

    return answer;
}


int main() {
    cout << evaluateInput() << endl;

    return 0;
}