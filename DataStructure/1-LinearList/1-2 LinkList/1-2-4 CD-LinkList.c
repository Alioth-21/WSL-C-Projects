// 1-2-4 CD-LinkList
// Circular Doubly Linked List in C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 5

typedef int DataType;
typedef struct Node* Ptr;
typedef struct CDLinkList* PtrL;

struct Node{
    Ptr Prev, Next;
    DataType Data;
};

struct CDLinkList{
    Ptr Head, Tail;
    int Length;
};

//


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



