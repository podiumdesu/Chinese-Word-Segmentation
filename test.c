#include <stdio.h>
#include <string.h>
#include "mylib.h"
#include "mystd.h"
#include "trieTree.h"
//int main (void) {
//    int fgets_count = 0;
//    char result[100][10000];
//    FILE *fp;
//    printf("%d",strlen("好"));
//    if ((fp = fopen("test.txt", "r")) == NULL) {
//        printf("not open");
//    } else {J
//        while (fgets(result[fgets_count], 10000, fp) != NULL) {   //将每段读入字符串中
//            //fgets(result[fgets_count], 10000, fp);
//            fgets_count++;
//        }
//        //printf("%d\n", fgets_count);
//        for (int i = 0; i < fgets_count; i++) {
//            printf("%s", result[i]);
//            printf("%d\n",strlen(result[i]));
//        }
//    }
//}

int main (void) {
    char result[1000];
    FILE *fp;
    Node root;
    if ((fp = fopen("/Users/petnakanojo/Documents/github/c_design/test.txt", "r")) == NULL) {
        printf("not open\n");
    } else {
        while(fgets(result, 1000, fp) != NULL) {
            if (result[0] != '\n') {
                printf("the word is %s\n", result);
                root = createTrieTree(result);
            }
        }
        int i = root->childNum;
        printf("%d", i);
        for (int j = 0; j < root->childNum; j++) {
            printf("wrong wrong %s\n", root->child[j]->word);
        }
    }
}
