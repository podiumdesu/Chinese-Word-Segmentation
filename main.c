#include "mystd.h"
#include "mylib.h"
#include "trieTree.h"

#define CHUNK 1024
int main() {

    char mainfile[1000] = "/Users/petnakanojo/Documents/github/c_design/reference/dict.txt";
    char testfile[1000] = "/Users/petnakanojo/Documents/github/c_design/test.txt";
    //      /Users/petnakanojo/Documents/github/c_design/testinput.txt
    //      /Users/petnakanojo/Documents/github/c_design/test.txt
    char dictFile[1000];
    char tempDictFile[1000];
    char tempFileName[1000];
    char input[10000], ch, result[100][10000];
    char temp[10];
    int tempChoice;
    int op = 1;

    int menuChoice, dictChoice, inputChoice;
    // record the max length of words in the dict.
    int maxLengthInDict;
    int dictHasChanged = 0;
    int readNewDict = 1;
    int done = 0;
    FILE *fp;
    int fgets_count = 0;


    //printf("MAX LENGTH IS %d\n", maxLengthInDict);

    Node root = createTrieTreeRoot();

    while (op) {

        if (readNewDict) {
            // 建立索引
            printf("请输入用于建立索引的文件名：(q退出)");
            //strcpy(dictFile, testfile);
            strcpy(tempDictFile, dictFile);
            scanf("%s", dictFile);
            while( buildDict(root, dictFile) == WRONG ) {
                printf("文件%s打开错误！\n请重新输入：\n", dictFile);
                scanf("%s", dictFile);
            };
            printf("总共支节点：%d\n", root->childNum);
            maxLengthInDict = maxLength(dictFile);
            //printf("this is a test: %d\n", root->child[0]->child[0]->isWord);
            readNewDict = 0;
            done = 1;
        }
        if (dictHasChanged) {
            getchar();
            printf("监测到您的词典有变动，是否更新索引？ y/n ");
            scanf("%c", &ch);
            if (ch == 'y' || ch == 'Y') {
                free(root);
                root = createTrieTreeRoot();
                buildDict(root, dictFile);
                dictHasChanged = 0;
                done = 1;
            } else {
                done = 1;
            }
            printf("\n");
        }

        if (done) {
            printf("*************欢迎使用中文分词系统***************\n");
            printf("** 1.词典维护  2.导入处理文件  3.载入新词典 0.退出**\n");
            printf("***********************************************\n");

            scanf("%d", &menuChoice);
            switch (menuChoice) {
                case 1:
                    while (1) {
                        char addString[WORDLENGTH];
                        printf("******请输入对词典的操作：*******\n");
                        printf("1.增加\t2.删除\t3.修改\t4.显示词典内容\t0.返回上一级\n");
                        scanf("%d", &dictChoice);
                        if (dictChoice == 1) {
                            printf("请输入想要添加的词汇\n");
                            scanf("%s", addString);
                            if (findNode(root, addString)) {
                                printf("操作无效，这个词已经在词典中了哦\n");
                                pressAnyKeyToContinue();
                            } else {
                                addNewNode(root, addString, dictFile);
                                dictHasChanged = 1;
                            }

                        } else if (dictChoice == 2) {
                            printf("输入想要删除的词汇：");
                            char removeWord[WORDLENGTH];
                            scanf("%s", removeWord);
                            if (findNode(root, removeWord)) {
                                removeNode(root, removeWord, dictFile);
                                dictHasChanged = 1;
                            } else {
                                printf("操作无效，不在词典中哦\n");
                            }
                            pressAnyKeyToContinue();

                        } else if (dictChoice == 3) {
                            char changeWord[WORDLENGTH];
                            char changeWordTo[WORDLENGTH];
                            printf("输入想要修改的词汇以及修改后的内容，用空格分开\t");
                            scanf("%s %s", changeWord, changeWordTo);
                            if (findNode(root, changeWord)) {
                                if (findNode(root, changeWordTo)) {
                                    printf("操作无效，想要替换的词已经在词典中了哦\n");
                                } else {
                                    removeNode(root, changeWord, dictFile);
                                    addNewNode(root, changeWordTo, dictFile);
                                    dictHasChanged = 1;
                                }
                            } else {
                                printf("这个词不在词典中哦\n");
                            }
                            pressAnyKeyToContinue();
                            printf("\n");
                        } else if (dictChoice == 4) {
                            showAllContent(dictFile);
                            pressAnyKeyToContinue();
                        } else if (dictChoice == 0) {
                            // system("clear");
                            break;
                        }
                    }
                    break;

                case 2: printf("导入处理文件: 1. 从文件导入\t2.直接读入\t0.返回上一级\n");
                    scanf("%d", &inputChoice);
                    if (inputChoice == 1) {    //处理文件导入
                        char inputFileName[1000];
                        printf("请输入导入文件名：");
                        scanf("%s", inputFileName);
                        if ((fp = fopen(inputFileName, "r")) == NULL) {
                            printf("FILE: %s not open\n", inputFileName);
                        } else {
                            fgets_count = 0;
                            printf("是否将结果保存成文件？y/n ：\n");
                            scanf("%s", temp);
                            tempChoice = ((*temp) == 'y' || (*temp) == 'Y') ? 1 : 0;
                            if (tempChoice) {
                                printf("保存文件名：");
                                scanf("%s", tempFileName);
                                remove(tempFileName);
                            }
                            char *buf = malloc(CHUNK);
                            if (buf == NULL) {
                                printf("malloc gg\n");
                            }
                            while (fgets(result[fgets_count], 10000, fp) != NULL) {
                                fgets_count++;
                            }
                            printf("共%d段\n", fgets_count);
                            printf("     ***分词结果***     \n");
                            for (int i = 0; i < fgets_count; i++) {
                                //printf("%s", result[i]);
                                //FILE * tempFp;
                                //FILE * tempFp
                                matchUserInput(root, result[i], maxLengthInDict, tempChoice, tempFileName);
                            }
                        }
                        fclose(fp);
                        printf("\n完成！\n");
                    } else if (inputChoice == 2) {

                        printf("是否将结果保存成文件？y/n ：");
                        scanf("%s", temp);
                        printf("请输入一段文字：\n");
                        tempChoice = ((*temp) == 'y' || (*temp) == 'Y') ? 1 : 0;
                        if (tempChoice) {
                            printf("保存文件名：");
                            scanf("%s", tempFileName);
                            remove(tempFileName);
                        }
                        getchar();
                        if (fgets(input, 10000, stdin) != NULL) {
                            matchUserInput(root, input, maxLengthInDict, tempChoice, tempFileName);
                        }
                    } else if (inputChoice == 0) {
                        break;
                        //system("clear");
                    } else {
                        printf("请正确输入\n");
                    }
                    break;
                case 3: readNewDict = 1;
                    break;
                case 0: op = 0;
                    printf("谢谢使用！\n");
                    break;
            }
            if (dictHasChanged) {
                done = 0;
            }
        }

    }
}