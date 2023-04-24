all: hashtable heap rbtree

hashtable: hashtable.cpp hashtable.hpp
	g++ -o hashtable hashtable.cpp

heap: heap.cpp heap.hpp
	g++ -o heap heap.cpp

rbtree: rbtree.cpp rbtree.hpp
	g++ -o rbtree rbtree.cpp

clear:
	rm hashtable
	rm heap
	rm rbtree