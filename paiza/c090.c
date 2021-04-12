#include <stdio.h>
#include <string.h>

int main(void){
    // 自分の得意な言語で
    // Let's チャレンジ！！
    int i;
    int len = 0;
    int sum = 0;
    int num = 0;
    char str[1000];
    
    
    fgets(str, sizeof(str), stdin);
    len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == '-') {
            continue;
        }
        
        num = str[i] - '0';
        if (num == 0) {
            sum += (12 * 2);
        }
        else if (num >0 && num < 10) {
            sum += (num + 2) * 2;
        }
    }
    
    printf("%d", sum);
    return 0;
}