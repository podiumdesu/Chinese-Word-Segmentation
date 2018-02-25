//
// Created by PetnaKanojo on 29/01/2018.
//
#include "trieTree.h"
#ifndef C_DESIGN_MYLIB_H
#define C_DESIGN_MYLIB_H

/*************************************
 Function: maxLength
 Description: calculate the max length of the word
 Input:
        fileName: dict
 Return:
        maxlength (int)
***************************************/
int maxLength(char * fileName);

char * resolveInput(char *);

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

#endif //C_DESIGN_MYLIB_H
