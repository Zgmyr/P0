#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include "tree.h"

using namespace std;

static void exitError(string);
static bool sanitizeToken(string&);
static void validateCin(ofstream&);
static void validateArgvFile(const char*, ofstream&);

int main(int argc, char* argv[]) {

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
		cout << "Enter numeric data (EOF: Ctrl+Z then ENTER on Windows, Ctrl+D on Linux): ";
		validateCin(tempFile);
	}
	else {
		// read from file argv[1]
		validateArgvFile(argv[1], tempFile);
	}

	cout << "Data sanitized and saved to \'valid_data.fs26s2\' temporary file\n";

	// close writing to file & reopen for reading
	tempFile.close();
	ifstream readFile("valid_data.fs26s2");

	// build BST from sanitized read file
	node_t* root = buildTree(readFile);
	
	// output BST pre/postorder traversal to file
	if (!printPreorder(root, argv[1]))
		cout << "Failed to generate .preorder output file\n";

	if (!printPostorder(root, argv[1]))
		cout << "Failed to generate .postorder output file\n";
	
	// cleanup allocated node_t* structures
	destroyTree(root);
	root = nullptr;

	return 0;
}

static void exitError(string s) {
	cout << s << endl;
	exit(1);
}

/** sanitizeToken
 * Given a string token, validates it is numeric then sanitizes it
 * returns true when all characters are digits, false otherwise
 * removes any leading zeros by modifying given token string
 */
static bool sanitizeToken(string& token) {
	
	// check whether a non-digit character exists
	for (auto c : token) {
		if (!isdigit(c)) {
			cout << "[X] rejected invalid datum \'" << token << "\'\n";
			return false;
		}
	}

	// trim any leading zero's from token
	int sanitizedToken = stoi(token, nullptr);
	token = to_string(sanitizedToken);

	// all characters are digits
	return true;
}

/** validateCin
 * Given an opened output file stream
 * reads lines of standard input (via keyboard/redirection) until EOF (^Z)
 * sanitizes numeric-only tokens and writes them to output file stream
*/
static void validateCin(ofstream& outFS) {
	string line;

	// read standard user input until EOF (^Z)
	while (getline(cin,line)) {
		stringstream ss(line);
		string token;

		// split line into tokens
		while (ss >> token) {
			// validate tokens & write to temp file
			if (sanitizeToken(token))
				outFS << token << " ";
		}
	}
}

/** validateArgvFile
 * Given a file name (argv[1]) + an opened output file stream
 * opens filename.fs26s2 for reading & validates opened successfully
 * reads tokens from opened filename.fs26s2 until EOF
 * sanitizes numeric-only tokens and writes them to output file stream
*/
static void validateArgvFile(const char* arg, ofstream& outFS) {
	string filename = string(arg) + ".fs26s2";
	string token;
	
	// open file from argument & validate
	ifstream argvFile(filename);
	if (!argvFile)
		exitError("File \'"+filename+"\' does not exist, or could not be opened");

	cout << "Reading data from \'" << filename << "\'...\n";

	// read tokens from argument file until EOF
	while (argvFile >> token) {
		// validate tokens & write to temp file
		if (sanitizeToken(token))
			outFS << token << " ";
	}
}
