//
// Created by PetnaKanojo on 12/02/2018.
//

#include "mystd.h"
#include "trieTree.h"

/*************************************
 Function:
 Description:
 Input:
 Return:
***************************************/



/*************************************
 Function: initTrieTreeNode
 Description: init the smallest of a node in the trieTree
 Input:
        word: the character.
        isWord: whether it is the end of a complete word.
 Return:
        pnode: means this constructed node.
***************************************/
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
    bool isWord = *(string + 3) == '\n' || *(string + 3) == '\0';
    char *tmpStr = charcpy(string);
    Node node = initTrieTreeNode(tmpStr, isWord);
    free(tmpStr);
    if (root->childNum == 0)
        root->child = (Node * )malloc(sizeof(struct TrieNode));
    else
        root->child = (Node * )realloc(root->child, sizeof(struct TrieNode) * (root->childNum + 1));
    root->child[root->childNum] = node;
    root->childNum++;
    return node;
}

Node updateTreeNode(Node node, char *string) {
    if (node->isWord == false)
        node->isWord = *(string + 3) == '\n' || *(string + 3) == '\0';
    return node;
}

void buildTrieTree(Node root, char * string) {
    while((*string != '\0') && (*string != '\n'))  {    // whether it is a whole word
        Node child;
        bool found = false;
        char *tmpStr = charcpy(string);
        for (int i = 0; i < root->childNum; i++) {
            if (root->child[i] && (strcmp(root->child[i]->word,tmpStr) == 0)) {
                found = true;
                child = updateTreeNode(root->child[i], string);
            }
        }
        free(tmpStr);
        if (!found)
            child = buildTreeNode(root, string);
        root = child;
        string += 3;
    }
}

Node createTrieTreeRoot() {
    Node root = initTrieTreeNode(" ", false);
    return root;
}

char * charcpy(char * str) {
    char * tmpStr = (char *)malloc(sizeof(char) * 4);
    strncpy(tmpStr, str, 3);
    tmpStr[3] = '\0';
    return tmpStr;
}

int findNode (Node root, char * string) {
    bool found = false;
    Node child;
    while((*string != '\0') && (*string != '\n')) {// whether it is a whole word
        char *tempStr = charcpy(string);
        for (int i = 0; i < root->childNum; i++) {
            if ((root->child[i]) && strcmp(root->child[i]->word, tempStr) == 0) {
                child = root->child[i];
                root = child;
                found = true;
                break;
            } else {
                found = false;
            }
        }

        string += 3;
        if (((*string != '\0') && (*string != '\n')) && (root->childNum == 0)) {
            found = false;
        }
        free(tempStr);
    }
    if (!found) {
        return false;
    } else {
        return (root->isWord) ? true : false;
    }
}
//
//static char printWord[100];
//static char tempWord[100];
//void writeNode(Node root, char * printWord) {
//    strcat(printWord, root->word);
//    //printf("%s", printWord);
//    if (root->childNum > 0 && (!root->isWord)) {
//        for (int i = 0; i < root->childNum; i++) {
//            //end = (i == root->childNum - 1);
//            strcpy(tempWord, printWord);
//            writeNode(root->child[i], tempWord);
//        }
//    } else if (root->childNum > 0 && root->isWord) {
//        printf("%s\n", printWord);
//        for (int i = 0; i < root->childNum; i++) {
//            //end = (i == root->childNum - 1);
//            strcpy(tempWord, printWord);
//            writeNode(root->child[i], tempWord);
//        }
//    } else if (root->childNum <= 0 && root->isWord) {
//        printf("%s\n", printWord);
//        printWord[0] = '\0';
//    } else {
//    }
//}
//void writeTofile(Node root, char * fileName) {
//    bool end = false;
//    printf("hello, this is test writing \n");
//    for (int i = 0; i < root->childNum; i++) {
//        writeNode(root->child[i], printWord);
//    }
//
//};
