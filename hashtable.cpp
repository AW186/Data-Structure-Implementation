#include "hashtable.hpp"
#include <iostream>

using namespace std;
#define HASHSIZE 20
int openhash(int val, int i) {
    return (val + i) % HASHSIZE;
}
int hashfunc(int val) {
    return (val) % HASHSIZE;
}
int main() {
    HashTable<int, int> *table;
    char c;
    cout << "Chained hash (reply 'C') or open hash (reply O) " << endl;
    cin >> c;
    if (c == 'C') {
        table = new ChainedHashTable<int, int>(hashfunc, HASHSIZE);
    } else if (c == 'O') {
        table = new OpenHashTable<int, int>(openhash, HASHSIZE);
    } else {
        return 0;
    }
    int key, value;
    while(1) {
        cout << "enter your key (type: int, enter 0 to quit and print):" << endl;
        cin >> key;
        if (!key) break;
        cout << "enter your value (type: int): " << endl;
        cin >> value;
        table->insert(key, value);
    }
    table->print();
}