// 1-2-5 AoS-StaticLinkList.c
// Array of Structures, AoS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NODATA -1
#define MAXSIZE 5

typedef int DataType;
typedef struct Node* Ptr;
typedef struct SList* PtrL;

struct Node {
    DataType NodeData;
    int Next;
};

struct SList{   // Array of Structures, AoS
    struct Node Data[MAXSIZE];
    int Length;
    int Head, Tail;
};

//
PtrL InitList();
void PrintList(PtrL L);
bool InsertNode(PtrL L);
bool FindNode(PtrL L);
bool UpdateNode(PtrL L);
bool DeleteNode(PtrL L);
void ClearList(PtrL L);

bool IsEmpty(PtrL L);
bool IsFull(PtrL L);
int GetLength(PtrL L);
Ptr GetNode(PtrL L, int index);
int findFreeIndex(PtrL L);
bool InserHead(PtrL L, DataType data);
bool InsertTail(PtrL L, DataType data);
bool InsertAt(PtrL L, DataType data, int index);
bool DeleteHead(PtrL L);
bool DeleteTail(PtrL L);
bool DeleteAt(PtrL L, int index);

int main(){
    int choice = -1;
    PtrL L = InitList();

    while (choice!=0)  {
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
        switch (choice){
            case 1: PrintList(L); break;
            case 2: printf("Length: %d\n", GetLength(L)); break;
            case 3: InsertNode(L); break;
            case 4: FindNode(L); break;
            case 5: UpdateNode(L); break;
            case 6: DeleteNode(L); break;
            case 7: ClearList(L); break;
            case 0: break;
            default: printf("Invalid input!\n");
        }
    }

    return 0;
}

PtrL InitList(){
    PtrL L = (PtrL)malloc(sizeof(struct SList));
    for(int i=0; i<MAXSIZE; i++){
        L->Data[i].NodeData = NODATA;
        L->Data[i].Next = -1;
    }
    L->Head = -1;
    L->Tail = -1;
    L->Length = 0;
    return L;
}
void PrintList(PtrL L){
    printf("Storage of List:\n");
    printf("Index, Data, Next\n");
    for(int i=0; i<MAXSIZE; i++){
        printf(" %d, Data: %d, Next: %d\n", i, L->Data[i].NodeData, L->Data[i].Next);
    }
    printf("List : ");
    int i = L->Head;
    while(i != -1){
        printf("%d ", L->Data[i].NodeData);
        i = L->Data[i].Next;
        if(i == -1 || L->Data[i].NodeData == NODATA ){
            break;
        }
    }
    printf("\n");
}
Ptr GetNode(PtrL L, int index){
    if(index<0 || index>=L->Length){
        return NULL;
    }
    int pos = L->Head;
    for(int i=0; i<index; i++){
        pos = L->Data[pos].Next;
    }
    return &L->Data[pos];
}

bool FindNode(PtrL L){
    int index=0;
    printf("Enter the index to find: ");
    scanf("%d", &index);
    if(index<0 || index>=L->Length){
        printf("Invalid index!\n");
        return false;
    }
    Ptr p = GetNode(L, index);
    if(p == NULL){
        printf("Node not found!\n");
        return false;
    }
    printf("Element at index %d: %d\n", index, p->NodeData);
    return true;
}
bool UpdateNode(PtrL L){
    if(IsEmpty(L)){
        printf("List is empty!\n");
        return false;
    }
    int index=0;
    DataType data;
    printf("Enter the index to update: ");
    scanf("%d", &index);
    printf("Enter the new element: ");
    scanf("%d", &data);
    if(index<0 || index>=L->Length){
        printf("Invalid index!\n");
        return false;
    }
    Ptr p = GetNode(L, index);
    if(p == NULL){
        printf("Node not found!\n");
        return false;
    }
    p->NodeData = data;
    return true;
}
bool InsertNode(PtrL L){
    if(IsFull(L)) {
        printf("List is full!\n");
        return false;
    }
    int index=0;
    DataType data;
    printf("Enter the index to insert: ");
    scanf("%d", &index);
    printf("Enter the element to insert: ");
    scanf("%d", &data);
    if(index<0 || index>L->Length){
        printf("Invalid index!\n");
        return false;
    }
    if(index == 0){
        return InserHead(L, data);
    }
    else if(index == L->Length){
        return InsertTail(L, data);
    }
    else{
        return InsertAt(L, data, index);
    }
    return true;
}
bool DeleteNode(PtrL L){
    if(IsEmpty(L)){
        printf("List is empty!\n");
        return false;
    }
    int index=0;
    printf("Enter the index to delete: ");
    scanf("%d", &index);
    if(index<0 || index>=L->Length){
        printf("Invalid index!\n");
        return false;
    }
    if(index == 0){
        DeleteHead(L);
    }
    else if(index == L->Length - 1){
        DeleteTail(L);
    }
    else{
        DeleteAt(L, index);
    }
    return true;
}
void ClearList(PtrL L){
    while (!IsEmpty(L)){
        DeleteHead(L);
    }
}

