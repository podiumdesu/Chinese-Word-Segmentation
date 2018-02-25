#include <stdio.h>
#include "trieTree.h"
#include <time.h>

int main (void) {
    char result[1000];
    FILE *fp;
    Node root;
    time_t start = clock();
    root = createTrieTreeRoot();
    char mainfile[1000] = "/Users/petnakanojo/Documents/github/c_design/reference/dict.txt";
    char testfile[1000] = "/Users/petnakanojo/Documents/github/c_design/test.txt";
    int test = 1;
    if ((fp = fopen(testfile, "r")) == NULL) {
        printf("not open\n");
    } else {
        while(fgets(result, 1000, fp) != NULL) {
            if (result[0] != '\n')
                buildTrieTree(root, result);
        }
        if (test) {
            int i = root->childNum;
            printf("%d\n", i);
            for (int j = 0; j < root->childNum; j++) {
                printf("wrong wrong %s\n", root->child[j]->child[0]->word);
            }
            printf("this is a test: %d\n", root->child[0]->child[0]->isWord);
        }

    }
    time_t end = clock();
    printf("fucking time: %gs", (double)(end - start) / CLOCKS_PER_SEC);
}
