// 1-2-6 SoA-StaticLinkList.c
// Structure of Arrays, SoA

#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 5

typedef int DataType;

typedef struct{
    DataType Data[MAXSIZE];
    int Index[MAXSIZE];
    int Length;
    int Head, Tail;
}SList;

void InitList(SList* L);
void PrintList(SList* L);
bool InsertNode(SList* L);
bool FindNode(SList* L);
bool UpdateNode(SList* L);
bool DeleteNode(SList* L);
void ClearList(SList* L);

bool IsEmpty(SList* L);
bool IsFull(SList* L);
int GetLength(SList* L);
int MallocNode(SList* L);
void FreeNode(SList* L, int index);
bool InsertHead(SList* L, DataType data);
bool InsertTail(SList* L, DataType data);
bool InsertAt(SList* L, DataType data, int index);
bool DeleteHead(SList* L);
bool DeleteTail(SList* L);
bool DeleteAt(SList* L, int index);


int main(){
    int choice = -1;
    SList List;
    InitList(&List);

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
        case 1: PrintList(&List);   break;
        case 2: printf("Length: %d\n", GetLength(&List)); break;
        case 3: InsertNode(&List);   break;
        case 4: FindNode(&List);     break;
        case 5: UpdateNode(&List);   break;
        case 6: DeleteNode(&List);   break;
        case 7: ClearList(&List);    break;
        default:printf("Invalid input!\n");
        }
    }
    return 0;
}

void InitList(SList* L);
void PrintList(SList* L);
bool InsertNode(SList* L);
bool FindNode(SList* L);
bool UpdateNode(SList* L);
bool DeleteNode(SList* L);
void ClearList(SList* L);

bool IsEmpty(SList* L);
bool IsFull(SList* L);
int GetLength(SList* L);
int MallocNode(SList* L);
void FreeNode(SList* L, int index);
bool InsertHead(SList* L, DataType data);
bool InsertTail(SList* L, DataType data);
bool InsertAt(SList* L, DataType data, int index);
bool DeleteHead(SList* L);
bool DeleteTail(SList* L);
bool DeleteAt(SList* L, int index);
