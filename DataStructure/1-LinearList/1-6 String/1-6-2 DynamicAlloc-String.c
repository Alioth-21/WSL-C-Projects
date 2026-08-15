// 1-6-2 DynamicAlloc-String.c

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 20
typedef struct{
    char* Data;
    int Length;
}Str, *PtrS;

//functions:
PtrS InitStr();
bool StrEmpty(PtrS S);
int StrLength(PtrS S);
void PrintStr(PtrS S);
void InputStr(PtrS S);
void ClearStr(PtrS S);
bool StrAssign(char* str, PtrS S);
bool StrCopy(PtrS S, PtrS T);
int StrCompare(PtrS S, PtrS T);
bool Concat(PtrS S, PtrS S1, PtrS S2);
// int Index(PtrS S, PtrS T);   // 返回子串T在主串S中的位置，若不存在则返回0

int main(){
    // Initialize strings
    PtrS s1 = InitStr();
    PtrS s2 = InitStr();
    PtrS s3 = InitStr();

    // Input and print strings
    InputStr(s1);
    PrintStr(s1);
    printf("Length of s1: %d\n", StrLength(s1));
    InputStr(s2);
    PrintStr(s2);
    printf("Length of s2: %d\n", StrLength(s2));

    //copy
    StrCopy(s1, s3);
    PrintStr(s3);
    StrCopy(s2, s3);
    PrintStr(s3);

    //compare
    printf("Compare s1 and s2: %d\n", StrCompare(s1, s2));

    // concat
    Concat(s3, s1, s2);
    PrintStr(s3);


    return 0;
}

PtrS InitStr(){
    PtrS S = (PtrS)malloc(sizeof(Str));
    S->Data = NULL;
    S->Length = 0;
    return S;
}
bool StrEmpty(PtrS S){
    return S->Length == 0;
}
int StrLength(PtrS S){
    return S->Length;
}
void PrintStr(PtrS S){
    printf("Enter to String: ");
    char* p = S->Data;
    while(*p != '\0'){
        printf("%c", *p);
        p++;
    }
    printf("\n");
}
void InputStr(PtrS S){
    printf("Enter to String: ");
    char c;
    int size = 0;
    char temp[MAXSIZE];
    while((c = getchar()) != '\n' && size < MAXSIZE - 1){
        temp[size] = c;
        size++;
    }
    temp[size] = '\0';
    StrAssign(S, &temp);
}
bool StrAssign(char* str, PtrS S){
    if(S==NULL) {
        S= (PtrS)malloc(sizeof(Str));
    }
    free(S->Data);
    S->Data = (char*)malloc(MAXSIZE * sizeof(char));
    int i = 0;
    for(i = 0; str[i] != '\0'; i++) {
        if (i >= MAXSIZE - 1) break; // Exceeds maximum size
        S->Data[i] = str[i];
    }
    S->Length = i;
    S->Data[i] = '\0';
    return true;
}
bool StrCopy(PtrS S, PtrS T){
    if(S->Length < T->Length){
        return false;
    }
    int i = 0;
    while(i < S->Length){
        T->Data[i] = S->Data[i];
        i++;
    }
    T->Data[i] = '\0';
    T->Length = S->Length;
    return true;
}
int StrCompare(PtrS S, PtrS T){
    int i=0;
    for(i = 0; i < S->Length && i < T->Length; i++)
    if(S->Data[i] != T->Data[i]) break;
    return S->Data[i] - T->Data[i];
}
bool Concat(PtrS S, PtrS S1, PtrS S2){
    int sameLen = S1->Length + S2->Length;
    if(sameLen > MAXSIZE - 1){
        return false; // Concatenated string exceeds maximum size
    }
    S->Data = (char*)malloc((sameLen + 1) * sizeof(char));
    if(S->Data == NULL){
        return false; // Memory allocation failed
    }
    int i;
    for(i = 0; i < S1->Length; i++){
        S->Data[i] = S1->Data[i];
    }
    for(int j = 0; j < S2->Length; j++, i++){
        S->Data[i] = S2->Data[j];
    }
    S->Data[sameLen] = '\0';
    S->Length = sameLen;
    return true;
}
void ClearStr(PtrS S){
    if(S->Data != NULL){
        free(S->Data);
        S->Data = NULL;
    }
    S->Data = NULL;
    S->Length = 0;
}