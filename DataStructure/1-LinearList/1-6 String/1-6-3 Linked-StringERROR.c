// 1-6-3 Linked-String
// Block-Chain Storage Representation

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 20
#define NODE_SIZE 10

typedef char DataType;
typedef DataType* Ptdata;
typedef struct Node{
    DataType Data[NODE_SIZE];
    struct Node *Next;
}Node, *Ptr;
typedef struct{
    Ptr Head;
    int Length;
}Str, *PtrS;


//functions:
void PrintNode(Ptr N);
int NodeLength(Ptr N);
Ptr CreateNode();
bool DeleteNode(PtrS S, int pos);
bool CopyNode(Ptr dest, Ptr str);
bool AssignStr(Ptdata dest, Ptdata str, int len);
Ptr StrToNode(Ptdata str);
int StrLen(Ptdata str);

PtrS InitStr();
bool IsEmpty(PtrS S);
bool IsFull(PtrS S);
int StrLength(PtrS S);
void PrintStr(PtrS S);
void InputStr(PtrS S);
bool StrCopy(PtrS S, PtrS T);                   // Copy T to S 
bool Concat(PtrS S, PtrS S1, PtrS S2);          // Concatenate S1 and S2 to S
void ClearStr(PtrS S);
void DestroyStr(PtrS S);

// int Index(PtrS S, PtrS T);   // 返回子串T在主串S中的位置，若不存在则返回0

int main(){
    //init str
    PtrS s1 = InitStr();
    PtrS s2 = InitStr();

    printf("test IsEmpty:%d",IsEmpty(s1));

    //input
    InputStr(s1);
    PrintStr(s1);
    PrintStr(s2);

    //copy
    StrCopy(s2, s1);
    PrintStr(s2);


    return 0;
}
void PrintNode(Ptr N){
    int len = NodeLength(N);
    for(int i=0; i<len; i++){
        printf("%c", N->Data[i]);
    }
    printf("\n");
}
int NodeLength(Ptr N){
    if(N->Data[NODE_SIZE - 1] == '\0'){
        return NODE_SIZE;
    }
    int len = 0;
    for(len=0; len<NODE_SIZE; len++){
        if(N->Data[len] == '\0'){
            break;
        }
    }
    return len;
}
Ptr CreateNode(){
    Ptr p = (Ptr)malloc(sizeof(Node));
    if(p==NULL) return NULL;
    p->Next = NULL;
    p->Data[0] = '\0';
    return p;
}
bool DeleteNode(PtrS S, int pos){
    if(IsEmpty(S) || pos<0 || pos>=S->Length){
        return false;
    }
    Ptr q = S->Head;
    for(int i = 0; i < pos; i++){
        q = q->Next;
    }
    free(q);
    return true;
}
bool CopyNode(Ptr dest, Ptr str){
    int len = StrLen(str->Data);
    if(len<1) return false;
    dest->Next = str->Next;
    AssignStr(dest->Data, str->Data, StrLen(len));
    return true;
}
bool AssignStr(Ptdata dest, Ptdata str, int len){ // dest.size >= str.size
    if(dest==NULL || str==NULL || len<=0){
        return false;
    }
    for(int i=0; i<len; i++){
        dest[i] = str[i];
    }
    return true;
}
Ptr StrToNode(Ptdata str){
    int len = StrLen(str);
    int num = len%NODE_SIZE==0? len/NODE_SIZE : len/NODE_SIZE + 1;
    Ptr head = NULL, p = NULL;
    for(int i=0; i<num; i++){
        if(p==NULL){
            p = CreateNode();
            head = p;
        }
        else{
            p->Next = CreateNode();
            p = p->Next;
        }
        AssignStr(p->Data, str+NODE_SIZE*i, NODE_SIZE);
    }
    return head;
}
int StrLen(Ptdata str){
    Ptdata p = str;
    int len=0;
    while (p[len] != '\0') {
        len++;
    }
    return len;
}

PtrS InitStr(){
    PtrS S = (PtrS)malloc(sizeof(Str));
    S->Head = NULL;
    S->Length = 0;
    return S;
}
bool IsEmpty(PtrS S){
    return S->Length == 0;
}
bool IsFull(PtrS S){
    return S->Length == MAXSIZE;
}
int StrLength(PtrS S){
    return S->Length;
}
void PrintStr(PtrS S){
    Ptr p = S->Head;
    while(p != NULL){
        PrintNode(p);
        p = p->Next;
    }
}
void InputStr(PtrS S){
    if (IsFull(S)){
        printf("String is full\n");
        return;
    }
    printf("Input a string: ");
    DataType temp[MAXSIZE];
    fgets(temp, MAXSIZE, stdin);    
    S->Head = StrToNode(temp);
    S->Length = StrLen(temp);
}
bool StrCopy(PtrS S, PtrS T){
    ClearStr(S);
    Ptr sp = S->Head;
    Ptr tp = T->Head;
    while(1){
        if(sp==NULL){
            sp = CreateNode();
            S->Head = sp;
        }
        CopyNode(sp, tp);
        tp = tp->Next;
        if(tp==NULL) break;
        sp->Next = CreateNode();
        sp = sp->Next;
    }
    return true;
}
bool Concat(PtrS S, PtrS S1, PtrS S2){
    if(S1==NULL||S2==NULL){
        return false;
    }
    S->Length = S1->Length+S2->Length;
    Ptdata temp = (Ptdata)malloc(sizeof(DataType)*S->Length+1);
    S->Head = StrToNode(temp);
    return true; 
}
void ClearStr(PtrS S){
    if(IsEmpty(S)) return;
    Ptr q = S->Head;
    while(q!=NULL){
        free(q);
        S->Length--;
        S->Head = S->Head->Next;
        q = S->Head;
    }
}
void DestroyStr(PtrS S){
    ClearStr(S);
    free(S);
}