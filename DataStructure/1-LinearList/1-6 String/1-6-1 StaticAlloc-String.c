// 1-6-1 StaticAlloc-String
// Static Storage Representation
// String Last Element is '\0' and Length: [0, MAXSIZE-1]

#include<stdio.h>
#include<stdbool.h>
#define MAXSIZE 20

typedef struct{
    char Data[MAXSIZE];
    int Length;
}Str, *PtrS;

void InitStr(PtrS S);
bool StrEmpty(PtrS S);
int StrLength(PtrS S);
void PrintStr(PtrS S);
void InputStr(PtrS S);
void ClearStr(PtrS S);

bool StrAssign(PtrS S, char* str);
bool StrCopy(PtrS S, PtrS T);
int StrCompare(PtrS S, PtrS T);                     // 字典序比较字符串S和T的大小，若S>T则返回正数，若S<T则返回负数，若S=T则返回0
bool SubStr(PtrS Sub, PtrS S, int pos, int len);    // 子串Sub为串S的第pos个字符起长度为len的子串
bool Concat(PtrS S, PtrS S1, PtrS S2);
// int Index(PtrS S, PtrS T);   // 返回子串T在主串S中的位置，若不存在则返回0




int main(){
    Str s1, s2, s3;
    InitStr(&s1);
    InitStr(&s2);
    InitStr(&s3);

    //input and print
    InputStr(&s1);
    PrintStr(&s1);

    InputStr(&s2);
    PrintStr(&s2);
    ClearStr(&s2);
    PrintStr(&s2);

    // copy
    StrCopy(&s1, &s3);
    PrintStr(&s3);

    //compare
    StrAssign(&s2, "Hello");
    printf("Compare s1 and s2: %d\n", StrCompare(&s1, &s2));

    // substring
    SubStr(&s3, &s2, 0, 2);
    PrintStr(&s3);

    // concat
    ClearStr(&s3);
    Concat(&s3, &s1, &s2);
    PrintStr(&s3);

    return 0;
}

void InitStr(PtrS S){
    S->Data[0] = '\0';
    S->Length = 0;
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
    char c;
    int i = 0;
    while((c = getchar()) != '\n' && i < MAXSIZE - 1){
        S->Data[i] = c;
        i++;
    }
    S->Data[i] = '\0';
    S->Length = i;
}
void ClearStr(PtrS S){
    InitStr(S);
}


bool StrAssign(PtrS S, char* str){
    int i = 0;
    while(str[i] != '\0' && i < MAXSIZE-1){
        S->Data[i] = str[i];
        i++;
    }
    S->Data[i] = '\0';
    S->Length = i;
    return true;
}
bool StrCopy(PtrS S, PtrS T){
    if(S->Length != T->Length){
        return false;
    }
    int i = 0;
    while(i < S->Length){
        T->Data[i] = S->Data[i];
    }
    return true; 
}
int StrCompare(PtrS S, PtrS T){
    int i=0;
    for(i = 0; i < S->Length && i < T->Length; i++){
        if(S->Data[i] != T->Data[i]) break;
    }
    return S->Data[i] - T->Data[i];
}

bool SubStr(PtrS Sub, PtrS S, int pos, int len){
    if(pos< 0 || pos >= S->Length || len < 0 || len > S->Length - pos){
        return false;
    }
    for(int i=0; i<len; i++){
        Sub->Data[i] = S->Data[pos+i];
    }
    return true;
}

bool Concat(PtrS S, PtrS S1, PtrS S2){
    if(S1->Length + S2->Length > MAXSIZE - 1){
        return false;
    }
    for(int i=0; i<S1->Length; i++){
        S->Data[i] = S1->Data[i];
    }
    for(int i=0; i<S2->Length; i++){
        S->Data[S1->Length + i] = S2->Data[i];
    }
    return true;
}


