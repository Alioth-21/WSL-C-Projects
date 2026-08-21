// 1-2-6 SoA-StaticLinkList.c
// Structure of Arrays, SoA

#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 5
#define NO_DATA -1

typedef int DataType;

typedef struct{
    DataType Data[MAXSIZE];
    int Next[MAXSIZE];
    int Length;
    int Head, Tail;
}SList, *PtrL;

//
bool InitList(PtrL L);
void PrintList(PtrL L);
bool InsertNode(PtrL L);
bool FindNode(PtrL L);
bool UpdateNode(PtrL L);
bool DeleteNode(PtrL L);
void ClearList(PtrL L);

bool IsEmpty(PtrL L);
bool IsFull(PtrL L);
int GetLength(PtrL L);
int GetIndex(PtrL L, int index);
int findFreeIndex(PtrL L);
bool InserHead(PtrL L, DataType data);
bool InsertTail(PtrL L, DataType data);
bool InsertAt(PtrL L, DataType data, int index);
bool DeleteHead(PtrL L);
bool DeleteTail(PtrL L);
bool DeleteAt(PtrL L, int index);

int main(){
    int choice = -1;
    SList list;
    PtrL L = &list;
    InitList(L);

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
        if(scanf("%d", &choice) != 1){
            while(getchar() != '\n');
            choice = -1;
            printf("Invalid input!\n");
            continue;
        }
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

bool InitList(PtrL L){
    if(L == NULL){
        return false;
    }
    for(int i=0; i<MAXSIZE; i++){
        L->Data[i] = NO_DATA;
        L->Next[i] = -1;
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
        printf(" [%d] Data: %d, Next: %d\n", i, L->Data[i], L->Next[i]);
    }
    printf("List : ");
    for(int i=0; i<L->Length; i++){
        printf("%d ", L->Data[GetIndex(L, i)]);
    }
    printf("\n");
}
int GetIndex(PtrL L, int index){
    if(L==NULL || index<0 || index>=L->Length){
        return -1;
    }
    int pos = L->Head;
    for(int i=0; i<index; i++){
        pos = L->Next[pos];
    }
    return pos;
}

bool FindNode(PtrL L){
    int index=0;
    printf("Enter the index to find: ");
    scanf("%d", &index);
    if(index<0 || index>=L->Length){
        printf("Invalid index!\n");
        return false;
    }
    int pos = GetIndex(L, index);
    printf("Element at index %d pos[%d] Data=%d Next=%d\n", index, pos, L->Data[pos], L->Next[pos]);
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
    int pos = GetIndex(L, index);
    if(pos == -1){
        printf("Node not found!\n");
        return false;
    }
    L->Data[pos] = data;
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
    else if(L->Length !=0 && index == L->Length){
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
    else if(index!=0 && index == L->Length-1 ){
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
        if(L->Data[i] == NO_DATA){
            return i;
        }
    }
    return -1; // No free index found
}

bool InserHead(PtrL L, DataType data){
    int pos = findFreeIndex(L);
    if(pos == -1){
        return false;
    }
    L->Data[pos] = data;
    L->Next[pos] = L->Head;
    L->Head = pos;
    if(L->Length == 0){
        L->Tail = pos;
    }
    L->Length++;
    return true;
}
bool InsertTail(PtrL L, DataType data){
    int newpos = findFreeIndex(L);
    if(newpos == -1){
        return false;
    }
    L->Data[newpos] = data;
    L->Next[newpos] = -1;
    L->Next[L->Tail] = newpos; // Link the old tail to the new node
    L->Tail = newpos;
    L->Length++;
    return true;
}
bool InsertAt(PtrL L, DataType data, int index){
    int newpos = findFreeIndex(L);
    if(newpos == -1){
        return false;
    }
    int prev = L->Head;
    for(int i=0; i<index-1; i++){
        prev = L->Next[prev];
    }
    L->Data[newpos] = data;
    L->Next[newpos] = L->Next[prev];

    L->Next[prev] = newpos;    //prev index's next is newpos
    L->Length++;
    return true;
}
bool DeleteHead(PtrL L){
    int oldHead = L->Head;
    L->Head = L->Next[L->Head];
    L->Data[oldHead] = NO_DATA; // Mark as free
    L->Next[oldHead] = -1;         // Reset next pointer
    L->Length--;
    if(L->Length == 0){
        L->Head = -1; // Reset head if list is empty
        L->Tail = -1; // Reset tail if list is empty
    }
    return true;
}
bool DeleteTail(PtrL L){
    int prev = L->Head;
    while(prev != -1){
        if( L->Next[prev] == L->Tail){
            L->Next[prev] = -1; // Set the next of the previous node to -1
            break;
        }
        prev = L->Next[prev];
    }
    L->Data[L->Tail] = NO_DATA; // Mark as free
    L->Next[L->Tail] = -1;         // Reset next pointer
    L->Tail = prev; // Update tail to the previous node
    L->Length--;
    return true;
}
bool DeleteAt(PtrL L, int index){
    int prev = L->Head;
    for(int i=0; i<index-1; i++){
        prev = L->Next[prev];
    }
    int delpos = L->Next[prev];
    L->Next[prev] = L->Next[delpos];
    L->Data[delpos] = NO_DATA; // Mark as free
    L->Next[delpos] = -1;         // Reset next pointer
    L->Length--;
    return true;
}


