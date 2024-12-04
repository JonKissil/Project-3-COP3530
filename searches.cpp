//
// Created by kiand on 12/4/2024.
//

#include "searches.h"
TreeNode::TreeNode(std::string val) : value(val), left(nullptr), right(nullptr) {}

TreeNode* makeBST(const std::vector<std::string>& sortedList, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2;
    TreeNode* root = new TreeNode(sortedList[mid]);
    root->left = makeBST(sortedList, start, mid - 1);
    root->right = makeBST(sortedList, mid + 1, end);
    return root;
}
// wrapper
TreeNode* helpMakeBST(const std::vector<std::string>& sortedList) {
    return makeBST(sortedList, 0, sortedList.size() - 1);
}
// for testing
void printInOrder(TreeNode* root) {
    if (!root) return;
    printInOrder(root->left);
    std::cout << root->value << " ";
    printInOrder(root->right);
}

std::vector<std::string> bfsTraverse(TreeNode* root) {
    std::vector<std::string> res;
    if (!root) return res;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        res.push_back(current->value);
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }

    return res;
}

//  pre order DFS
std::vector<std::string> dfsTraverse(TreeNode* root) {
    std::vector<std::string> res;
    if (!root) return res;

    std::stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* current = st.top();
        st.pop();

        res.push_back(current->value);

        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }

    return res;
}