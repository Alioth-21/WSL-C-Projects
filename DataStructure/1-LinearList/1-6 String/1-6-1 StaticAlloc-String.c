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
bool IsEmpty(PtrS S);
int GetLength(PtrS S);
void PrintStr(PtrS S);
void InputStr(PtrS S);
void ClearStr(PtrS S);

bool StrAssign(char* dest, char* str, int* len);
bool StrCopy(PtrS S, PtrS T);                       // Copy string S to T
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
    //
    printf("Clear s2\n");
    ClearStr(&s2);
    PrintStr(&s2);

    // copy
    printf("Copy s1 to s3\n");
    StrCopy(&s1, &s3);
    PrintStr(&s3);

    //Assign
    printf("Assign \"Hello\" to s2\n");
    StrAssign(s2.Data, "Hello", &s2.Length);
    PrintStr(&s2);

    //compare
    printf("Compare s1 and s2: %d\n", StrCompare(&s1, &s2));

    // substring: s3 = s2[0:2]
    printf("Substring s2[](pos=0, len=3) to s3, print s3\n");
    SubStr(&s3, &s2, 0, 3);
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
bool IsEmpty(PtrS S){
    return S->Length == 0;
}
int GetLength(PtrS S){
    return S->Length;
}
void PrintStr(PtrS S){
    printf("PrintString: ");
    char* p = S->Data;
    while(*p != '\0'){
        printf("%c", *p);
        p++;
    }
    printf("\n");
}

void InputStr(PtrS S){
    printf("input to str:");
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


bool StrAssign(char* dest, char* str, int* len){  //str assign to dest[MAXSIZE]
    int i = 0;
    while(str[i] != '\0' && i < MAXSIZE-1){
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    *len = i;
    return true;
}
bool StrCopy(PtrS S, PtrS T){
    if(S==NULL || T==NULL){
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
    else S->Length = S1->Length + S2->Length;
    for(int i=0; i<S1->Length; i++){
        S->Data[i] = S1->Data[i];
    }
    for(int i=0; i<S2->Length; i++){
        S->Data[S1->Length + i] = S2->Data[i];
    }
    S->Data[S->Length] = '\0';
    return true;
}


