//
// Created by PetnaKanojo on 26/02/2018.
//

#include "mystd.h"
#include "mylib.h"
#include "trieTree.h"

int check(int waitForCheck ) {
    // 1 for english word
    // 2 for numbers
    // 3 for chinese word
    int temp = waitForCheck;
    temp = temp >> 7;
    if ((temp & 1) == 1) {
        return 3;
    } else {
        temp = waitForCheck;
        temp = temp >> 6;
        if ((temp & 1) == 1) {
            return 1;
        } else {
            return 2;
        }
    }

}
int matchStringForMAX(Node root, char * resolveString, int length, int saveOrNot, char * saveFile) {   //最多传入maxLength个汉字->resolveString

    char tempStr[100];
    FILE *fp;
    if (saveOrNot) {
        fp = fopen(saveFile, "a");
    }

    my_strncpy(tempStr, resolveString, length);  //length目前有效长度
    while ((*tempStr != '\n') || (*tempStr != '\0') || (*tempStr != '\r')) {  //
        if (findNode(root, tempStr)) {
            //resolveString += letterLength(tempStr) * WORDCHAR;    //已经匹配完的剔除，对于剩下的字符串继续
            printf("%s|", tempStr);
            if (saveOrNot) {
                fprintf(fp, "%s|", tempStr);
                fclose(fp);
            }
            return (letterLength(tempStr) + 1);  //返回现在完成的长度
        } else { //如果目前tempStr不能匹配
            if (length == 1) { //如果现在长度为1，词典匹配失败，直接输出
                if (saveOrNot) {
                    fprintf(fp, "%s|", tempStr);
                    fclose(fp);
                }
                printf("%s|", tempStr);
                return 1;
            }
            length--;
            my_strncpy(tempStr, tempStr, length);    //如果未查找到，将tempStr最后一位剔除
        }
    }
    return 0;
}


void matchUserInput(Node root, char * string, int maxLength, int fileOrNot, char * saveFile) {

    int flag;
    FILE *fp;
    if (fileOrNot) {
        fp = fopen(saveFile, "a");
    }


    int removeLength = 0;
    FILE *tempFp;
    char temp[10];
    do {
        if (check(*string) != 3) {

            if (check(*string) == 2) {
                // 前一个为英文
                if (flag == 1) {
                    if (fileOrNot) {
                        fp = fopen(saveFile, "a");
                        fprintf(fp, "|");
                        fprintf(fp, "%c", *string);
                        fclose(fp);
                    }
                    printf("|%c", *string);
                } else {
                    if (fileOrNot) {
                        fp = fopen(saveFile, "a");
                        fprintf(fp, "%c", *string);
                        fclose(fp);
                    }
                    printf("%c", *string);
                }
                flag = 2;
                string += 1;
            } else {
                if (flag == 2) {
                    if (fileOrNot) {
                        fp = fopen(saveFile, "a");
                        fprintf(fp, "|");
                        fprintf(fp, "%c", *string);
                        fclose(fp);
                    }
                    printf("|%c", *string);
                } else {
                    if (fileOrNot) {
                        fp = fopen(saveFile, "a");
                        fprintf(fp, "%c", *string);
                        fclose(fp);
                    }
                    printf("%c", *string);
                }
                flag = 1;
                string += 1;
            }

        } else {
            if (fileOrNot) {
                fp = fopen(saveFile, "a");
                fprintf(fp, "|");
                fclose(fp);
            }
            if (flag == 1) {
                printf("|");
            }
            flag = 0;
            if (letterLength(string) > maxLength) {
                removeLength = matchStringForMAX(root, string, maxLength, fileOrNot, saveFile);
            } else {
                removeLength = matchStringForMAX(root, string, letterLength(string), fileOrNot, saveFile);
            }
            string += removeLength * WORDCHAR;
        }

        //printf("now you need to resolve %s\n",string);
    } while ((*string != '\n') && (*string != '\0') && (*string != '\r'));
    if (fileOrNot) {
        tempFp = fopen(saveFile, "a");
        strcpy(temp, "\n");
        fprintf(tempFp, "%s", temp);
        fclose(tempFp);
    }
    printf("\n");
}

//
//int matchStringForMAX(Node root, char * resolveString, int length, int saveOrNot, char * saveFile) {   //最多传入maxLength个汉字->resolveString
//    char tempStr[100];
//    FILE *fp;
//    if (saveOrNot) {
//        fp = fopen(saveFile, "a");
//    }
//    my_strncpy(tempStr, resolveString, length);  //length目前有效长度
//    while ((*tempStr != '\n') || (*tempStr != '\0') || (*tempStr != '\r')) {  //
//        if (findNode(root, tempStr)) {
//            //resolveString += letterLength(tempStr) * WORDCHAR;    //已经匹配完的剔除，对于剩下的字符串继续
//            printf("%s|", tempStr);
//            if (saveOrNot) {
//                fprintf(fp, "%s|", tempStr);
//                fclose(fp);
//            }
//            return (letterLength(tempStr) + 1);  //返回现在完成的长度
//        } else { //如果目前tempStr不能匹配
//            if (length == 1) { //如果现在长度为1，词典匹配失败，直接输出
//                if (saveOrNot) {
//                    fprintf(fp, "%s|", tempStr);
//                    fclose(fp);
//                }
//                printf("%s|", tempStr);
//                return 1;
//            }
//            length--;
//            my_strncpy(tempStr, tempStr, length);    //如果未查找到，将tempStr最后一位剔除
//        }
//    }
//    return 0;
//}
//
//void matchUserInput(Node root, char * string, int maxLength, int fileOrNot, char * saveFile) {
//    int removeLength = 0;
//    FILE *tempFp;
//    char temp[10];
//    do {
//        if (letterLength(string) > maxLength) {
//            removeLength = matchStringForMAX(root, string, maxLength, fileOrNot, saveFile);
//        } else {
//            removeLength = matchStringForMAX(root, string, letterLength(string), fileOrNot, saveFile);
//        }
//        string += removeLength * WORDCHAR;
//        //printf("now you need to resolve %s\n",string);
//    } while ((*string != '\n') && (*string != '\0') && (*string != '\r'));
//    if (fileOrNot) {
//        tempFp = fopen(saveFile, "a");
//        strcpy(temp, "\n");
//        fprintf(tempFp, "%s", temp);
//        fclose(tempFp);
//    }
//    printf("\n");
//}
