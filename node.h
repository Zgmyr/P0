/**
 * node.h
 * Zachary Gmyr
 * CS4280 - Program Translation Project
 * 09/25/2026
 * 
 * Defines the node_t structure used to represent nodes in BST
 */

#ifndef NODE_H
#define NODE_H

#include <vector>

struct node_t {
    int key = 0;
    std::vector<std::string> datums;
    node_t* left = nullptr;
    node_t* right = nullptr;
};

#endif