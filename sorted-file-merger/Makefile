CC=gcc
CXX=g++
FLAGS=-std=c++11
RM=rm -f
PROGS=merge

SRCS=merge.cpp SortedFileMerger.cpp

all: merge

merge: $(SRCS)
	$(CXX) $(FLAGS) $(SRCS) -o merge

clean:
	$(RM) $(PROGS)
