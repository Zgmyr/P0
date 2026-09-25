/**
 * tree.cpp
 * Zachary Gmyr
 * CS4280 - Program Translation Project
 * 09/25/2026
 * 
 * Implements binary search tree construction, insertion, traversal output, and destruction. Expects
 * data to be passed as a file, containing only nonnegative integers, where BST key is the number of
 * digits in a datum AFTER ignoring any leading zeros. Datums are grouped by digit-count key while
 * preserving unique datums in the order by which they are read from the input file. Nodes are defined
 * in a separate header (see node.h).
 */

#include "tree.h"

using namespace std;

static node_t* insertDatum(node_t*, string);
static void traversePreorder(const node_t*, int, ofstream&);
static void traversePostorder(const node_t*, int, ofstream&);


/** buildTree
 * given an input file stream, responsible for constructing BST where
 * the input file is expected to contain only nonnegative integers.
 * first pass collects unique datums from tokens stored in given file,
 * second pass inserts each of these collected unique datums into BST
 */
node_t* buildTree(ifstream& validDataFile) {

    // 1st pass: building container of unique datums
    vector<string> uniqueDatums;
    string datum;

    // extract each token from validated data file
    while (validDataFile >> datum) {

        // check if datum has been recorded yet
        bool isUnique = true;
        for (int i = 0; i < uniqueDatums.size(); i++) {
            if (uniqueDatums[i] == datum) {
                isUnique = false;
                break;
            }
        }

        // add only unique datums
        if (isUnique) {
            uniqueDatums.push_back(datum);
        }
    }

    // 2nd pass: build BST in preserved order, ignoring leading zeros for key
    node_t* root = nullptr;

    for (const auto& datum : uniqueDatums) {
        root = insertDatum(root, datum);
    }

    // return root pointer
    return root;
}

/** destroyTree
 * destroys dynamically allocated node_t nodes in
 * BST using post-order traversal
 */
void destroyTree(node_t* root) {
    // base case, end of subtree
    if (root == nullptr)
        return;
    
    // recursive case, destroy left subtree
    destroyTree(root->left);

    // recursive case, destroy right subtree
    destroyTree(root->right);

    // delete subtree root as recursion unwinds
    delete root;
}

/** printPreorder
 * given a root node to a BST and base filename passed to P0 by argv[1]
 * generates output file with .preorder extension using base filename (or "out" for no argv[1])
 * uses static helper function to traverse BST in preorder & write node info to output file
 */
bool printPreorder(const node_t* root, const char* baseFilename) {
    // set output filename based on P0 argument (if exists)
    string outFilename = (baseFilename != nullptr) ? string(baseFilename)+".preorder" : "out.preorder";

    // open output file & validate successfully opened
    ofstream outFile(outFilename);

    if (!outFile)
        return false;
    
    // traverse BST by preorder & print to outFile
    traversePreorder(root, 0, outFile);

    return true;
}

/** printPostorder
 * given a root node to a BST and base filename passed to P0 by argv[1]
 * generates output file with .postorder extension using base filename (or "out" for no argv[1])
 * uses static helper function to traverse BST in postorder & write node info to output file
 */
bool printPostorder(const node_t* root, const char* baseFilename) {
    // set output filename based on P0 argument (if exists)
    string outFilename = (baseFilename != nullptr) ? string(baseFilename)+".postorder" : "out.postorder";

    // open output file & validate successfully opened
    ofstream outFile(outFilename);
    
    if (!outFile)
        return false;
    
    // traverse BST by postorder & print to outFile
    traversePostorder(root, 0, outFile);

    return true;
}

/* HELPER FUNCTIONS */

/** insertDatum
 * given a root node ptr, inserts validated integer datum into appropriate node of BST
 * BST key = number of digits AFTER ignoring leading zeros
 * recursively searches child subtrees until finding a node with the same key,
 * or creates a new node if one does not exist
 */
static node_t* insertDatum(node_t* root, string datum) {
    // calculate digit-count key AFTER ignoring leading zeros
    string trimmedDatum = to_string(stoi(datum,nullptr));

    // base case, if node does not exist create one and return it
    if (root == nullptr) {
        root = new node_t;
        root->key = trimmedDatum.length();
        root->datums.push_back(datum);
        return root;
    }
    
    // matching case, subtree root has the same digit-count key
    if (trimmedDatum.length() == root->key) {
        root->datums.push_back(datum);
        return root;
    }

    // recursive cases, search the appropriate child subtree
    if (trimmedDatum.length() < root->key) {
        root->left = insertDatum(root->left, datum);
    }
    else
        root->right = insertDatum(root->right, datum);
    
    // return subtree root as recursion unwinds
    return root;
}

/** traversePreorder
 * helper func for printPreorder, initally given root node, level 0, and output file
 * uses recursion to traverse BST by preorder and writes node contents to output file
 */
static void traversePreorder(const node_t* root, int level, ofstream& outFile) {
    // base case, end of subtree
    if (root == nullptr)
        return;
    
    // write subtree root to output file
    outFile << string(level * 2, ' ') << "=" << root->key << ": ";
    for (const auto& datum : root->datums) {
        outFile << datum << " ";
    }
    outFile << "\n";

    // recursive cases, traverse left/right subtrees
    traversePreorder(root->left, level + 1, outFile);
    traversePreorder(root->right, level + 1, outFile);
}

/** traversePostorder
 * helper func for printPostorder, initally given root node, level 0, and output file
 * uses recursion to traverse BST by postorder and writes node contents to output file
 */
static void traversePostorder(const node_t* root, int level, ofstream& outFile) {
    // base case, end of subtree
    if (root == nullptr)
        return;
    
    // recursive cases, traverse left/right subtrees
    traversePostorder(root->left, level + 1, outFile);
    traversePostorder(root->right, level + 1, outFile);

    // write subtree root to output file
    outFile << string(level * 2, ' ') << "=" << root->key << ": ";
    for (const auto& datum : root->datums) {
        outFile << datum << " ";
    }
    outFile << "\n";

}