#ifndef MYMAIN_H
#define MYMAIN_H
// mystd.h
// Created by PetnaKanojo on 29/01/2018.
//

// include standard lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stdbool.h"
//

//#endif //C_DESIGN_MYSTD_H

//
// Created by PetnaKanojo on 29/01/2018.
//
//#include "trieTree.h"
//#ifndef C_DESIGN_MYLIB_H
//#define C_DESIGN_MYLIB_H

#define WORDLENGTH 100

// TrieTree.h
//
// Created by PetnaKanojo on 24/02/2018.
//


//#ifndef C_DESIGN_TRIETREE_H
//#define C_DESIGN_TRIETREE_H
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
 status: WRONG / OK
 ***************************************/
double buildDict(Node root, char * fileName);

void buildTrieTree(Node root, char * string);
Node createTrieTreeRoot();
Node createTrieTree(char * string);
char * charcpy(char * str);

//void writeTofile(Node root, char * fileName);
/*************************************
 Function: findNode
 Description:
 Input:
 root: Trie Tree Root
 string: new word
 fileName: dict Name
 Return:
 void
 testFile: testFile/testForFindNode.c
 ***************************************/
bool findNode (Node root, char * string);

/*************************************
 Function: addNewNode
 Description:
 Input:
 root: Trie Tree Root
 string: new word
 fileName: dict Name
 Return:
 void
 testFile: testFile/testForAddNewNode.c
 ***************************************/
status addNewNode (Node root, char * string, char * fileName);

/*************************************
 Function: removeNode
 Description:
 Input:
 root: Trie Tree Root
 string: new word
 fileName: dict Name
 Return:
 void
 testFile: testFile/testForRemoveNode.c
 ***************************************/
status removeNode (Node root, char * string, char * fileName);

//#endif //C_DESIGN_TRIETREE_H



#define WORDCHAR (3 * sizeof(char))
/*************************************
 Function: maxLength
 Description: calculate the max length of the word
 Input:
 fileName: dict
 Return:
 maxlength (int)
 ***************************************/
int maxLength(char * fileName);


/*************************************
 Function: resolveInput
 Description: resolve users' input
 Input:
 string: input
 Return:

 ***************************************/
char * resolveInputDictName(char * string);
char * resolveInput(char * string);

void showAllContent(char * string);

int letterLength(char * string);

void pressAnyKeyToContinue(void);
char * my_strncpy(char * des, char * src, int length);

void matchUserInput(Node root, char * string, int maxLength, int fileOrNot, char * saveFile);


#endif // MYMAIN_H
