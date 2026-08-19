// 1-6-6 KMP-index.c
// This is the KMP pattern matching algorithm with index-based next array implementation
// The next array is built using index-based approach, where next[i] indicates the length of the longest proper prefix which is also a suffix for the substring p[0..i].

#include <stdio.h>
#include <string.h>

void SetNext(char *p, int *next) {
    int len = strlen(p);
    next[0] = -1;
    int i = 0, j = -1;

    while (i < len - 1) {
        if (j == -1 || p[i] == p[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

int kmpSearch(char *s, char *p, int *next) {
    int sLen = strlen(s);
    int pLen = strlen(p);
    int i = 0, j = 0;

    while (i < sLen && j < pLen) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }

    return (j == pLen) ? (i - j) : -1;
}

int main() {
    char s[] = "ABABABABC";
    char p[] = "ABABC";
    int next[strlen(p)];

    SetNext(p, next);

    // 打印 next 数组（下标型）
    printf("next: ");
    for (int i = 0; i < strlen(p); i++) {
        printf("%d ", next[i]);
    }
    printf("\n");

    int pos = kmpSearch(s, p, next);
    printf("Pattern found at: %d\n", pos);

    return 0;
}