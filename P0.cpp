#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>
// #include <cstdio>
#include "tree.h"

using namespace std;

static void exitError(string);
static bool isIntToken(const string&);
static void validateCin(ofstream&);
static void validateArgvFile(const char*, ofstream&);

int main(int argc, char* argv[]) {

	// validate argument count
	if (argc > 2)
		exitError("Too many arguments were given");

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


	// build container of string frequencies

	// possibly remove temporary file afterwards with:
	// remove("valid_data.fs26s2");

	// build the tree
	
	// output traversing the tree 3 ways to file


	return 0;
}

static void exitError(string s) {
	cout << s << endl;
	exit(1);
}

/** isIntToken
 * Given a string token & validates its representation as an integer
 * token is converted from string to integer value
 * returns false if token contains non-numeric characters
 * returns true if entire token converts to integer successfully
 */
static bool isIntToken(const string& token) {
	size_t pos;

	// try converting token to integer
	try {
		int numericVal = stoi(token, &pos);
		
		// failed to convert entire token to int
		if (pos != token.length()) {
			cout << "[X] rejected invalid datum \'" << token << "\'\n";
			return false;
		}
	}
	catch (invalid_argument) {
		// failed to convert token with starting characters
		cout << "[X] rejected invalid datum \'" << token << "\'\n";
		return false;
	}
	
	// entire token successfully converted
	return true;
}

/** validateCin
 * Given an opened output file stream
 * reads lines of standard input (via keyboard/redirection) until EOF (^Z)
 * sanitizes signed integer tokens and writes them to output file stream
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
			if (isIntToken(token))
				outFS << token << " ";
		}
	}
}

/** validateCin
 * Given a file name (argv[1]) + an opened output file stream
 * opens filename.fs26s2 for reading & validates opened successfully
 * reads tokens from opened filename.fs26s2 until EOF
 * sanitizes signed integer tokens and writes them to output file stream
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
		if (isIntToken(token))
			outFS << token << " ";
	}
}
