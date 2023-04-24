
#include "heap.hpp"
#include <iostream>

using namespace std;

bool cmp(int v1, int v2) {
    return v1 < v2;
}

int main() {
    Heap<int> *heap = new Heap<int>(cmp);
    int value;
    while(1) {
        cout << "enter your value (type: int, enter 0 to quit and print):" << endl;
        cin >> value;
        if (!value) break;
        heap->insert(value);
        // heap->printTree();
    }
    heap->print();
}