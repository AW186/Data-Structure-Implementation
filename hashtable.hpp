
#ifndef HASHTABLE
#define HASHTABLE

#include<stdlib.h>
#include<stdio.h>
#include<string.h>


//ONLY FOR NON-ZERO KEYS
template<typename K, typename V>
class HashTable {
public:
    virtual void insert(K key, V value) = 0;
    virtual bool member(K key) = 0;
    virtual void print() = 0;
};

template<typename K, typename V>
class OpenHashTable: public HashTable<K, V> {
private:
    int (*hash)(K, int);
    V *values;
    K *keys;
    size_t size;
public:
    OpenHashTable(int (*hashfunc)(K, int), size_t s) {
        hash = hashfunc;
        size = s;
        values = (V *)malloc(size * sizeof(V));
        bzero(values, size * sizeof(V));
        keys = (K *)malloc(size * sizeof(K));
        bzero(keys, size * sizeof(K));
    }
    virtual void insert(K key, V value) {
        int hashValue;
        for (int j = 0; j < size && keys[hashValue = hash(key, j)] != key; j++) {
            if (!keys[hashValue]) {
                keys[hashValue] = key;
                values[hashValue] = value;
                return;
            }
        }
        printf("Can't insert, hashtable is full");
    }
    virtual bool member(K key) {
        int hashValue;
        for (int j = 0; j < size && keys[hashValue = hash(key, j)]; j++) {
            if (keys[hashValue] == key) true;
        }
        return false;
    }
    virtual void print() {
        for (int i = 0; i < size; i++) {
            printf("%d: %d\n", i, values[i]);
        }
    }
};

template<typename K, typename V>
class Node {
public:
    Node *next = NULL;
    V value;
    K key;
    Node(K k, V v) {
        value = v;
        key = k;
    }
};

template<typename K, typename V>
class ChainedHashTable: public HashTable<K, V> {
private:
    int (*hash)(K);
    int size;
    Node<K, V> **nodes;
public:
    ChainedHashTable(int (*hashfunc)(K), size_t s) {
        hash = hashfunc;
        size = s;
        nodes = (Node<K, V> **)malloc(size * sizeof(Node<K, V> *));
        bzero(nodes, size * sizeof(Node<K, V> *));
    }
    virtual void insert(K key, V value) {
        int hashValue = hash(key);
        for (Node<K, V> *current = nodes[hashValue]; current; current = current->next) {
            if (current->key == key) return;
        }
        Node<K, V> *node = new Node<K, V>(key, value);
        node->next = nodes[hashValue];
        nodes[hashValue] = node;
    }
    virtual bool member(K key) {
        int hashValue = hash(key);
        for (Node<K, V> *current = nodes[hashValue]; current; current = current->next) {
            if (current->key == key) return true;
        }
        return false;
    }
    virtual void print() {
        for (int i = 0; i < size; i++) {
            printf("%d:", i);
            for (Node<K, V> *current = nodes[i]; current; current = current->next) {
                printf(" (%d, %d)", current->key, current->value);
            }
            printf("\n");
        }
    }
};

#endif
