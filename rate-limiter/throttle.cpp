#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <cerrno>
using namespace std;

#include "RateLimiter.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage: ./throttler <input-file-path>" << endl;
		exit(1);
	}
	
	ifstream inp(argv[1]);
	if (!inp.is_open()) {
		cout << "Unable to open input file " << argv[1] << endl;
		exit(1);
	}
	
	int N=0, T=0;
	if (inp >> N >> T)
	{
		inp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else {
		cout << "First line format wrong in input file" << endl;
		exit(1);
	}
	
	RateLimiter rl(N, T);
	string line;
	uint64_t ts=0;
	while (getline(inp, line)) {
		//ignore empty lines
		if (line.size() == 0) continue;
		ts = strtoull(line.c_str(), NULL, 10);
		if (ts == 0 || errno == ERANGE) {
			errno = 0;
			cout << "Warning: timestamp out of range or could not be converted to uint64_t for " << line << "\n";
			continue;
		}
		
		if (rl.isRateLimiterOK(ts)) {
			cout << ts << " pass\n";
		}
		else {
			cout << ts << " fail\n";
		}
	}
	
	cout.flush();
	return 0;		
}