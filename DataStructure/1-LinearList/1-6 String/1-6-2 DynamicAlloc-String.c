// 1-6-2 DynamicAlloc-String.c

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 20
#define SIZE 10

typedef char DataType;
typedef DataType* Ptr;
typedef struct{
    Ptr Data;
    int Length;
    int Capacity;
}Str, *PtrS;

//functions:
PtrS InitStr();
bool IsEmpty(PtrS S);
int GetLength(PtrS S);
void PrintStr(PtrS S);
void InputStr(PtrS S);
void ClearStr(PtrS S);

bool Resize(PtrS S, int size);                  //realloc memory for string S
bool StrAssign(Ptr dest, Ptr str, int len);     //str assign to S
bool StrCopy(PtrS S, PtrS T);                   // Copy T to S 
int StrCompare(PtrS S, PtrS T);
bool Concat(PtrS S, PtrS S1, PtrS S2);          // Concatenate S1 and S2 to S
// int Index(PtrS S, PtrS T);   // 返回子串T在主串S中的位置，若不存在则返回0

int main(){
    // Initialize strings
    PtrS s1 = InitStr();
    PtrS s2 = InitStr();
    PtrS s3 = InitStr();

    // Input and print strings
    InputStr(s1);
    PrintStr(s1);
    printf("Length of s1: %d\n", GetLength(s1));
    InputStr(s2);
    PrintStr(s2);
    printf("Length of s2: %d\n", GetLength(s2));

    //copy
    StrCopy(s3, s1);    //copy s1 to s3
    PrintStr(s3);
    

    //compare
    printf("Compare s1 and s2: %d\n", StrCompare(s1, s2));

    // concat
    Concat(s3, s1, s2);
    PrintStr(s3);


    DestroyStr(s1);
    return 0;
}

PtrS InitStr(){
    PtrS S = (PtrS)malloc(sizeof(Str));
    S->Data = NULL;
    S->Length = 0;
    S->Capacity = 0;
    return S;
}
bool IsEmpty(PtrS S){
    return S->Length == 0;
}
int GetLength(PtrS S){
    return S->Length;
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

    if(size > S->Capacity)  Resize(S, size + 1);
    
    StrAssign(S->Data, temp, size);
    S->Length = size;
}
bool Resize(PtrS S, int size){
    if (size<1 || size>MAXSIZE) return false; 
    free(S->Data);
    S->Length = 0;
    S->Capacity = size;
    S->Data = (Ptr)malloc(sizeof(DataType)*size);
    if(S->Data == NULL) return false;
    else return true;
}
bool StrAssign(Ptr dest, Ptr str, int len){  //str[len] assign to S
    if(dest == NULL || str == NULL || len < 1 || len >= MAXSIZE) {
        return false;
    }
    int i = 0;
    for(i = 0; i<len; i++) {
        if (str[i] == '\0') break; // Exceeds maximum size
        dest[i] = str[i];
    }
    dest[i] = '\0';
    return true;
}
void PrintStr(PtrS S){
    if(S==NULL || S->Data==NULL){
        printf("String is NULL\n");
        return;
    }
    printf("PrintStr: ");
    Ptr p = S->Data;
    while(*p != '\0'){
        printf("%c", *p);
        p++;
    }
    printf("\n");
}
bool StrCopy(PtrS S, PtrS T){
    if (S==NULL || T==NULL){
        return false;
    }
    
    if( S->Length < T->Length ){
        if(Resize(S, T->Length + 1)) printf("Resize Capacity\n");
        else return false;
    }

    StrAssign(S->Data, T->Data, T->Length);
    S->Length = T->Length;
    return true;
}
int StrCompare(PtrS S, PtrS T){
    if(S==NULL || T==NULL){
        return -1; // Error: one of the strings is NULL
    }
    int i=0;
    for(i = 0; i < S->Length && i < T->Length; i++)
    if(S->Data[i] != T->Data[i]) break;
    return S->Data[i] - T->Data[i];
}
bool Concat(PtrS S, PtrS S1, PtrS S2){
    int SLen = S1->Length + S2->Length;
    if(SLen<1 || SLen > MAXSIZE - 1){
        return false; 
    }
    else if(S->Capacity < SLen + 1){
        if(Resize(S, SLen + 1)) printf("Resize S to %d\n", SLen + 1);
        else return false;
    }
    for(int i = 0; i < S1->Length; i++){
        S->Data[i] = S1->Data[i];
    }
   for(int i = 0; i < S2->Length; i++){
        S->Data[S1->Length + i] = S2->Data[i];
    }
    S->Data[SLen] = '\0';
    S->Length = SLen;
    return true;
}
void ClearStr(PtrS S){
    if(S==NULL) return;
    if(S->Data != NULL) free(S->Data);
    free(S);
}