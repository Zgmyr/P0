/**
 * tree.h
 * Zachary Gmyr
 * CS4280 - Program Translation Project
 * 09/25/2026
 * 
 * Declares the public BST operations used by P0 driver
 */

#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "node.h"

node_t* buildTree(std::ifstream&);

void destroyTree(node_t*);

bool printPreorder(const node_t*, const char*);

bool printPostorder(const node_t*, const char*);

#endif