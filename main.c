#include "mystd.h"
#include "mylib.h"

#define CHUNK 1024
int main() {
    char input[10000], ch, result[100][10000];
    int inputChoice;
    int op = 1;
    FILE *fp;
    size_t nread;
    int fgets_count = 0;
    while (op) {
        printf("请输入1 或者 2， 0退出");  //从文件导入或是直接读入，0退出
        scanf("%d", &inputChoice);
        if (inputChoice == 1) {    //处理文件导入

            if ((fp = fopen("testinput.txt", "r")) == NULL) {
                printf("not open\n");

            } else { //成功打开文件
//                while ((ch = fgetc(fp)) != EOF ) /* 从文件读一字符，显示到屏幕*/
//                    putchar(ch);
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