bool IsEmpty(PtrL L){
    return (L->Length == 0);
}
bool IsFull(PtrL L){
    return (L->Length == MAXSIZE);
}
int GetLength(PtrL L){
    return L->Length;
}
int findFreeIndex(PtrL L){
    for(int i=0; i<MAXSIZE; i++){
        if(L->Data[i].NodeData == NODATA){
            return i;
        }
    }
    return -1; // No free index found
}

bool InserHead(PtrL L, DataType data){
    if (IsFull(L)) {
        return false;
    }
    int index = findFreeIndex(L);
    if(index == -1){
        return false;
    }
    L->Data[index].NodeData = data;
    L->Data[index].Next = L->Head;
    L->Head = index;
    if(L->Length == 0){
        L->Tail = index;
    }
    L->Length++;
    return true;
}
bool InsertTail(PtrL L, DataType data){
    if (IsFull(L)) {
        return false;
    }
    int index = findFreeIndex(L);
    if(index == -1){
        return false;
    }
    L->Data[index].NodeData = data;
    L->Data[index].Next = -1;
    if(L->Length == 0){
        L->Head = index;
        L->Tail = index;
    }
    else{
        L->Data[L->Tail].Next = index;
        L->Tail = index;
    }
    L->Length++;
    return true;
}
bool InsertAt(PtrL L, DataType data, int index){
    if(IsFull(L)){
        return false;
    }
    int prevIndex = L->Head;
    for(int i=0; i<index-1; i++){
        prevIndex = L->Data[prevIndex].Next;
    }
    int newIndex = findFreeIndex(L);
    if(newIndex == -1){
        return false;
    }
    L->Data[newIndex].NodeData = data;
    L->Data[newIndex].Next = L->Data[prevIndex].Next;
    L->Data[prevIndex].Next = newIndex;
    L->Length++;
    return true;
}
bool DeleteHead(PtrL L){
    if(IsEmpty(L)){
        return false;
    }
    int oldHead = L->Head;
    L->Head = L->Data[L->Head].Next;
    L->Data[oldHead].NodeData = NODATA; // Mark as free
    L->Data[oldHead].Next = -1;         // Reset next pointer
    L->Length--;
    if(L->Length == 0){
        L->Head = -1; // Reset head if list is empty
        L->Tail = -1; // Reset tail if list is empty
    }
    return true;
}
bool DeleteTail(PtrL L){
    if(IsEmpty(L)){
        return false;
    }
    if(L->Head==L->Tail){ // Only one element
        L->Data[L->Tail].NodeData = NODATA; // Mark as free
        L->Data[L->Tail].Next = -1;         // Reset next pointer
        L->Head = -1;
        L->Tail = -1;
        L->Length--;
        return true;
    }
    int prev = L->Head;
    while(prev != -1){
        if( L->Data[prev].Next == L->Tail){
            L->Data[prev].Next = -1; // Set the next of the previous node to -1
            break;
        }
        prev = L->Data[prev].Next;
    }
    L->Data[L->Tail].NodeData = NODATA; // Mark as free
    L->Data[L->Tail].Next = -1;         // Reset next pointer
    L->Tail = prev; // Update tail to the previous node
    L->Length--;
    return true;
}
bool DeleteAt(PtrL L, int index){
    if (IsEmpty(L) || index<0 || index>=L->Length){
        return false;
    }
    int prev = L->Head;
    for(int i=0; i<index-1; i++){
        prev = L->Data[prev].Next;
    }
    int del = L->Data[prev].Next;
    L->Data[prev].Next = L->Data[del].Next;
    L->Data[del].NodeData = NODATA; // Mark as free
    L->Data[del].Next = -1;         // Reset next pointer
    L->Length--;
    return true;
}

