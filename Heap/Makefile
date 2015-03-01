CXX=clang++
CXXFLAGS=-O3 -Werror -Weverything -Wpedantic -Wno-c++98-compat -std=c++11

test: test_heap
	./test_heap

test_heap: test_heap.cc

clean:
	rm -f test_heap
