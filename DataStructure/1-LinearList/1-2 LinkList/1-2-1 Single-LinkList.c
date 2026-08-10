// 1-2-1 Single-LinkList.c

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 5
#define NotFound -1

typedef int DataType;
typedef struct Node* Ptr;
typedef struct LinkList* PtrL;

struct Node{
    DataType Data;
    Ptr Next;
};

struct LinkList{
    Ptr Head, Tail;
    int Length;
};

//basic operations
PtrL InitList();
bool IsEmpty(PtrL L);
bool IsFull(PtrL L);
int GetLength(PtrL L);
bool CheckIndex(PtrL L, int Index);
bool CheckInsertIndex(PtrL L, int Index);
DataType GetData(Ptr P);
Ptr GetNode(PtrL L, int Index);
Ptr GetPrevNode(PtrL L, int index);//get prev node address
bool SetData(Ptr P, DataType Data);
Ptr CreateNode(DataType Data);
bool DeleteAtIndex(PtrL L, int Index);
bool InsertHead(PtrL L, Ptr P);
bool InsertTail(PtrL L, Ptr P);
bool InsertAtIndex(PtrL L, int Index, Ptr P);

//operations
void PrintList(PtrL L);
bool Insert(PtrL L);
int FindByData(PtrL L);
DataType FindByIndex(PtrL L);
bool UpdeteNode(PtrL L);
bool DeleteNode(PtrL L);
void ClearList(PtrL L);
void DestoryList(PtrL L);

int main(){
    int chioce = -1;
    PtrL L = InitList();
    while (chioce){
        printf("1. PrintList\n2. ListLength\n3. Insert\n4. FindByData\n5. FindByIndex\n6. Update\n7. Delete\n8. ClearList\n0. Exit\n");
        scanf("%d", &chioce);
        switch (chioce){
            case 1: PrintList(L); break;
            case 2: printf("Length:%d\n",GetLength(L)); break;
            case 3: Insert(L); break;
            case 4: FindByData(L); break;
            case 5: FindByIndex(L); break;
            case 6: UpdeteNode(L); break;
            case 7: DeleteNode(L); break;
            case 8: ClearList(L); break;
            case 0: DestoryList(L); break;
            default: printf("Invalid input!\n");
        }
    }
    return 0;
}

