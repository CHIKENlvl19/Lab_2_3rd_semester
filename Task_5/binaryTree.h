#pragma once

#include <iostream>

using namespace std;

class BinaryTree {
public:
    struct Node {
        char symbol;
        int freq;
        Node* left;
        Node* right;

        Node(char s, int f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

    Node* insert(Node* node, char symbol, int freq) {
        if (node == nullptr)
        {
            return new Node(symbol, freq);
        }

        if (freq < node->freq)
        {
            node->left = insert(node->left, symbol, freq);
        }
            
        else
        {
            node->right = insert(node->right, symbol, freq);
        }

        return node;
    }

    void preorder(Node* node) const {
        if (node == nullptr)
        {
            return;
        } 

        cout << node->symbol << "(" << node->freq << ") ";
        preorder(node->left);
        preorder(node->right);
    }

    void freeTree(Node* node) {
        if (node == nullptr)
        {
            return;
        } 
        
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { freeTree(root); }

    void insert(char symbol, int freq) {
        root = insert(root, symbol, freq);
    }

    void printPreorder() const {
        preorder(root);
        cout << endl;
    }

    void clear() {
        freeTree(root);
        root = nullptr;
    }

    Node* getRoot() const {
        return root;
    }
};