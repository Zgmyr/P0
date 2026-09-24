#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct node_t {
    int key = 0;
    std::vector<std::string> datums;
    node_t* left = nullptr;
    node_t* right = nullptr;
};

node_t* buildTree(std::ifstream&);

void destroyTree(node_t*);

void printPreorder(const node_t*, const char*);

void printPostorder(const node_t*, const char*);

#endif