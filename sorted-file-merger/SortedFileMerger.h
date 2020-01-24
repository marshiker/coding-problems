#include <string>
#include <vector>
#include <memory>

class SortedFileMerger {
	struct Line {
		std::string data;
		int index;
		Line(std::string s, int index) : data(s), index(index) {}
	};

	struct LineComp {
		bool operator()(const Line& a, const Line& b) {
			return a.data > b.data;
		}
	};
public:
	static bool Merge(const std::string& inpDir, const std::vector<std::string>& inputFiles, const std::string& outputFile); 
};