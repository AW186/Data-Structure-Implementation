all: hashtable heap

hashtable: hashtable.cpp hashtable.hpp
	g++ -o hashtable hashtable.cpp

heap: heap.cpp heap.hpp
	g++ -o heap heap.cpp

clear:
	rm hashtable
	rm heap