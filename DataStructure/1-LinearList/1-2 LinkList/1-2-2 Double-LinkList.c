// 1-2-2

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
    Ptr Prev, Next;
};

struct LinkList{
    Ptr Head, Tail;
    int Length;
};

//High-level functions
PtrL InitList();
void PrintList(PtrL L);
bool InsertNode(PtrL L);
bool FindNode(PtrL L);
bool UpdeteNode(PtrL L);
bool DeleteNode(PtrL L);
void ClearList(PtrL L);
void DestoryList(PtrL L);

//Low-level functions
bool IsEmpty(PtrL L);
bool IsFull(PtrL L);
int GetLength(PtrL L);
bool CheckIndex(PtrL L, int Index);
bool CheckInsertIndex(PtrL L, int Index);
Ptr GetNode(PtrL L, int Index);
//DoubleList dont need GetPrevNode
DataType GetData(Ptr P);
bool SetData(Ptr P, DataType Data);
Ptr CreateNode(DataType Data);
bool InsertHead(PtrL L, Ptr P);
bool InsertTail(PtrL L, Ptr P);
bool InsertAtIndex(PtrL L, int Index, Ptr P);
bool DeleteHead(PtrL L);
bool DeleteTail(PtrL L);
bool DeleteAtIndex(PtrL L, int Index);

int main(){
    int chioce = -1;
    PtrL L = InitList();
    while (chioce){
        printf("1. PrintList\n");
        printf("2. Length\n");
        printf("3. Insert\n");
        printf("4. Find\n");
        printf("5. Update\n");
        printf("6. Delete\n");
        printf("7. ClearList\n");
        printf("0. Exit\n");
        scanf("%d", &chioce);
        switch (chioce){
            case 1: PrintList(L); break;
            case 2: printf("Length:%d\n",GetLength(L)); break;
            case 3: InsertNode(L); break;
            case 4: FindNode(L); break;
            case 5: UpdeteNode(L); break;
            case 6: DeleteNode(L); break;
            case 7: ClearList(L); break;
            case 0: DestoryList(L); break;
            default: printf("Invalid input!\n");
        }
    }
    return 0;
}

//High-level functions
PtrL InitList(){
    PtrL L = (PtrL)malloc(sizeof(struct LinkList));
    L->Head = NULL;
    L->Tail = NULL;
    L->Length = 0;
    return L;
}
void PrintList(PtrL L){
    Ptr p = L->Head;
    while(p != NULL){
        printf("%d ", p->Data);
        p = p->Next;
    }
    printf("\n");
}
bool InsertNode(PtrL L){
    int index;
    DataType data;
    printf("Enter the index to insert: ");
    scanf("%d", &index);
    printf("Enter the element to insert: ");
    scanf("%d", &data);
    Ptr p = CreateNode(data);
    if(p == NULL){
        printf("Memory allocation failed!\n");
        return false;
    }
    if(index == 0){
        return InsertHead(L, p);
    }
    else if(index == L->Length){
        return InsertTail(L, p);
    }
    else{
        return InsertAtIndex(L, index, p);
    }
}
bool FindNode(PtrL L){
    int index;
    printf("Enter the index to find: ");
    scanf("%d", &index);
    Ptr p = GetNode(L, index);
    if( p == NULL) {
        printf("Node not found!\n");
        return false;
    }
    printf("Data at index %d is %d\n", index, GetData(p));
    return true;
}
bool UpdeteNode(PtrL L){
    int index;
    DataType data;
    printf("Enter the index to update: ");
    scanf("%d", &index);
    printf("Enter the new element: ");
    scanf("%d", &data);
    Ptr p = GetNode(L, index);
    if(p == NULL){
        return false;
    }
    return SetData(p, data);
}
bool DeleteNode(PtrL L){
    int index;
    printf("Enter the index to delete: ");
    scanf("%d", &index);
    if(CheckIndex(L, index) == false){
        printf("Invalid index!\n");
        return false;
    }
    if(index == 0){
        return DeleteHead(L);
    }
    else if(index == L->Length - 1){
        return DeleteTail(L);
    }
    else{
        return DeleteAtIndex(L, index);
    }
}
void ClearList(PtrL L){
    while (L!=NULL && !IsEmpty(L)){
        DeleteHead(L);
    }
}
void DestoryList(PtrL L){
    ClearList(L);
    free(L);
}


//
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
    return P->Data;
}
Ptr GetNode(PtrL L, int Index){
    if(CheckIndex(L, Index) == false){
        return NULL;
    }
    Ptr p = L->Head;
    for(int i = 0; i < Index; i++){
        p = p->Next;
    }
    return p;
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
    if(p == NULL){
        return NULL;
    }
    p->Data = Data;
    p->Prev = NULL;
    p->Next = NULL;
    return p;
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
        L->Head->Prev = P;
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
        P->Prev = L->Tail;
        L->Tail->Next = P;
        L->Tail = P;
    }
    L->Length++;
    return true;
}
bool InsertAtIndex(PtrL L, int Index, Ptr P){
    if(IsFull(L)||P==NULL||CheckInsertIndex(L, Index) == false){
        return false;
    }
    Ptr p = GetNode(L, Index);
    P->Next = p;
    P->Prev = p->Prev;
    p->Prev->Next = P;
    p->Prev = P;
    L->Length++;
    return true;
}
bool DeleteHead(PtrL L){
    if(IsEmpty(L)){
        return false;
    }
    else if(L->Length == 1){
        free(L->Head);
        L->Head = NULL;
        L->Tail = NULL;
    }
    else{
        Ptr head = L->Head;
        L->Head = L->Head->Next;
        L->Head->Prev = NULL;
        free(head);
    }
    L->Length--;
    return true;
}
bool DeleteTail(PtrL L){
    if(IsEmpty(L)){
        return false;
    }
    else if(L->Length == 1){
        free(L->Tail);
        L->Head = NULL;
        L->Tail = NULL;
    }
    else{
        Ptr tail = L->Tail;
        L->Tail = L->Tail->Prev;
        L->Tail->Next = NULL;
        free(tail);
    }
    L->Length--;
    return true;
}
bool DeleteAtIndex(PtrL L, int Index){
    if(IsEmpty(L)||CheckIndex(L, Index) == false){
        return false;
    }
    Ptr p = GetNode(L, Index);
    if(L->Length > 1){
        p->Next->Prev = p->Prev;
        p->Prev->Next = p->Next;
    }
    L->Length--;
    free(p);
    return true;
}