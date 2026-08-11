// 1-6-1 StaticAlloc-String
// Static Storage Representation

#include<stdio.h>
#include<stdbool.h>
#define MAXSIZE 20

typedef struct{
    char Data[MAXSIZE];
    int Length;
}Str, *PtrS;

void InitStr(PtrS S);
void PrintStr(PtrS S);

bool StrAssign(PtrS S, char* str);
bool StrCopy(PtrS S, PtrS T);
bool StrEmpty(PtrS S);

int StrCompare(PtrS S, PtrS T);
int StrLength(PtrS S);
bool SubStr(PtrS Sub, PtrS S, int pos, int len);

bool Concat(PtrS S, PtrS S1, PtrS S2);
int Index(PtrS S, PtrS T);
void ClearStr(PtrS S);
void DestoryStr(PtrS S);



int main(){
    return 0;
}