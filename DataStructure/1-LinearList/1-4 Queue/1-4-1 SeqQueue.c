// 1-4-1 SeqQueue.c
// Cricular Queue using Array
/*
Queue Pointer setting：
    Front： point to the first element
    Rear： point to the last element's next Pos
Jugle:
    IsEmpty： Front == Rear
    IsFull： (Rear + 1) % MAXSIZE == Front  //Rear is Prev of Front
    Length: (Rear-Front+MAXSIZE)%MAXSIZE
*/

#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 5
typedef int DataType;
typedef struct{
    DataType Data[MAXSIZE];
    int Front, Rear;
}SeqQueue, *PtrQ;

void InitQueue(PtrQ Q);
void PrintQueue(PtrQ Q);
bool EnQueue(PtrQ Q, DataType data);
bool DeQueue(PtrQ Q, DataType* data);
bool IsEmpty(PtrQ Q);
bool IsFull(PtrQ Q);
int GetFront(PtrQ Q);
int GetRear(PtrQ Q);
int GetLength(PtrQ Q);
void ClearQueue(PtrQ Q);


int main(){
    SeqQueue Q;
    InitQueue(&Q);
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
                if(EnQueue(&Q, data)){
                    printf("Enqueued element: %d\n", data);
                }
                else{
                    printf("Enqueue Fail \n");
                }
                break;
            }
            case 2: {
                if (DeQueue(&Q, &data)){
                    printf("Dequeued element: %d\n", data);
                } 
                else{
                    printf("Dequeue Fail \n");
                }
                break;
            }
            case 3: PrintQueue(&Q); break;
            case 4: printf("Length: %d\n", GetLength(&Q)); break;
            case 5: printf("Front: %d, Rear: %d\n", GetFront(&Q), GetRear(&Q)); break;
            case 6: ClearQueue(&Q); break;
            default: printf("Invalid input!\n");
        }
    }

    return 0;
}
void InitQueue(PtrQ Q){
    Q->Front = 0;
    Q->Rear = 0;
}
void PrintQueue(PtrQ Q){
    for(int i = Q->Front; i != Q->Rear; i = (i + 1) % MAXSIZE){
        printf("%d ", Q->Data[i]);
    }
    printf("\n");
}
bool EnQueue(PtrQ Q, DataType data){
    if (IsFull(Q)){
        printf("Queue is full!\n");
        return false;
    }
    Q->Data[Q->Rear] = data;
    Q->Rear = (Q->Rear + 1) % MAXSIZE;
    return true;
}
bool DeQueue(PtrQ Q, DataType* data){
    if (IsEmpty(Q)){
        printf("Queue is empty!\n");
        return false;
    }
    *data = Q->Data[Q->Front];
    Q->Front = (Q->Front + 1) % MAXSIZE;
    return true;
}
bool IsEmpty(PtrQ Q){
    return (Q->Front == Q->Rear);
}
bool IsFull(PtrQ Q){
    return ((Q->Rear + 1) % MAXSIZE == Q->Front);
}
int GetFront(PtrQ Q){
    return Q->Front;
}
int GetRear(PtrQ Q){
    return Q->Rear;
}
int GetLength(PtrQ Q){
    return (Q->Rear - Q->Front + MAXSIZE) % MAXSIZE;
}
void ClearQueue(PtrQ Q){
    Q->Front = 0;
    Q->Rear = 0;
}