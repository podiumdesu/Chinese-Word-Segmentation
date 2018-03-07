//
// Created by PetnaKanojo on 12/02/2018.
//

#include "mystd.h"
#include "trieTree.h"
#include "mylib.h"

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

/*************************************
 Function: buildTrieTree
 Description: according to the string, to build up the trie tree
 Input:
        root: trie tree root
        string: string to insert the tree
 Return:
        void
***************************************/
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
/*************************************
 Function: addNewWord
 Description: addNewWord to the Trie Tree && dict
 Input:
        root: trie tree root
        string: word to add
        fileName: dictFile Name
 Return:
        void
***************************************/
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

/*************************************
 Function: removeWord
 Description: removeWord from the Trie Tree && dict
 Input:
        root: trie tree root
        string: word to add
        fileName: dictFile Name
 Return:
        void
 Notes: use function Delete()
***************************************/
void removeNode (Node root, char * string, char * fileName) {
    FILE *fp;
    char result[100];
    int rowNum = 1;
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("FILE: %s not open\n", fileName);
    } else {
        while(fgets(result, 100, fp) != NULL) {
            // 处理result
            if (rowNum < 217145) {
                result[strlen(result) - 2] ='\0';
            } else {
                result[strlen(result) - 1] ='\0';
            }
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

