//
// Created by Maddie on 12/3/2024.
//

#include "readresults.h"
#include "./gui/gui.h"
#include <stack>
#include <queue>
#include <vector>

// struct for handling basic structure of algorithm parts
struct Algo{
    std::string *artistPtr;
    std::string *songPtr;
    std::vector<std::string> *outputPtr;

    void algoFunction(){
        std::cout << "Running Analysis\n";
        std::cout << "Inputted String: \"" << *(artistPtr) << " : " << (*songPtr) << "\"\n";

        runscript((*artistPtr), (*songPtr));
        (*outputPtr) = readResults();
    }

    Algo(){
        artistPtr = new std::string("");
        songPtr = new std::string("");
        outputPtr = new std::vector<std::string>;
    }
};

struct TreeNode {
    std::string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(std::string val) : value(val), left(nullptr), right(nullptr) {}
};

TreeNode* makeBST(const std::vector<std::string>& sortedList, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end- start) / 2;
    TreeNode* root = new TreeNode(sortedList[mid]);
    root->left = makeBST(sortedList, start, mid - 1);
    root->right = makeBST(sortedList, mid + 1, end);
    return root;
}

TreeNode* helpMakeBST(const std::vector<std::string>& sortedList) {
    return makeBST(sortedList, 0, sortedList.size() - 1);
}

void printInOrder(TreeNode* root) {
    if (!root) return;
    printInOrder(root->left);
    std::cout << root->value << " ";
    printInOrder(root->right);
}
std::vector<std::string> bfsTraverse(TreeNode* root) {
    std::vector<std::string> res;
    if(!root) return res;
    std::queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        res.push_back(current->value);
        if(current->left) {
            q.push(current->left);
        } if (current->right) {
            q.push(current->right);
        }
    }
    return res;
}
std::vector<std::string> dfsTraverse(TreeNode*root ) {
    std::vector<std::string> res;
    if(!root) return res;\
    std::stack<TreeNode*> st;
    st.push(root);

    while(!st.empty()) {
        TreeNode* current = st.top();
        st.pop();
        res.push_back(current->value);

        if (current->right) {
            // pre order dfs
            st.push(current->right);
        } if (current->left) {
            st.push(current->left);
        }
    }
    return res;
}


int main() {

    GUI &gui = GUI::getInstance();
    Algo *algo = new Algo();

    // where the gui should write the user inputs
    gui.setInputPtrs(algo->artistPtr, algo->songPtr);

    // what the search button does
    gui.setSearchButtonFunction([&]() {
        algo->algoFunction();
    });

    // where the gui should get its output contents from
    gui.setOutputListPtr(algo->outputPtr);

    // gui will return exit codes
    int status = gui.run();
    return status;
}