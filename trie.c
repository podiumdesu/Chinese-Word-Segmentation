//
// Created by PetnaKanojo on 12/02/2018.
//

#include "mylib.h"
#include "mystd.h"
#include "trieTree.h"
#include <string.h>

//Tree initEntry() {
//    ptree = (Tree)malloc(sizeof(struct TrieTree));
//    if (ptree)
//        ptree->root = NULL;
//    return ptree;
//}

Node initTrieTreeNode(char * word, bool isWord) {
    Node pnode = (Node)malloc(sizeof(struct TrieNode));
    if (pnode) {
        strcpy(pnode->word, word);
        pnode->isWord = isWord;
        pnode->child = NULL;
        pnode->childNum = 0;
    }
    return pnode;
}

Node buildTreeNode(Node root, char *string) {
    bool isWord = (*(string + 3) == '\n' || *(string + 3) == '\0') ? true : false;
    char tmpStr[4];
    strncpy(tmpStr, string, 3);
    tmpStr[3] = '\0';
    Node node = initTrieTreeNode(tmpStr, isWord);
    if (root->childNum == 0)
        root->child = (Node * )malloc(sizeof(struct TrieNode));
    else
        root->child = (Node * )realloc(root->child, sizeof(struct TrieNode) * (root->childNum + 1));
    root->child[root->childNum] = node;
    root->childNum++;
    return node;
}

void buildTrieTree(Node root, char * string) {
    Node tempNode;
//    tempNode = malloc(sizeof(struct TrieNode));
    tempNode = root;
    while((*string != '\0') && (*string != '\n'))  {    // whether it is a whole word
        Node child;
        bool found = false;
        for (int i = 0; i < tempNode->childNum; i++) {
            if (tempNode->child[i] && (strcmp(tempNode->child[i]->word,string) == 0)) {
                found = true;
                child = tempNode->child[i];
            }
        }
        child = found ? child : buildTreeNode(tempNode, string);
        tempNode = child;
        string += 3;
    }
    // if string is done;
//    tempNode->child = NULL;
}

Node createTrieTreeRoot() {
    Node root = initTrieTreeNode(" ", false);
    return root;
}


Node createTrieTree(char * string) {
    Node doomRoot = initTrieTreeNode(" ", false);
    buildTrieTree(doomRoot, string);
    return doomRoot;
}
//status createTrieTree(Tree tree, char * string) {
//    int i;
//    int j = 0;
//    i = tree->root->childNum;
//    Node tempNode;
//    tempNode->word = *(string+j);
//    tree->root->child[0] = tempNode;
//    if (i == 0) {
//        createTrieTreeNode(&(tree->root), string);
//    } else {
//
//    }
//
//}
