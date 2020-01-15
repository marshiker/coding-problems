CXX=g++
RM=rm -f
PROGS=throttler ut_rate_limiter

SRCS=throttle.cpp 
UT_SRCS=ut_RateLimiter.cpp

all: throttler ut_rate_limiter

throttler: $(SRCS)
	$(CXX) $(SRCS) -o $@

ut_rate_limiter: $(UT_SRCS)
	$(CXX) $(UT_SRCS) -o $@

clean:
	$(RM) $(PROGS)
