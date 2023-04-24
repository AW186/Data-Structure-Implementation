#include "rbtree.hpp"
#include <iostream>

using namespace std;

bool cmp(int a, int b) { 
    return a > b;
}

int main() {
    RBTree<int> *t = new RBTree<int>(cmp);
    int val;
    while(1) {
        cout << "insert (type int, 0 to exit and print): " << endl;
        cin >> val;
        if (val == 0) break;
        t->insert(val);
    }
    cout << "height: " << t->height() << endl; 
    t->inorderPrint();
    return 0;
}