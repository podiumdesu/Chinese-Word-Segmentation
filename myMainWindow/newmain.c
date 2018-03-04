#include "main.h"
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

//////

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
    int removeLength = 0;
    FILE *tempFp;
    char temp[10];
    do {
        if (letterLength(string) > maxLength) {
            removeLength = matchStringForMAX(root, string, maxLength, fileOrNot, saveFile);
        } else {
            removeLength = matchStringForMAX(root, string, letterLength(string), fileOrNot, saveFile);
        }
        string += removeLength * WORDCHAR;
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

//////
int maxLength(char *fileName) {
    char result[1000];
    int maxlength = 0;
    int templen;
    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("FILE: %s not open\n", fileName);
    } else {
        while(fgets(result, 10000, fp) != NULL) {
            if (result[0] != '\n') {
                templen = (int) ((strlen(result) - 1) / 3);
                // todo delete
                // printf("%d\n", templen);
                if (templen > maxlength) maxlength = templen;
            }
        }
    }
    return maxlength;
}

////share.c
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

void pressAnyKeyToContinue(void) {
    printf("\n请按任意键继续...");
    getchar();
    getchar();
}

/*************************************
 Function: initTrieTreeNode
 Description: init the smallest of a node in the trieTree
 Input:
 word: the character.
 isWord: whether it is the end of a complete word.
 Return:
 pnode: means this constructed node.
 ***************************************/
Node initTrieTreeNode(char * word, bool isWord) {
    Node pnode = (Node)malloc(sizeof(struct TrieNode));
    if (pnode) {
        strcpy(pnode->word, word);
        pnode->isWord = isWord;
        pnode->child = NULL;
        pnode->childNum = 0;
    }
    return pnode;
}

Node buildTreeNode(Node root, char *string) {
    bool isWord = *(string + 3) == '\n' || *(string + 3) == '\0' || *(string + 3) == '\r';
    char *tmpStr = charcpy(string);
    Node node = initTrieTreeNode(tmpStr, isWord);
    free(tmpStr);
    if (root->childNum == 0)
        root->child = (Node * )malloc(sizeof(struct TrieNode));
    else
        root->child = (Node * )realloc(root->child, sizeof(struct TrieNode) * (root->childNum + 1));
    root->child[root->childNum] = node;
    root->childNum++;
    return node;
}

Node updateTreeNode(Node node, char *string) {
    if (node->isWord == false)
        node->isWord = *(string + 3) == '\n' || *(string + 3) == '\0' || *(string + 3) == '\r';
    return node;
}

void buildTrieTree(Node root, char * string) {
    while((*string != '\0') && (*string != '\n') && (*string != '\r'))  {    // whether it is a whole word
        Node child;
        bool found = false;
        char *tmpStr = charcpy(string);
        for (int i = 0; i < root->childNum; i++) {
            if (root->child[i] && (strcmp(root->child[i]->word,tmpStr) == 0)) {
                found = true;
                child = updateTreeNode(root->child[i], string);
            }
        }
        free(tmpStr);
        if (!found)
            child = buildTreeNode(root, string);
        root = child;
        string += 3;
    }
}

Node createTrieTreeRoot() {
    Node root = initTrieTreeNode(" ", false);
    return root;
}

char * charcpy(char * str) {
    char * tmpStr = (char *)malloc(sizeof(char) * 4);
    strncpy(tmpStr, str, 3);
    tmpStr[3] = '\0';
    return tmpStr;
}
///// trie.c
/*************************************
 Function: findNode
 Description: find whether node is in the trie tree
 Input:
 root: trie tree root
 string: name of the node
 Return:
 found (bool)
 ***************************************/
bool findNode (Node root, char * string) {
    bool found = false;
    Node child;
    while((*string != '\r') && (*string != '\n') && (*string != '\0') && (*string)) {// whether it is a whole word
        char *tempStr = charcpy(string);
        for (int i = 0; i < root->childNum; i++) {
            if ((root->child[i]) && strcmp(root->child[i]->word, tempStr) == 0) {
                child = root->child[i];
                root = child;
                found = true;
                break;
            } else {
                found = false;
                if (i == root->childNum - 1) {
                    return found;
                }
            }
        }
        string += 3;
        if (((*string != '\r') && (*string != '\n') && (*string != '\0')) && (root->childNum == 0)) {
            found = false;
            free(tempStr);
            break;
        }
        free(tempStr);
    }
    if (!found) {
        return false;
    } else {
        return (root->isWord) ? true : false;
    }
}

void addNewNode (Node root, char * string, char * fileName) {
    FILE *fp;
    if ((fp = fopen(fileName, "a")) == NULL) {
        printf("FILE: open %s wrong", fileName);
    } else {
        buildTrieTree(root, string);
        //todo inspect the end of the file to add '\n'
        fwrite(string, 3*sizeof(char), strlen(string) / 3, fp);
        fwrite("\n", sizeof(char), 1, fp);
        fclose(fp);
        printf("%s 添加成功\n", string);
    }
    
}

void Delete(char* filename, int n){
    FILE *fp1, *fp2;
    char c[100];
    int del_line, temp = 1;
    fp1 = fopen(filename, "r");
    del_line = n;
    fp2 = fopen("temp.txt", "w");
    while (fgets(c, 100, fp1) != NULL) {
        if (temp != del_line) {
            fputs(c, fp2);
        }
        temp++;
    }
    fputs("\n", fp2);
    fclose(fp1);
    fclose(fp2);
    //remove original file
    remove(filename);
    //rename the file temp.txt to original name
    rename("temp.txt", filename);
}

void removeNode (Node root, char * string, char * fileName) {
    FILE *fp;
    char result[100];
    int rowNum = 1;
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("FILE: %s not open\n", fileName);
    } else {
        while(fgets(result, 100, fp) != NULL) {
            result[strlen(result) - 1] ='\0';
            if (strcmp(result, string) == 0) {
                //printf("%s row num is: %d\n", string , rowNum);
                break;
            }
            rowNum++;
        }
        printf("%d\n", rowNum);
        Delete(fileName, rowNum);
        printf("REMOVE DONE\n");
    }
    
}


////
