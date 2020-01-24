#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include "SortedFileMerger.h"
using namespace std;

static bool getInputFiles(const string& dirName, vector<string>& inputFiles)
{
	DIR* dirp = opendir(dirName.c_str());
	if (dirp == nullptr) return false;
	
	struct dirent * dp;
	while ((dp = readdir(dirp)) != NULL) {
		if (string(dp->d_name) == "." || string(dp->d_name) == "..") continue;
		inputFiles.push_back(dp->d_name);
	}
	closedir(dirp);
	return true;
}

static void verifyInputFiles(const string& dirName, vector<string>& inputFiles) {
	string filePath; filePath.reserve(128);
	vector<string> goodFiles; goodFiles.reserve(100);
	string line; line.reserve(256);
	string lastLine; lastLine.reserve(256);
	
	for (auto & fname: inputFiles) {
		ifstream inp;
		filePath = dirName+"/"+fname;
		inp.open(filePath);
		if (!inp) {
			cout << "Unable to open file " << filePath << " Ignoring file" << endl;
			continue;
		}
		
		line.clear(); lastLine.clear();
		bool goodFile = true;
		while (getline(inp, line)) {
			if (line.size() == 0) continue;
			if (lastLine.size() > 0 && line < lastLine) {
				cout << "File " << filePath << "  is not sorted. Ignoring file" << endl;
				goodFile = false;
				break;
			}
			lastLine = line;
		}
		
		if (lastLine.size() == 0) {
			cout << "File " << filePath << " has only empty lines. Ignoring file" << endl;
		}
		
		if (goodFile && lastLine.size() > 0)
			goodFiles.push_back(fname);	
	}
	
	inputFiles = goodFiles;
	cout << "Files to be merged: count=" << inputFiles.size() << endl;
	for (auto & f: inputFiles) {
		cout << f << endl;
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "Usage: ./merge <input-dir-path> <output_file_name>" << endl;
		exit(1);
	}
	
	vector<string> inputFiles;
	inputFiles.reserve(100);
	string inpDir(argv[1]);
	if (!getInputFiles(inpDir, inputFiles)) {
		cout << "Failed opening input directory" << endl;
		exit(1);
	}
	
	ofstream output;
	string outputFile(argv[2]);
	output.open(outputFile);
	if (!output) {
		cout << "Failed to open output file" << endl;
		exit(1);
	}
	output.close();
	
	//process each file to see if it is sorted, otherwise ignore the file
	verifyInputFiles(inpDir, inputFiles);
	if (inputFiles.size() == 0) {
		return 0;
	}
	
	// Merge Utility class
	if (SortedFileMerger::Merge(inpDir, inputFiles, outputFile)) {
		cout << "Valid Input Files merged successfully" << endl;
	}
	else {
		cout << "Errors merging files...check program output on stdout" << endl;
	}
	
	return 0;
}