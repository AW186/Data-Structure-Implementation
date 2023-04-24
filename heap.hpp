#ifndef HEAP
#define HEAP

#include<stdlib.h>
#include<string.h>
#include<iostream>

#define INIT_LEN 10
#define LEFT(i) (i * 2 + 1)
#define RIGHT(i) (i * 2 + 2)
#define PARENT(i) ((i - 1) / 2)

using namespace std;

template<typename T>
class Heap {
private:
    //return true if second is greater than first
    bool (* cmp)(T, T);
    T *array;
    int size;
    int limit;
    void shrink() {
        if (limit <= INIT_LEN) return;
        T *temp = array;
        limit /= 2;
        array = (T *)malloc(limit * sizeof(T));
        memcpy(array, temp, size * sizeof(T));
    }
    void expand() {
        T *temp = array;
        limit *= 2;
        array = (T *)malloc(limit * sizeof(T));
        memcpy(array, temp, size * sizeof(T));
    }
    void swap(int i, int j) {
        auto temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    void siftDown(int i) {
        if (i > size) return;
        int max = i;
        if (LEFT(i) < size && cmp(array[max], array[LEFT(i)])) max = LEFT(i);
        if (RIGHT(i) < size && cmp(array[max], array[RIGHT(i)])) max = RIGHT(i);
        if (i == max) return;
        swap(i, max);
        siftDown(max);
    }
    void siftUp(int i) {
        if (i == 0) return;
        if (cmp(array[PARENT(i)], array[i])) {
            swap(i, PARENT(i));
            siftUp(PARENT(i));
        }
    }
public:
    Heap(bool (* func)(T, T)) {
        cmp = func;
        array = (T *)malloc(INIT_LEN * sizeof(T));
        size = 0;
        limit = INIT_LEN;
    }
    void insert(T element) {
        if (size == limit) expand();
        array[size++] = element;
        siftUp(size-1);
    }
    T extract() {
        // if (size < limit / 4) shrink();
        T val = array[0];
        swap(size-1, 0);
        size--;
        siftDown(0);
        return val;
    }
    void printTree() {
        int num = 1;
        cout << "heap: " << endl;
        for(int i = 0; i < size; ) {
            for (int j = 0; j < num && i < size; j++, i++) {
                cout << array[i] << " ";
            }
            num *= 2;
            cout << endl;
        }
    }
    void print() {
        cout << "sorted ouput:";
        while (size) {
            cout << " " << extract();
        }
        cout << endl;
    }
};

#endif