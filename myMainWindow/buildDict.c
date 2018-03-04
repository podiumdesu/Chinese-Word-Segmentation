//
// Created by PetnaKanojo on 25/02/2018.
//
#include "mystd.h"
#include "mylib.h"
#include <time.h>
//function in trie.c

//root = createTrieTreeRoot();
status buildDict(Node root, char * fileName) {
    char result[3000];
    FILE *fp;
    time_t start = clock();
    if ((fp = fopen(fileName, "r")) == NULL) {
        //printf("%s not open!\n", fileName);
        return WRONG;
    } else {
        printf("读取词典成功！正在建立TRIE树......\n");
        while (fgets(result, 3000, fp) != NULL) {
            if (result[0] != '\n')
                buildTrieTree(root, result);
        }
    }
    time_t end = clock();
    printf("Building time costs: %gs\n", (double)(end - start) / CLOCKS_PER_SEC);
    return OK;
}

