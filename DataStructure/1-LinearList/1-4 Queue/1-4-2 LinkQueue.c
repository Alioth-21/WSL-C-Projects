// 1-4-2 LinkQueue.c
// Singly Linked Queue in C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 5
typedef int DataType;
typedef struct Node{
    DataType Data;
    struct Node* Next;
}Node, *Ptr;

typedef struct{
    Ptr Front, Rear;
    int Length;
}LinkQueue, *PtrQ;

//
PtrQ InitQueue();
bool EnQueue(PtrQ Q, DataType data);
bool DeQueue(PtrQ Q, DataType* data);
void PrintQueue(PtrQ Q);
int GetLength(PtrQ Q);
void ClearQueue(PtrQ Q);

Ptr CreateNode(DataType data);
Ptr GetFront(PtrQ Q);
Ptr GetRear(PtrQ Q);
bool IsEmpty(PtrQ Q);
bool IsFull(PtrQ Q);


int main(){
    PtrQ Q = InitQueue();
    if(Q == NULL){
        printf("Memory allocation failed!\n");
        return -1;
    }
    DataType data;
    int choice = -1;
    while (choice)  {
        printf("1. EnQueue\n");
        printf("2. DeQueue\n");
        printf("3. PrintQueue\n");
        printf("4. Length\n");
        printf("5. Front&Rear\n");
        printf("6. Clear\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1: {
                printf("Enter the element to enqueue: ");
                scanf("%d", &data);
                if(EnQueue(Q, data)){
                    printf("Enqueued element: %d\n", data);
                }
                else{
                    printf("Enqueue Fail \n");
                }
                break;
            }
            case 2: {
                if (DeQueue(Q, &data)){
                    printf("Dequeued element: %d\n", data);
                } 
                else{
                    printf("Dequeue Fail \n");
                }
                break;
            }
            case 3: PrintQueue(Q); break;
            case 4: printf("Length of queue: %d\n", GetLength(Q)); break;
            case 5: {
                if(!IsEmpty(Q)){
                    printf("Front element: %d, Rear element: %d\n", GetFront(Q)->Data, GetRear(Q)->Data);
                }
                else{
                    printf("Queue is empty\n");
                }
                break;
            }
            case 6: ClearQueue(Q); break;
            default: printf("Invalid input!\n");
        }
    }
    return 0;
}

PtrQ InitQueue(){
    PtrQ Q = (PtrQ)malloc(sizeof(LinkQueue));
    Q->Front = Q->Rear = NULL;
    Q->Length = 0;
    return Q;
}
bool EnQueue(PtrQ Q, DataType data){
    if(IsFull(Q)){
        printf("Queue is full\n");
        return false;
    }
    Ptr p = CreateNode(data);
    if(p == NULL){
        printf("Node malloc failed\n");
        return false;
    }
    if(IsEmpty(Q)){
        Q->Front = Q->Rear = p;
    }
    else{
        Q->Rear->Next = p;
        Q->Rear = p;        //Q->Rear = Q->Rear->Next;
    }
    Q->Length++;
    return true;
}
bool DeQueue(PtrQ Q, DataType* data){
    if(IsEmpty(Q)){
        printf("Queue is empty\n");
        return false;
    }
    Ptr p = Q->Front;
    *data = p->Data;
    Q->Front = p->Next;
    free(p);
    Q->Length--;
    return true;
}
void PrintQueue(PtrQ Q){
    Ptr p = Q->Front;
    for(int i=0; i<Q->Length; i++){ //while(p->Next != NULL){...}
        printf("%d ", p->Data);
        p = p->Next;
    }
    printf("\n");
}
int GetLength(PtrQ Q){
    return Q->Length;
}
void ClearQueue(PtrQ Q){
    while(!IsEmpty(Q)){
        DataType data;
        DeQueue(Q, &data);
    }
    //Q->Front = Q->Rear = NULL;
}

Ptr CreateNode(DataType data){
    Ptr p = (Ptr)malloc(sizeof(Node));
    if(p == NULL) return NULL;
    p->Data = data;
    p->Next = NULL;
    return p;
}
Ptr GetFront(PtrQ Q){
    return Q->Front;
}
Ptr GetRear(PtrQ Q){
    return Q->Rear;
}
bool IsEmpty(PtrQ Q){
    return Q->Length == 0;  //return Q->Front == NULL && Q->Rear == NULL;
}
bool IsFull(PtrQ Q){
    return Q->Length == MAXSIZE;
}