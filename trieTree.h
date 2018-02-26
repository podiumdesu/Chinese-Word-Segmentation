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
    struct TrieNode ** child;
    int childNum;
    bool isWord;
    char word[4];
};
typedef struct TrieNode *Node;

/*************************************
 Function: buildDict
 Description: read the dict.txt and build the trie tree
 Input:
        root: createTrieTreeRoot()
        fileName: name of dict
 Return:
        void
***************************************/
void buildDict(Node root, char * fileName);

void buildTrieTree(Node root, char * string);
Node createTrieTreeRoot();
Node createTrieTree(char * string);
char * charcpy(char * str);

void writeTofile(Node root, char * fileName);


bool findNode (Node root, char * string);

void addNewNode (Node root, char * string, char * fileName);
void removeNode (Node root, char * string, char * fileName);
#endif //C_DESIGN_TRIETREE_H
