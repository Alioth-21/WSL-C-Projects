// 1-2-3 Circular-SLinkList.c
// Circular Singly Linked List in C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 5

typedef int DataType;
typedef struct Node* Ptr;
typedef struct CSLinkList* PtrL;

struct Node{
    DataType Data;
    Ptr Next;
};

struct CSLinkList{
    Ptr Head, Tail;
    int Length;
};

// Function
PtrL InitList();
void PrintList(PtrL L);
bool InsertNode(PtrL L);
bool FindNode(PtrL L);
bool UpdateNode(PtrL L);
bool DeleteNode(PtrL L);
void ClearList(PtrL L);
void DestroyList(PtrL L);

//
bool IsEmpty(PtrL L);
bool IsFull(PtrL L);
int GetLength(PtrL L);
Ptr GetNode(PtrL L, int Index);
DataType GetData(Ptr P);
bool SetData(Ptr p, DataType Data);
Ptr CreateNode(DataType Data);
bool InsertHead(PtrL L, Ptr P);
bool InsertTail(PtrL L, Ptr P);
bool InsertAt(PtrL L, Ptr P, int Index);
bool DeleteHead(PtrL L);
bool DeleteTail(PtrL L);
bool DeleteAt(PtrL L, int Index);

int main() {
    int choice = -1;
    PtrL L = InitList();
    while (choice)  {
        printf("1. PrintList\n");
        printf("2. Length\n");
        printf("3. Insert\n");
        printf("4. Find\n");
        printf("5. Update\n");
        printf("6. Delete\n");
        printf("7. Clear\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: PrintList(L); break;
            case 2: printf("Length: %d\n", GetLength(L)); break;
            case 3: InsertNode(L); break;
            case 4: FindNode(L); break;
            case 5: UpdateNode(L); break;
            case 6: DeleteNode(L); break;   
            case 7: ClearList(L); break;
            case 0: DestroyList(L); break;
            default: printf("Invalid input!\n");
        }
    }
    return 0;
}

PtrL InitList(){
    PtrL L = (PtrL)malloc(sizeof(struct CSLinkList));
    if(L == NULL){
        return NULL;
    }
    L->Head = NULL;
    L->Tail = NULL;
    L->Length = 0;
    return L;
}
void PrintList(PtrL L){
    Ptr p = L->Head;
    for(int i = 0; i < L->Length; i++){
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
    if(index == 0){
        return InsertHead(L, p);
    }
    else if(index == L->Length){
        return InsertTail(L, p);
    }
    else{
        return InsertAt(L, p, index);
    }
}
bool FindNode(PtrL L){
    int index;
    printf("Enter the index to find: ");
    scanf("%d", &index);
    Ptr p = GetNode(L, index);
    if( index<0 || index>=L->Length || (p == NULL)){
        printf("Invalid index!\n");
        return false;
    }
    printf("Element at index %d is: %d\n", index, p->Data);
    return true;
}
bool UpdateNode(PtrL L){
    int index;
    DataType data;
    printf("Enter the index to update: ");
    scanf("%d", &index);
    printf("Enter the new element: ");
    scanf("%d", &data);
    Ptr p = GetNode(L, index);
    if( index<0 || index>=L->Length || (p == NULL)){
        printf("Invalid index!\n");
        return false;
    }
    return SetData(p, data);
}
bool DeleteNode(PtrL L){
    int index;
    printf("Enter the index to delete: ");
    scanf("%d", &index);
    if(index == 0){
        return DeleteHead(L);
    }
    else if(index == L->Length - 1){
        return DeleteTail(L);
    }
    else{
        return DeleteAt(L, index);
    }
}
void ClearList(PtrL L){
    while (L!=NULL && !IsEmpty(L)){
        DeleteHead(L);
    }
}
void DestroyList(PtrL L){
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
Ptr GetNode(PtrL L, int Index){
    if(IsEmpty(L) || Index<0 || Index>=L->Length){
        return NULL;
    }
    Ptr p = L->Head;
    for(int i = 0; i < Index; i++){
        p = p->Next;
    }
    return p;
}
DataType GetData(Ptr P){
    return P->Data;
}
bool SetData(Ptr p, DataType Data){
    if(p == NULL){
        return false;
    }
    p->Data = Data;
    return true;
}
Ptr CreateNode(DataType Data){
    Ptr p = (Ptr)malloc(sizeof(struct Node));
    if(p == NULL){
        return NULL;
    }
    p->Data = Data;
    p->Next = NULL;
    return p;
}
bool InsertHead(PtrL L, Ptr P){
    if (IsFull(L) || P == NULL) {
        return false;
    }
    if(IsEmpty(L)) {
        L->Head = P;
        L->Tail = P;
        P->Next = P; // Point to itself
    } 
    else {
        P->Next = L->Head;
        L->Tail->Next = P; // Tail points to new head
        L->Head = P; // Update head
    }
    L->Length++;
    return true;
}
bool InsertTail(PtrL L, Ptr P){
    if (IsFull(L) || P == NULL) {
        return false;
    }
    P->Next = L->Head;
    L->Tail->Next = P;
    L->Tail = P;
    L->Length++;
    return true;
}
bool InsertAt(PtrL L, Ptr P, int Index){
    if(IsFull(L) || P==NULL || Index<=0 || Index>=L->Length ){
        return false;
    }
    Ptr prev = GetNode(L, Index-1);
    P->Next = prev->Next; 
    prev->Next = P;
    L->Length++;
    return true;
}
bool DeleteHead(PtrL L){
    if(IsEmpty(L)){
        return false;
    }
    if(L->Length == 1){
        free(L->Head);
        L->Head = NULL;
        L->Tail = NULL;
    }
    else{
        Ptr head = L->Head;
        L->Head = L->Head->Next;
        L->Tail->Next = L->Head; // Update tail's next to new head
        free(head);
    }
    L->Length--;
    return true;
}
bool DeleteTail(PtrL L){
    if(IsEmpty(L)){
        return false;
    }
    Ptr prev = GetNode(L, L->Length - 2);
    free(L->Tail);
    L->Tail = prev;
    L->Tail->Next = L->Head;
    L->Length--;
    return true;
}
bool DeleteAt(PtrL L, int Index){
    if (IsEmpty(L) || Index<0 || Index>=L->Length) {
        return false;
    }
    Ptr prev = GetNode(L, Index - 1);
    Ptr del = prev->Next;
    prev->Next = del->Next;
    free(del);
    L->Length--;
    return true;
}