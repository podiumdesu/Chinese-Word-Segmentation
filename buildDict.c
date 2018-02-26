//
// Created by PetnaKanojo on 25/02/2018.
//
#include "mystd.h"
#include "mylib.h"
#include <time.h>
//function in trie.c

//root = createTrieTreeRoot();
void buildDict(Node root, char * fileName) {
    char result[3000];
    FILE *fp;
    time_t start = clock();
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("%s not open!\n", fileName);
    } else {
        while (fgets(result, 3000, fp) != NULL) {
            if (result[0] != '\n')
                buildTrieTree(root, result);
        }
    }
    //todo delete test
//    int test = 1;
//    if (test) {
//        int i = root->childNum;
//        printf("%d\n", i);
//        for (int j = 0; j < root->childNum; j++) {
//            printf("wrong wrong %s\n", root->child[j]->child[0]->word);
//        }
//        printf("this is a test: %d\n", root->child[0]->child[0]->isWord);
//    }
    time_t end = clock();
    printf("Building time costs: %gs\n", (double)(end - start) / CLOCKS_PER_SEC);
}

