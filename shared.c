//
// Created by PetnaKanojo on 25/02/2018.
//

// shared and common functions
#include "mystd.h"
#include "mylib.h"

char * charcpy(char * str) {
    char * tmpStr = (char *)malloc(sizeof(char) * 4);
    strncpy(tmpStr, str, 3);
    tmpStr[3] = '\0';
    return tmpStr;
}
void showAllContent(char * filename) {
    FILE *fp;
    char string[100];
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("FILE: %s not open\n", filename);
    } else {
        printf("****Here is the content*****\n");
        while(fgets(string,100, fp) != NULL) {
            printf("\t%s", string);
        }
        printf("****************************\n");
    }
}
char * my_strncpy(char * des, char * src, int length) {
    if (des == src) {
        char temp[100];
        strncpy(temp, src, length * WORDCHAR);
        strncpy(des, temp, length * WORDCHAR);
    } else {
        strncpy(des, src, length * WORDCHAR);
    }
    des[length * WORDCHAR] = '\0';
    return des;
}

/*************************************
 Function: letterLength
 Description: calculate the length of characters
 Input:
        string
 Return:
        length of string

***************************************/
int letterLength(char * string) {
    return (strlen(string) - 1) / 3;
}

char * resolveInputDictName(char * string) {
    char temp[1000];
    strcpy(temp, string);
    if ((*string == 'q' || *string == 'Q') && (strlen(string) < 3)) {
        strcpy(string, temp);
        printf("仍使用%s词典文件\n", string);
    }
    free(temp);
    return string;
}

/*************************************
 Function: pressAnyKeyToContinue
 Description: press key to continue
 Input:
        void
 Return:
        void
***************************************/
void pressAnyKeyToContinue(void) {
    printf("\n请按任意键继续...");
    getchar();
    getchar();
}