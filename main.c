#include "mystd.h"
#include "mylib.h"
#include "trieTree.h"
#define CHUNK 1024
int main() {

    char mainfile[1000] = "/Users/petnakanojo/Documents/github/c_design/reference/dict.txt";
    char testfile[1000] = "/Users/petnakanojo/Documents/github/c_design/test.txt";

    char input[10000], ch, result[100][10000];
    int op = 1;
    // choose 1 2 0
    int inputChoice;
    // record the max length of words in the dict.
    int maxLengthInDict;

    FILE *fp;
    int fgets_count = 0;

    //Node in trie tree
    Node root = createTrieTreeRoot();

    while (op) {
        maxLengthInDict = maxLength(testfile);
        printf("MAX LENGTH IS %d\n", maxLengthInDict);
        buildDict(root, testfile);
        printf("this is a test: %d\n", root->child[0]->child[0]->isWord);
        //writeTofile(root, testfile);   todo delete unuseful
        //todo delete this is the test for findNode       passed;
//        printf("%d, *******\n",findNode(root, "中华人民"));
//        printf("%d, *******\n",findNode(root, "中华人民共和国"));
//        printf("%d, *******\n",findNode(root, "中华人民共和"));
//        printf("%d, *******\n",findNode(root, "你"));
//        printf("%d, *******\n",findNode(root, "你好吗哈哈哈"));
//        printf("%d, *******\n",findNode(root, "这是"));

        printf("请输入1 或者 2， 0退出\n");  //从文件导入或是直接读入，0退出
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
    }
    //printf("%s", input);

}