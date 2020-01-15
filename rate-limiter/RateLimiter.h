#include <deque>

class RateLimiter {
public:
	RateLimiter(int N, int T) : _numMsgs(N), _timeWindow(T) {
	}
	
	bool isRateLimiterOK(uint64_t ts) {
		if (_dq.empty()) {
			_dq.push_front(ts);
			return true;
		}
		
		while (!_dq.empty() && (ts - _dq.back() >= _timeWindow)) {
			_dq.pop_back();
		}
		
		if (_dq.size() < _numMsgs) {
			_dq.push_front(ts);
			return true;
		}
		
		return false;
	}
	
	int getCountInWindow() {
		return _dq.size();
	}
	
private:
	std::deque<uint64_t> _dq;
	int _numMsgs;
	int _timeWindow;	
};
