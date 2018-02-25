//
// Created by PetnaKanojo on 14/02/2018.
//
#include "../mystd.h"
int maxLength(char *fileName) {
    char result[1000];
    int maxlength = 0;
    int templen;
    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("not open\n");
    } else {
        while(fgets(result, 10000, fp) != NULL) {
            if (result[0] != '\n') {
                templen = (int) ((strlen(result) - 1) / 3);
                printf("%d\n", templen);
                if (templen > maxlength) maxlength = templen;
            }
        }
    }
    return maxlength;
}
