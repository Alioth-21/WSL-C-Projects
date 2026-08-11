// 1-4-2 Dynamic-CricularQueue.c
// Malloc
// Set Length and Capacity
/*
Queue Pointer setting：
    Front： point to the first element
    Rear： point to the last element's next Pos
Jugle:
    IsEmpty： Front == Rear
    IsFull： 
        (Rear + 1) % MAXSIZE == Front  //Rear is Prev of Front
        Length == MAXSIZE-1
    Length: (Rear-Front+MAXSIZE)%MAXSIZE
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 10
#define SIZE 5
typedef int DataType;
typedef DataType* Ptr;
typedef struct{
    Ptr Data;
    int Front, Rear;
    int Length;
    int Capacity;
}Queue, *PtrQ;

bool Resize(PtrQ Q, int size);
PtrQ InitQueue();
void PrintQueue(PtrQ Q);
bool EnQueue(PtrQ Q, DataType data);
bool DeQueue(PtrQ Q, DataType* data);
bool IsEmpty(PtrQ Q);
bool IsFull(PtrQ Q);
bool IsCapacityFull(PtrQ Q);
int GetFront(PtrQ Q);
int GetRear(PtrQ Q);
int GetLength(PtrQ Q);
void ClearQueue(PtrQ Q);


int main(){
    PtrQ Q = InitQueue();
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
            case 4: printf("Length: %d\n", GetLength(Q)); break;
            case 5: printf("Front: %d, Rear: %d\n", GetFront(Q), GetRear(Q)); break;
            case 6: ClearQueue(Q); break;
            default: printf("Invalid input!\n");
        }
    }

    return 0;
}
bool Resize(PtrQ Q, int size){
    Ptr p = (Ptr)malloc(sizeof(DataType)*size);
    if (p==NULL) return false;
    int pos = Q->Front;
    for(int i=0; i<Q->Length; i++){
        p[i] = Q->Data[pos];
        pos = (pos+1) % Q->Capacity;
    }
    if(Q->Data != NULL)  free(Q->Data);
    Q->Data = p;
    Q->Front = 0;
    Q->Rear = Q->Length;
    Q->Capacity = size;
    return true;
}
PtrQ InitQueue(){
    PtrQ p = (PtrQ)malloc(sizeof(Queue));
    if(p==NULL) return NULL;
    p->Front = 0;
    p->Rear = 0;
    p->Data = NULL;
    p->Length = 0;
    p->Capacity = SIZE;
    if(!Resize(p, p->Capacity)){
        printf("Malloc Failed\n");
        free(p);
        return NULL;
    }
    return p;
}
void PrintQueue(PtrQ Q){
    for(int i = Q->Front; i != Q->Rear; i = (i + 1) % Q->Capacity){
        printf("%d ", Q->Data[i]);
    }
    printf("\n");
}
bool EnQueue(PtrQ Q, DataType data){
    if (IsFull(Q)){
        printf("Queue is full!\n");
        return false;
    }
    if(IsCapacityFull(Q)){
        if(Resize(Q, Q->Capacity+SIZE)){
            printf("Malloc Completed\n");
        }
        else{
            printf("Malloc Failed\n");
            return false;
        }
    }
    Q->Data[Q->Rear] = data;
    Q->Rear = (Q->Rear + 1) % Q->Capacity;
    Q->Length++;
    return true;
}
bool DeQueue(PtrQ Q, DataType* data){
    if (IsEmpty(Q)){
        printf("Queue is empty!\n");
        return false;
    }
    *data = Q->Data[Q->Front];
    Q->Front = (Q->Front + 1) % Q->Capacity;
    Q->Length--;
    return true;
}
bool IsEmpty(PtrQ Q){
    return (Q->Front == Q->Rear);
}
bool IsFull(PtrQ Q){
    return Q->Length==MAXSIZE-1;     //
}
bool IsCapacityFull(PtrQ Q){
    return Q->Length==Q->Capacity && Q->Capacity<MAXSIZE;
}
int GetFront(PtrQ Q){
    return Q->Front;
}
int GetRear(PtrQ Q){
    return Q->Rear;
}
int GetLength(PtrQ Q){
    return Q->Length;       //(Q->Rear - Q->Front + MAXSIZE) % MAXSIZE;
}
void ClearQueue(PtrQ Q){
    Q->Front = 0;
    Q->Rear = 0;
    Q->Length = 0;
}