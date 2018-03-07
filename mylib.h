//
// Created by PetnaKanojo on 29/01/2018.
//
#include "trieTree.h"
#ifndef C_DESIGN_MYLIB_H
#define C_DESIGN_MYLIB_H

#define WORDLENGTH 100

#define WORDCHAR (3 * sizeof(char))


char * charcpy(char * str);

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


/*************************************
 Function: letterLength
 Description: calculate the length of characters
 Input:
        string
 Return:
        length of string

***************************************/
int letterLength(char * string);

/*************************************
 Function: pressAnyKeyToContinue
 Description: press key to continue
 Input:
        void
 Return:
        void
***************************************/
void pressAnyKeyToContinue(void);


/*************************************
 Function: my_strncpy
 Description: redesign the strncpy
 Input:
        des: des string
        src: src string
        length: copy length
 Return:
        length of string
***************************************/
char * my_strncpy(char * des, char * src, int length);

/*************************************
 Function: matchUserInput
 Description: resolve the input string, to divide it according to the dictFile,
              you can choose to save it or not.
 Input:
        root: Trie Tree root
        string: string to resolved
        maxLength: return by function maxLength()
        fileOrNot: true to save
        saveFile: if (fileOrNot) saveFile name
 Return:
        void

***************************************/
void matchUserInput(Node root, char * string, int maxLength, int fileOrNot, char * saveFile);





#endif //C_DESIGN_MYLIB_H
