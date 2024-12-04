//
// Created by kiand on 12/4/2024.
//
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#ifndef PROJECT_3_COP3530_SEARCHES_H
#define PROJECT_3_COP3530_SEARCHES_H

struct TreeNode {
    std::string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(std::string val);
};

TreeNode* makeBST(const std::vector<std::string>& sortedList, int start, int end);
TreeNode* helpMakeBST(const std::vector<std::string>& sortedList);
void printInOrder(TreeNode* root);
std::vector<std::string> bfsTraverse(TreeNode* root);
std::vector<std::string> dfsTraverse(TreeNode* root);

#endif //PROJECT_3_COP3530_SEARCHES_H
