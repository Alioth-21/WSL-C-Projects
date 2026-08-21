// 1-6-5 KMP-length.c
// This is the KMP pattern matching algorithm with length-based next array implementation
// Standard KMP Algorithm

#include <stdio.h>
#include <string.h>

#define S_Empty -1
#define P_Empty -2
#define NotFound -3

void SetNext(const char* P, int* next, int len){
    if(len==0) return;
    next[0] = 0;
    int j=0;                     //j作为最长公共前后缀的长度 
    for(int i=1; i<len; i++){           //i作为主循环的循环变量，表示后缀的下标指针
        while(j>0 && P[i] != P[j]){     //回退
            j = next[j-1];
        }
        if(P[i] == P[j]){
            j++;                 //最长公共前后缀长度加1
        }
        next[i] = j;             //更新当前next数组元素
    }
}

int KMP(const char* S, const char* P, int next[]){
    //judge S and P is empty, print message
    int slen = strlen(S);
    int plen = strlen(P);
    if(slen == 0) return S_Empty;
    if(plen == 0) return P_Empty;

    int i = 0, j = 0;  // i: 主串指针，j: 模式串指针

    while(i<slen && j<plen){
        if(S[i] == P[j]){   //匹配成功，j后移
            i++;
            j++;                    
        }
        else if(j==0){  //模式串指针回到起点，主串指针后移
            i++;
        }
        else{           //模式串指针回退
            j = next[j-1];
        }
    }
    return (j==plen) ? (i-j) : NotFound;  //匹配成功返回主串下标，否则返回-3
}

void KMP_All(const char* S, const char* P, int next[]){
    int slen = strlen(S);
    int plen = strlen(P);
    if(slen == 0) return;
    if(plen == 0) return;

    int i = 0, j = 0;  // i: 主串指针，j: 模式串指针

    while(i<slen){
        if(S[i] == P[j]){   //匹配成功，j后移
            i++;
            j++;
            if(j==plen){ //匹配成功，输出位置
                printf("匹配成功，位置为: %d\n", i-j);
                j = next[j-1]; //继续寻找下一个匹配
            }
        }
        else if(j==0){  //模式串指针回到起点，主串指针后移
            i++;
        }
        else{           //模式串指针回退
            j = next[j-1];
        }
    }
}

void PrintNext(int* next, int len){
    printf("NextArray: ");
    for(int i=0; i<len; i++){
        printf("%d ", next[i]);
    }
    printf("\n");
}

int main(){
    char S[] = "aaabaaaab"; //"ababcabcacbab";
    char P[] = "aaaab";     //"abcac";
    
    int next[5];
    SetNext(P, next, 5);
    PrintNext(next, 5);
    
    int res=KMP(S, P, next);

    switch (res) {
        case S_Empty:
            printf("主串为空\n");
            break;
        case P_Empty:
            printf("模式串为空\n");
            break;
        case NotFound:
            printf("未找到匹配\n");
            break;
        default:
            printf("匹配成功，位置为: %d\n", res);
            break;
    }

    KMP_All(S, P, next);
    
    return 0;
}