PtrL InitList(){
    PtrL L = (PtrL)malloc(sizeof(struct LinkList));
    L->Head = NULL;
    L->Tail = NULL;
    L->Length = 0;
    return L;
}
bool IsEmpty(PtrL L){
    return L->Length == 0;
}
bool IsFull(PtrL L){
    return L->Length == MAXSIZE;
}
int GetLength(PtrL L){
    return L->Length;
}
bool CheckIndex(PtrL L, int Index){
    return Index >= 0 && Index < L->Length;
}
bool CheckInsertIndex(PtrL L, int Index){
    return Index >= 0 && Index <= L->Length;
}
DataType GetData(Ptr P){
    if(P == NULL){
        printf("Node is NULL!\n");
        return NotFound;
    }
    return P->Data;
}
Ptr GetNode(PtrL L, int Index){
    if(!CheckIndex(L, Index)){
        return NULL;
    }
    Ptr P = L->Head;
    for(int i = 0; i < Index; i++){
        P = P->Next;
    }
    return P;
}
Ptr GetPrevNode(PtrL L, int index){//get prev node address
    if(index <= 0){
        return NULL;
    }
    return GetNode(L, index - 1);
}
bool SetData(Ptr P, DataType Data){
    if(P == NULL){
        return false;
    }
    P->Data = Data;
    return true;
}
Ptr CreateNode(DataType Data){
    Ptr p = (Ptr)malloc(sizeof(struct Node));
    if (p==NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    p->Data = Data;
    p->Next = NULL;
    return p;
}
bool DeleteAtIndex(PtrL L, int Index){
    if(!CheckIndex(L, Index)){
        printf("Invalid index!\n");
        return false;
    }
    
    Ptr prev = GetPrevNode(L, Index);
    Ptr dp = GetNode(L, Index);
    if(L->Length == 1){             // If there's only one node
        L->Head = NULL;
        L->Tail = NULL;
    }
    else if(Index == 0){            // If deleting the head node
        L->Head = dp->Next;
    }
    else{                           // Deleting other node
        prev->Next = dp->Next;
        if(Index == L->Length - 1){ // If deleting the tail node
            L->Tail = prev;
        }
    }
    
    free(dp);
    L->Length--;
    return true;
}
bool InsertHead(PtrL L, Ptr P){
    if(IsFull(L)||P==NULL){
        return false;
    }
    
    if(IsEmpty(L)){
        L->Head = P;
        L->Tail = P;
    }
    else{
        P->Next = L->Head;
        L->Head = P;    
    }
    L->Length++;
    return true;
}
bool InsertTail(PtrL L, Ptr P){
    if(IsFull(L)||P==NULL){
        return false;
    }

    if(IsEmpty(L)){
        L->Head = P;
        L->Tail = P;
    }
    else{
        L->Tail->Next = P;
        L->Tail = P; 
    }
    L->Length++;
    return true;
}
bool InsertAtIndex(PtrL L, int Index, Ptr P){
    if(IsFull(L) || P==NULL || !CheckInsertIndex(L, Index)){
        return false;
    }
    if(IsEmpty(L)){          // 独立调用时空表兜底
        L->Head = P;
        L->Tail = P;
    }
    else{
        Ptr prev = GetPrevNode(L, Index);
        P->Next = prev->Next;
        prev->Next = P;
    }
    L->Length++;
    return true;
}


//operations
void PrintList(PtrL L){
    Ptr p = L->Head;
    while(p != NULL){
        printf("%d ", p->Data);
        p = p->Next;
    }
    printf("\n");
}
bool Insert(PtrL L){
    if (IsFull(L)){
        printf("List is full!\n");
        return false;
    }

    int Index;
    DataType Data;
    printf("Enter the index to insert: ");
    scanf("%d", &Index);
    printf("Enter the element to insert: ");
    scanf("%d", &Data);

    if(CheckInsertIndex(L, Index) == false){
        printf("Invalid index!\n");
        return false;
    }

    Ptr p = CreateNode(Data);
    if (p == NULL) {
        return false;
    }

    if (Index == 0){
        return InsertHead(L, p);
    }
    else if(Index==L->Length){
        return InsertTail(L, p);
    }
    else{
        return InsertAtIndex(L, Index, p);
    }
}
int FindByData(PtrL L){
    DataType Data;
    printf("Enter the element to find: ");
    scanf("%d", &Data);
    for(int i = 0; i < L->Length; i++){
        if(GetData(GetNode(L, i)) == Data){
            printf("Dataent %d found at index %d\n", Data, i);
            return i;
        }
    }
    printf("Dataent %d not found!\n", Data);
    return NotFound;
}
DataType FindByIndex(PtrL L){
    int Index;
    printf("Enter the index to find: ");
    scanf("%d", &Index);
    if(CheckIndex(L, Index) == false){
        printf("Invalid index!\n");
        return NotFound;
    }
    DataType Data = GetData(GetNode(L, Index));
    printf("Dataent at index %d is %d\n", Index, Data);
    return Data;
}
bool UpdeteNode(PtrL L){
    int Index;
    DataType Data;
    printf("Enter the index to update: ");
    scanf("%d", &Index);
    printf("Enter the new element: ");
    scanf("%d", &Data);
    if(CheckIndex(L, Index) == false){
        printf("Invalid index!\n");
        return false;
    }
    return SetData(GetNode(L, Index), Data);
}
bool DeleteNode(PtrL L){
    if(IsEmpty(L)){
        printf("List is empty!\n");
        return false;
    }

    int Index;
    printf("Enter the index to delete: ");
    scanf("%d", &Index);
    
    return DeleteAtIndex(L, Index);
}
void ClearList(PtrL L){
    while(!IsEmpty(L)){
        DeleteAtIndex(L, 0);   // 从头删到尾,不弹输入框
    }
}
void DestoryList(PtrL L){
    ClearList(L);
    free(L);
}