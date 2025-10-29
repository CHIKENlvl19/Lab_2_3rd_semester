#pragma once

#include "binaryTree.h"
#include "nodeArray.h"
#include <cstring>

using namespace std;

class Huffman {
private:
    BinaryTree::Node* root; // корень дерева Хаффмана

public:
    Huffman() : root(nullptr) {}

    ~Huffman() {
        freeTree(root);
    }

    
    void countFrequencies(const char* text, int* freqTable) {
        for (int i = 0; i < 256; ++i)
        {
            freqTable[i] = 0;
        }

        for (int i = 0; text[i] != '\0'; ++i)
        {
            freqTable[(unsigned char)text[i]]++;
        }
    }

    
    void build(const char* text) {
        int freq[256];
        countFrequencies(text, freq);

        NodeArray<BinaryTree::Node> nodes;

        // создаём узлы для всех встречающихся символов
        for (int i = 0; i < 256; ++i) {
            if (freq[i] > 0)
            {
                nodes.add(new BinaryTree::Node((char)i, freq[i]));
            }
        }

        // пока не останется один узел
        while (nodes.getSize() > 1)
        {
            BinaryTree::Node* left = nodes.extractMin();
            BinaryTree::Node* right = nodes.extractMin();

            BinaryTree::Node* parent = new BinaryTree::Node('\0', left->freq + right->freq);
            parent->left = left;
            parent->right = right;

            nodes.add(parent);
        }

        root = nodes.extractMin(); // последний узел — корень дерева
    }

    
    void buildCodes(BinaryTree::Node* node, char* code, int depth, char codes[256][32]) {
        if (!node) return;

        // если лист — сохранить код
        if (!node->left && !node->right && node->symbol != '\0') 
        {
            code[depth] = '\0';
            strcpy(codes[(unsigned char)node->symbol], code);
            return;
        }

        // идти влево (0)
        code[depth] = '0';
        buildCodes(node->left, code, depth + 1, codes);

        // идти вправо (1)
        code[depth] = '1';
        buildCodes(node->right, code, depth + 1, codes);
    }

    void encode(const char* text, char* encoded) {
        if (!root) return;

        char codes[256][32];
        for (int i = 0; i < 256; ++i)
        {
            codes[i][0] = '\0';
        }
            
        char tempCode[32];
        buildCodes(root, tempCode, 0, codes);

        encoded[0] = '\0';
        for (int i = 0; text[i] != '\0'; ++i)
        {
            strcat(encoded, codes[(unsigned char)text[i]]);
        } 
    }

    void decode(const char* encoded, char* decoded) {
        if (!root) return;

        int decodedIndex = 0;
        BinaryTree::Node* current = root;

        for (int i = 0; encoded[i] != '\0'; ++i) 
        {
            if (encoded[i] == '0')
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            } 

            if (!current->left && !current->right) 
            {
                decoded[decodedIndex++] = current->symbol;
                current = root;
            }
        }
        decoded[decodedIndex] = '\0';
    }

    BinaryTree::Node* getRoot() {
        return root;
    }

private:
    void freeTree(BinaryTree::Node* node) {
        if (!node)
        {
            return;
        } 

        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
};