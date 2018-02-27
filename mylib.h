//
// Created by PetnaKanojo on 29/01/2018.
//
#include "trieTree.h"
#ifndef C_DESIGN_MYLIB_H
#define C_DESIGN_MYLIB_H

#define WORDLENGTH 100

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





#endif //C_DESIGN_MYLIB_H
