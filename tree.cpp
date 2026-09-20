#include "tree.h"


using namespace std;

node_t* buildTree(ifstream& file) {

    // 1st pass: building container of unique datums & their frequencies
    vector<datumCount> uniqueDatums;
    string datum;

    // extract each token from validated data file
    while (file >> datum) {
        // find the index of a datum in unique container, if exists
        int datumIdx = -1;

        for (int idx = 0; idx < uniqueDatums.size(); idx++) {
            if (uniqueDatums[idx].datum == datum) {
                datumIdx = idx;
                break;
            }
        }

        // update frequency if datum exists, otherwise add unique datum
        if (datumIdx != -1)
            uniqueDatums[datumIdx].frequency++;
        else
            uniqueDatums.push_back({datum, 1});
    }

    // 2nd pass: building BST in preserved order w/ key = datum-length
    node_t* root = nullptr;

    /* WIP:
    *   next build BST using uniqueDatums vector
    */

    // return root pointer
    return root;
}
