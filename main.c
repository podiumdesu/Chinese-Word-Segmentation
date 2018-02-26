#include "mystd.h"
#include "mylib.h"
#include "trieTree.h"
#define CHUNK 1024
int main() {

    char mainfile[1000] = "/Users/petnakanojo/Documents/github/c_design/reference/dict.txt";
    char testfile[1000] = "/Users/petnakanojo/Documents/github/c_design/test.txt";
    char dictFile[1000];
    char input[10000], ch, result[100][10000];
    int op = 1;

    int menuChoice, dictChoice, inputChoice;
    // record the max length of words in the dict.
    int maxLengthInDict;

    FILE *fp;
    int fgets_count = 0;

    maxLengthInDict = maxLength(testfile);
    //printf("MAX LENGTH IS %d\n", maxLengthInDict);
    // 建立索引
    printf("请输入用于建立索引的文件名：");
    Node root = createTrieTreeRoot();
    scanf("%s", dictFile);
    buildDict(root, dictFile);
    printf("总共支节点：%d\n", root->childNum);
    //printf("this is a test: %d\n", root->child[0]->child[0]->isWord);

    while (op) {
        printf("********欢迎使用中文分词系统********\n");
        printf("1.词典维护\t2.导入处理文件\t0.退出\n");
        scanf("%d", &menuChoice);
        switch (menuChoice) {
            case 1:
                    while (1) {
                        char addString[100];
                        printf("请输入对词典的操作：1.增加\t2.删除\t3.修改\t0.返回上一级\n");
                        scanf("%d", &dictChoice);
                        if (dictChoice == 1) {
                            scanf("%s", addString);
                            addNewNode(root, addString, dictFile);
                        } else if (dictChoice == 2) {
                            removeNode(root, "你好", dictFile);
                        } else if (dictChoice == 3) {

                        } else if (dictChoice == 0) {
                            break;
                        }
                    }
                    break;

            case 2: printf("导入处理文件: 1. 从文件导入\t2.直接读入\t0.返回上一级\n");
                    scanf("%d", &inputChoice);
                    if (inputChoice == 1) {    //处理文件导入

                        if ((fp = fopen("testinput.txt", "r")) == NULL) {
                            printf("not open\n");

                        } else { //成功打开文件
                            char *buf = malloc(CHUNK);
                            if (buf == NULL) {
                                printf("malloc gg\n");
                            }
                            while (fgets(result[fgets_count], 10000, fp) != NULL) {   //将每段读入字符串中
                                //fgets(result[fgets_count], 10000, fp);
                                fgets_count++;
                            }
                            printf("%d\n", fgets_count);
                            for (int i = 0; i < fgets_count; i++) {
                                printf("%s", result[i]);
                            }
    //                while((nread = fread(buf, 1, CHUNK, fp)) > 0) {
    //                    fwrite(buf, 1, nread, result);
    //                    printf("gg\n");
    //                }
                        }
                        fclose(fp);
                        printf("\n功能未完善\n");
                    } else if (inputChoice == 2) {
                        printf("请输入一段文字\n");
                        while (scanf("%s", input) != EOF) {
                            printf("%s", input);
                        }
                    } else if (inputChoice == 0) {
                        op = 0;
                    } else {
                        printf("请正确输入\n");
                    }
                    break;
            case 0: op = 0;
                    printf("谢谢使用！\n");
                    break;
        }

    }
}