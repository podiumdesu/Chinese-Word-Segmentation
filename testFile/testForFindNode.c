//
// Created by PetnaKanojo on 26/02/2018.
//

#include "../mystd.h"
#include "../trieTree.h"

int main (void) {
    Node root = createTrieTreeRoot();
    char testfile[1000] = "/Users/petnakanojo/Documents/github/c_design/test.txt";
    char mainfile[1000] = "/Users/petnakanojo/Documents/github/c_design/reference/new.txt";
    buildDict(root, mainfile);
    printf("%d\n", root->child[0]->child[0]->childNum);
    printf("%s\n", root->child[0]->child[0]->child[1]->word);
    printf("this is the test for findNodes\n");
    printf("********* %d *****\n", findNode(root, "你好"));
    printf("********* %d *****\n", findNode(root, "你好"));
    printf("********* %d *****\n", findNode(root, "你好吗哈哈哈哈"));
    printf("********* %d *****\n", findNode(root, "中华人民共和国"));
    printf("********* %d *****\n", findNode(root, "猪头"));
    printf("********* %d *****\n", findNode(root, "心疼"));

}