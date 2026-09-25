#include "tree.h"

using namespace std;

static node_t* insertDatum(node_t*, string);
static void traversePreorder(const node_t*, int, ofstream&);
static void traversePostorder(const node_t*, int, ofstream&);


/** buildTree
 * given an input file stream, responsible for constructing BST.
 * first pass collects unique datums from tokens stored in given file
 * second pass inserts each of these collected unique datums into BST
 */
node_t* buildTree(ifstream& file) {

    // 1st pass: building container of unique datums
    vector<string> uniqueDatums;
    string datum;

    // extract each token from validated data file
    while (file >> datum) {

        // check if datum has been recorded yet
        bool isUnique = true;
        for (int i = 0; i < uniqueDatums.size(); i++) {
            if (uniqueDatums[i] == datum) {
                isUnique = false;
                break;
            }
        }

        // add only unique datusms
        if (isUnique) {
            uniqueDatums.push_back(datum);
        }
    }

    // 2nd pass: building BST in preserved order w/ key = datum-length
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
 * generates output file with .preorder extention using base filename (or "out" for no argv[1])
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
 * generates output file with .postorder extention using base filename (or "out" for no argv[1])
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
 * given a root node ptr, inserts datum into appropriate node of BST
 * where BST key = datum length (number of digits).
 * recursively searches child subtrees until finding the corresponding
 * node with key == datum's length, or creates a node if one does not exist
 */
static node_t* insertDatum(node_t* root, string datum) {
    // base case, if node does not exist create one and return it
    if (root == nullptr) {
        root = new node_t;
        root->key = datum.length();
        root->datums.push_back(datum);
        return root;
    }
    
    // matching case, subtree root has the key of the current datum length
    if (datum.length() == root->key) {
        root->datums.push_back(datum);
        return root;
    }

    // recursive cases, search the appropriate child subtree
    if (datum.length() < root->key) {
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