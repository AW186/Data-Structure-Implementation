
#ifndef RBTREE
#define RBTREE

#include <iostream>

#define BLACK 0
#define RED 1
#define GRANDPA(z) (z->parent->parent)
#define MAX(a, b) (a > b ? a : b)

using namespace std;

template<typename T>
class Node {
public: 
    T val;
    bool color;
    Node<T> *left = NULL;
    Node<T> *right = NULL;
    Node<T> *parent = NULL;
    Node (T v) {
        val = v;
    }
    void rightLink(Node<T> *node) {
        this->right = node;
        if (node) node->parent = this;
    }
    void leftLink(Node<T> *node) {
        this->left = node;
        if (node) node->parent = this;
    }
};

template<typename T>
class RBTree {
private:
    Node<T> *root;
    bool (* cmp)(T, T);
    void leftRotate(Node<T> **node) {
        cout << "rotate left" << endl;
        Node<T> *x = *node;
        if (!x->right) return;
        Node<T> *y = x->right;
        Node<T> *xnewright = y->left;
        y->leftLink(x);
        x->rightLink(xnewright);
        *node = y;
    }
    void rightRotate(Node<T> **node) {
        cout << "rotate right" << endl;
        Node<T> *x = *node;
        if (!x->left) return;
        Node<T> *y = x->left;
        Node<T> *xnewleft = y->right;
        y->rightLink(x);
        x->leftLink(xnewleft);
        *node = y;
    }

    bool fix(Node<T> *z) {
        cout << "fixing" << endl;
        return !z->parent || !GRANDPA(z) || 
            tryCase1(z) || tryCase2(z) || tryCase3(z);
    }
    bool tryCase1(Node<T> *z) {
        cout << "case 1" << endl;
        if (GRANDPA(z)->left && GRANDPA(z)->right && \
            GRANDPA(z)->left->color && GRANDPA(z)->right->color) {
            GRANDPA(z)->left->color = BLACK;
            GRANDPA(z)->right->color = BLACK;
            GRANDPA(z)->color = RED;
            fix(GRANDPA(z));
            return true;
        } else return false;
    }
    bool tryCase2(Node<T> *z) {
        cout << "case 2" << endl;
        Node<T> *p = z->parent;
        Node<T> *g = GRANDPA(z);
        if (z == p->left && p == g->right) {
            cout << "case 2 right" << endl;
            rightRotate(&(g->right));
            tryCase3(p);
            return true;
        } else if (z == p->right && p == g->left) {
            cout << "case 2 left" << endl;
            leftRotate(&(g->left));
            tryCase3(p);
            return true;
        } else return false;
    }
    Node<T> **ref(Node<T> *z) {
        if (z->parent) {
            if (z->parent->left == z) return &z->parent->left;
            if (z->parent->right == z) return &z->parent->right;
        } return &root;
        cout << "structure ERROR" << endl;
        return NULL;
    }
    bool tryCase3(Node<T> *z) {
        cout << "case 3" << endl;
        Node<T> *p = z->parent;
        Node<T> *g = GRANDPA(z);
        if (z == p->left && p == g->left) {
            rightRotate(ref(g));
            p->color = BLACK;
            g->color = RED;
            return true;
        } else if (z == p->right && p == g->right) {
            leftRotate(ref(g));
            p->color = BLACK;
            g->color = RED;
            return true;
        } else return false;
    }

public:
    RBTree(bool (* func)(T, T)) {
        cmp = func;
    }
    void insert(T e) {
        Node<T> *node = new Node<T>(e);
        if (!root) {
            root = node;
            return;
        }
        node->color = RED;
        for (Node<T> *current = root; 1; ) {
            if (cmp(e, current->val)) {
                if (!current->left) {
                    current->leftLink(node);
                    break;
                } else current = current->left;
            } else if (!cmp(e, current->val)) {
                if (!current->right) {
                    current->rightLink(node);
                    break;
                } else current = current->right;
            }
        }
        fix(node);
        root->color = BLACK;
    }
    int height() {
        return height(root);
    }
    int height(Node<T> *node) {
        if (!node) return 0;
        int l = height(node->left), r = height(node->right);
        return MAX(l, r) + 1;
    }
    void inorderPrint() {
        cout << "In order: ";
        inorderPrint(root);
        cout << endl;
    }
    void inorderPrint(Node<T> *node) {
        if (node) {
            inorderPrint(node->left);
            cout << node->val << " ";
            inorderPrint(node->right);
        }
    }
    void printTree() {
        printTree(root, 0);
    }
    void printSpaces(int spaces) {
        for (int i = 0; i < spaces; i++) {
            cout << " ";
        }
    }
    void printTree(Node<T> *t, int spaces) {
        if (!t) return;
        printSpaces(spaces);
        if (t->color == RED) cout << "\033[1;31m" << t->val << "\033[0m" << endl;
        else cout << t->val << endl;
        printTree(t->left, spaces + 2);
        printTree(t->right, spaces + 2);
    }
};


#endif