// 1-2-5 AoS-StaticLinkList.c
// Array of Structures, AoS

#include <stdio.h>
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

struct SList{
    struct Node Data[MAXSIZE];
    int Length;
    int Head, Tail;
};

//
void InitList(PtrL L);
void PrintList(PtrL L);
bool InsertNode(PtrL L);
bool FindNode(PtrL L);
bool UpdateNode(PtrL L);
bool DeleteNode(PtrL L);
void ClearList(PtrL L);

bool IsEmpty(PtrL L);
bool IsFull(PtrL L);
int GetLength(PtrL L);
int MallocNode(PtrL L);
void FreeNode(PtrL L, int index);
bool InserHead(PtrL L, DataType data);
bool InsertTail(PtrL L, DataType data);
bool InsertAt(PtrL L, DataType data, int index);
bool DeleteHead(PtrL L);
bool DeleteTail(PtrL L);
bool DeleteAt(PtrL L, int index);

int main(){
    int choice = -1;
    struct SList List;
    PtrL L = &List;
    InitList(L);

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
        switch (choice){
            case 1: PrintList(L); break;
            case 2: printf("Length: %d\n", GetLength(L)); break;
            case 3: InsertNode(L); break;
            case 4: FindNode(L); break;
            case 5: UpdateNode(L); break;
            case 6: DeleteNode(L); break;
            case 7: ClearList(L); break;
            default: printf("Invalid input!\n");
        }
    }

    return 0;
}

void InitList(PtrL L){
    for(int i=0; i<MAXSIZE; i++){
        L->Data[i].NodeData = NODATA;
    }
    L->Head = -1;
    L->Tail = -1;
    L->Length = 0;
}
void PrintList(PtrL L){
    int index = L->Head;
    while(index != -1){
        printf("%d ", L->Data[index].NodeData);
        index = L->Data[index].Next;
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

}
bool FindNode(PtrL L){
    
}
bool UpdateNode(PtrL L);
bool DeleteNode(PtrL L);
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
int MallocNode(PtrL L);
void FreeNode(PtrL L, int index);
bool InserHead(PtrL L, DataType data);
bool InsertTail(PtrL L, DataType data);
bool InsertAt(PtrL L, DataType data, int index);
bool DeleteHead(PtrL L);
bool DeleteTail(PtrL L);
bool DeleteAt(PtrL L, int index);

