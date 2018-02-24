//
// Created by PetnaKanojo on 24/02/2018.
//

#include "stdbool.h"
#ifndef C_DESIGN_TRIETREE_H
#define C_DESIGN_TRIETREE_H

typedef int status;

#define OK 1
#define WRONG -1
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
struct TrieNode{
//    struct trieNode * front;
    struct TrieNode ** child;
    int childNum;
    bool isWord;
    char word[3];
};
typedef struct TrieNode *Node;

//typedef struct {
//    Node root;
//} TrieTree, *Tree;

Node createTrieTree(char * string);
#endif //C_DESIGN_TRIETREE_H
