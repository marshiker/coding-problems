#include <cassert>
#include "RateLimiter.h"

int main(int argc, char *argv[]) {
	RateLimiter rl(5, 5);
	assert(rl.isRateLimiterOK(1) == true);
	assert(rl.isRateLimiterOK(2) == true);
	assert(rl.isRateLimiterOK(3) == true);
	assert(rl.isRateLimiterOK(4) == true);
	assert(rl.isRateLimiterOK(5) == true);
	assert(rl.isRateLimiterOK(6) == true);
	//old element should be popped
	assert(rl.getCountInWindow() == 5);
	
	assert(rl.isRateLimiterOK(8) == true);
	//timestamps until 3 should be popped
	assert(rl.getCountInWindow() == 4);
	
	assert(rl.isRateLimiterOK(8) == true);
	//although time window not breached, N is breached
	assert(rl.isRateLimiterOK(8) == false);
	assert(rl.getCountInWindow() == 5);
	
	return 0;
}