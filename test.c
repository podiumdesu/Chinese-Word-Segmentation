#include <stdio.h>

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

int main (void) {
    char a[3] = "王";
    char b[3] = "ddd";
    char c[3] = "11";
    printf("%d", check(*a));
    printf("%d", check("，"));
    printf("%d", check(*b));
    printf("%d", check(*c));
    return 0;
}
