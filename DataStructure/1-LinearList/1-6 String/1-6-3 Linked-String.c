// 1-6-3 Linked-String
// Block-Chain Storage Representation

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define Max_Size 20
#define Block_Size 5

typedef char DataType;
typedef DataType* PtD;
typedef struct Node* Ptr;
struct Node{
    DataType Block[Block_Size];
    int Len;
    Ptr Next;
};
typedef struct{
    Ptr Head;
    int StrLen;
    int NodeNum;
}Str, *PtrS;


//functions:
Ptr CreateNode();  //创建一个新结点
bool DeleteNode(Ptr p);  //删除结点
int BlockLen(Ptr p);  //返回结点p中存储的字符数
bool AssignNode(Ptr S, PtD str, int size);  //将字符串str赋值给串S
bool CopyNode(Ptr S, Ptr T);  //将串T复制给串S
void PrintNode(Ptr S);  //输出串S

PtrS InitStr();  //初始化串
bool IsEmpty(PtrS S);  //判断串是否为空
int StrLength(PtrS S);  //返回串的长度
int NodeNum(PtrS S);  //返回串的结点数
void InputStr(PtrS S);  //输入串
bool StrToNode(PtrS S, char* str, int size);  //将字符串str转换为链式串S
void PrintStr(PtrS S);  //输出串
bool CopyStr(PtrS S, PtrS T);  //将串T复制给串S
bool Concat(PtrS S, PtrS T);  //将串T连接到串S的后面
void ClearStr(PtrS S);  //清空串S

// int Index(PtrS S, PtrS T);   // 返回子串T在主串S中的位置，若不存在则返回0

int main(){
    //init str
    PtrS s1 = InitStr();
    PtrS s2 = InitStr();

    //input
    InputStr(s1);
    printf("s1: node num = %d, str len = %d\n", NodeNum(s1), StrLength(s1));
    PrintStr(s1);

    InputStr(s2);
    PrintStr(s2);

    //copy
    CopyStr(s2, s1);
    printf("After copying s1 to s2:\n");
    PrintStr(s1);
    PrintStr(s2);

    //clear
    ClearStr(s1);
    printf("After clearing s1:\n");
    PrintStr(s1);

    //concat
    InputStr(s1);
    Concat(s1, s2);
    printf("After concatenating s2 to s1:\n");
    PrintStr(s1);


    return 0;
}

//functions:
Ptr CreateNode(){
    Ptr p = (Ptr)malloc(sizeof(struct Node));
    if(p == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    p->Len = 0;
    p->Next = NULL;
    return p;
}
bool DeleteNode(Ptr p){
    if(p == NULL){
        return false;
    }
    free(p);
    return true;
}
int BlockLen(Ptr p){
    if(p == NULL){
        return -1;
    }
    return p->Len;
}
bool AssignNode(Ptr S, PtD str, int size){
    if(S==NULL || str==NULL || size<=0 || size>Block_Size){
        return false;
    }
    for(int i=0; i<size; i++){
        S->Block[i] = str[i];
    }
    S->Len = size;
    return true;
}
bool CopyNode(Ptr S, Ptr T){
    if(S==NULL || T==NULL){
        return false;
    }
    for(int i=0; i<T->Len; i++){
        S->Block[i] = T->Block[i];
    }
    S->Len = T->Len;
    //S->Next = T->Next;
    return true;
}
void PrintNode(Ptr S){
    if(S==NULL){
        printf("Node is NULL\n");
        return;
    }
    for(int i=0; i<S->Len; i++){
        printf("%c", S->Block[i]);
    }
}

PtrS InitStr(){
    PtrS S = (PtrS)malloc(sizeof(Str));
    if(S == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    S->Head = NULL;
    S->StrLen = 0;
    S->NodeNum = 0;
    return S;
}
bool IsEmpty(PtrS S){
    if(S == NULL){
        return true;
    }
    return S->StrLen == 0;
}
int StrLength(PtrS S){
    if(S == NULL){
        return -1;
    }
    return S->StrLen;
}
int NodeNum(PtrS S){
    if(S == NULL){
        return -1;
    }
    return S->NodeNum;
}
void InputStr(PtrS S){
    if(S == NULL){
        printf("String is NULL\n");
        return;
    }
    char buffer[Max_Size];
    printf("Enter a string (max %d characters): ", Max_Size);
    fgets(buffer, Max_Size, stdin);

    // 去掉末尾换行
    int count = 0;
    while(count < Max_Size && buffer[count] != '\0' && buffer[count] != '\n'){
        count++;
    }
    buffer[count] = '\0'; // 可加可不加，StrToNode 只用 count 个字符

    StrToNode(S, buffer, count);
}
bool StrToNode(PtrS S, char* str, int size){ //将字符串str转换为链式串S
    if(S == NULL || str == NULL || size <= 0 || size > Max_Size){
        return false;
    }
    S->StrLen = size;
    S->NodeNum = size/Block_Size + (size % Block_Size != 0 ? 1 : 0);
    Ptr p = NULL, np = NULL;
    for(int i=0; i<S->NodeNum; i++){
        np = CreateNode();

        int blockSize = (i == S->NodeNum - 1) ? (size - i*Block_Size) : Block_Size;
        AssignNode(np, str + i * Block_Size, blockSize);
        if(i==0){
            S->Head = np;
            p = S->Head;
        }
        else{
            p->Next = np;
            p = p->Next;
        }
    }
    return true;
}
void PrintStr(PtrS S){
    if(S == NULL){
        printf("String is NULL\n");
        return;
    }
    Ptr p = S->Head;
    while(p != NULL){
        PrintNode(p);
        p = p->Next;
    }
    printf("\n");
}

bool CopyStr(PtrS S, PtrS T){
    if(S == NULL || T == NULL){
        return false;
    }
    ClearStr(S);
    S->StrLen = T->StrLen;
    S->NodeNum = T->NodeNum;
    Ptr pT = T->Head;
    Ptr pS = NULL;
    Ptr prevS = NULL;
    while(pT != NULL){
        pS = CreateNode();
        CopyNode(pS, pT);
        if(prevS == NULL){
            S->Head = pS;
        }
        else{
            prevS->Next = pS;
        }
        prevS = pS;             
        pT = pT->Next;
    }
    return true;
}
bool Concat(PtrS S, PtrS T){
    if(S == NULL || T == NULL){
        return false;
    }
    Ptr pS = S->Head;
    if(pS == NULL){
        CopyStr(S, T);
        return true;
    }
    while(pS->Next != NULL){
        pS = pS->Next;
    }
    pS->Next = T->Head;
    S->StrLen += T->StrLen;
    S->NodeNum += T->NodeNum;
    return true;
}
void ClearStr(PtrS S){
    if(S == NULL){
        return;
    }
    Ptr p = S->Head;
    while(p != NULL){
        Ptr temp = p;
        p = p->Next;
        DeleteNode(temp);
    }
    S->Head = NULL;
    S->StrLen = 0;
    S->NodeNum = 0;
}