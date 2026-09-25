/**
 * P0.cpp
 * Zachary Gmyr
 * CS4280 - Program Translation Project
 * 09/25/2026
 * 
 * Main driver for P0. Handles invocation by either standard input (keyboard/redirection) when no
 * argument is given, or base file name passed by argument. Validates nonnegative integers from input
 * data (stored in separate temp file) and constructs a binary search tree from validated datums.
 * BST is constructed from another source (see tree.cpp/.h) where the key is number of digits, ignoring
 * leading zeros. BST root uses a struct defined in a separate header (see node.h), and P0 handles
 * cleanup for dynamically allocated nodes in the BST.
 * 
 * Input file (if invoking with a file argument) should be named with extension '.fs26s2', though only
 * the base filename should be passed to P0.
 * 
 * Generates two files displaying BST traversal for preorder and postorder. Output files are named using
 * .preorder and .postorder extensions, respectively.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include "tree.h"

using namespace std;

static void exitError(string);
static bool isValidToken(string&);
static void validateCin(ofstream&);
static void validateArgvFile(const char*, ofstream&);

int main(int argc, char* argv[]) {
	string baseFilename = (argv[1] != nullptr)? string(argv[1]) : "out";

	// validate argument count
	if (argc > 2)
		exitError("Too many arguments were given");
	
	// file to store sanitized data
	ofstream tempFile("valid_data.fs26s2");
	if (!tempFile)
		exitError("Failed to open temp file for writing");
	
	// handle data validation + set up read file
	if (argc == 1) {
		// read from standard input
		cout << "Enter nonnegative integers separated by [space], then signal EOF when finished:\n"
			"(EOF: Ctrl+Z then ENTER on Windows, or Ctrl+D on Linux)\n";
		
		validateCin(tempFile);
	}
	else {
		// read from file argv[1]
		validateArgvFile(argv[1], tempFile);
	}

	cout << "Data validated and saved to \'valid_data.fs26s2\' temporary file\n";

	// close writing to file & reopen for reading
	tempFile.close();
	ifstream sanitizedInputFile("valid_data.fs26s2");

	// build BST from sanitized read file
	node_t* root = buildTree(sanitizedInputFile);
	cout << "Binary search tree constructed from valid datums\n";
	
	// output BST pre/postorder traversal to file
	if (!printPreorder(root, argv[1]))
		cout << "Failed to generate .preorder output file\n";
	else
		cout << "Generated file \'" << baseFilename + ".preorder" << "\' containing preorder traversal\n";
		
	if (!printPostorder(root, argv[1]))
		cout << "Failed to generate .postorder output file\n";
	else
		cout << "Generated file \'" << baseFilename + ".postorder" << "\' containing postorder traversal\n";
		
	// cleanup allocated node_t* structures
	destroyTree(root);
	root = nullptr;

	return 0;
}

static void exitError(string s) {
	cout << s << endl;
	exit(1);
}

/** isValidToken
 * Given a string token, validates that token contains digits only
 * returns true when all characters are digits, false otherwise
 */
static bool isValidToken(string& token) {
	
	// check whether a non-digit character exists
	for (auto c : token) {
		if (!isdigit(c)) {
			cout << "[X] rejected invalid datum \'" << token << "\'\n";
			return false;
		}
	}

	// all characters are digits
	return true;
}

/** validateCin
 * Given an opened output file stream
 * reads lines of standard input (via keyboard/redirection) until EOF (^Z)
 * validates nonnegative integer tokens and writes them to output file stream
*/
static void validateCin(ofstream& outFS) {
	string line;

	// read standard user input until EOF (^Z)
	while (getline(cin,line)) {
		stringstream ss(line);
		string token;

		// split line into tokens, write valid tokens to temp file
		while (ss >> token) {
			if (isValidToken(token))
				outFS << token << " ";
		}
	}
}

/** validateArgvFile
 * Given a file name (argv[1]) + an opened output file stream
 * opens filename.fs26s2 for reading & validates opened successfully
 * reads tokens from opened filename.fs26s2 until EOF
 * validates nonnegative integer tokens and writes them to output file stream
*/
static void validateArgvFile(const char* arg, ofstream& outFS) {
	string filename = string(arg) + ".fs26s2";
	string token;
	
	// open file from argument & validate
	ifstream argvFile(filename);
	if (!argvFile)
		exitError("File \'"+filename+"\' does not exist, or could not be opened");

	cout << "Reading data from \'" << filename << "\'...\n";

	// read tokens from argument file until EOF, write vallid ones to temp file
	while (argvFile >> token) {
		if (isValidToken(token))
			outFS << token << " ";
	}
}
