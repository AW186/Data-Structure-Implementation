all: hashtable

hashtable: hashtable.cpp hashtable.hpp
	g++ -o hashtable hashtable.cpp