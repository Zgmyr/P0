#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <fstream>

struct datumCount {
    std::string datum;
    int frequency;
};

struct node_t {
    int key;
    std::vector<std::string> datums;
};

node_t* buildTree(std::ifstream&);

#endif