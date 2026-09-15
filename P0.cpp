#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static void readStdInput();

int main(int argc, char* argv[]) {

	ifstream inputFile;

	// process arguments & set up read file
	if (argc == 1) {
		// no args -> read from standard input
		readStdInput();
		inputFile.open("temp.fs26s2");
	}
	else {
		// read from file argument
		string filename = string(argv[1]) + ".fs26s2";

		inputFile.open(filename);

		if (!inputFile) {
			cout << "Failed to open file " << filename << endl;
			return 1;
		}
	}

	string testStr;
	getline(inputFile, testStr);

	cout << "first line read = " << testStr << endl;

	// build the tree
	

	// traverse the tree 3 ways


	return 0;
}

static void readStdInput() {
	ofstream tempFile("temp.fs26s2");

	string line;
	while (getline(cin, line)) {
		tempFile << line << "\n";
	}
}