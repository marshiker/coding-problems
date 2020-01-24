#include "SortedFileMerger.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

bool SortedFileMerger::Merge(const std::string& inpDir, const std::vector<std::string>& inputFiles, const std::string& outputFile) {
	ofstream out;
	out.open(outputFile);
	if (!out) {
		cout << "Failed to open output file" << endl;
		return false;
	}
	
	priority_queue<Line, vector<Line>, LineComp> pq;
	vector<unique_ptr<ifstream> > ifps;
	int i=0;
	for (auto & f: inputFiles)
	{
		ostringstream filename;
		filename << inpDir << "/" << f;
		unique_ptr<ifstream> fp(new ifstream(filename.str()));
		if (!fp || !fp->is_open()) {
			cout << "Unexpected error opening input file " << filename.str() << " Exiting" << endl;
			return false;
		}
		string line;
		while (!fp->eof() && line.size()==0) {
			getline(*fp, line);
		}
		if (line.size() == 0) continue;

		ifps.push_back(move(fp));
		pq.push(Line(line, i));
		++i;
	}
	
	string last;
	ostringstream oss;
	string line;
	while (!pq.empty()) {
		if (pq.top().data != last) {
			oss << pq.top().data << "\n";
			last = pq.top().data;
		}
		line.clear();
		while (!ifps[pq.top().index]->eof() && line.size()==0) {
			getline(*ifps[pq.top().index], line);
		}
		int idx = pq.top().index;
		pq.pop();
		if (line.size() != 0) {
			pq.push(Line(line, idx));
		}
	}

	out << oss.str();
	
	return true;
}
