// 1-4-4 Static-Deque.c
// Static Deque By Cricular Sequential Storage
// No Length and Capacity
// set a empty space for Rear, to distinguish between full and empty

#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 5
typedef int DataType;
typedef struct{
    DataType Data[MAXSIZE];
    int Front, Rear;
}Deque, *PtrD;

void InitDeque(PtrD D);
void PrintDeque(PtrD D);
bool EnQueueFront(PtrD D, DataType data);
bool EnQueueRear(PtrD D, DataType data);
bool DeQueueFront(PtrD D, DataType* data);
bool DeQueueRear(PtrD D, DataType* data);
int GetLength(PtrD D);
void ClearDeque(PtrD D);
bool IsEmpty(PtrD D);
bool IsFull(PtrD D);

int main(){
    Deque deque;
    PtrD D = &deque;
    InitDeque(D);
    DataType data;
    int choice = -1;
    while (choice)  {
        printf("1. EnQueue Front\n");
        printf("2. EnQueue Rear\n");
        printf("3. DeQueue Front\n");
        printf("4. DeQueue Rear\n");
        printf("5. PrintDeque\n");
        printf("6. Length\n");
        printf("7. Clear\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1: {
                printf("Enter the element to enqueue at front: ");
                scanf("%d", &data);
                if(EnQueueFront(D, data)){
                    printf("Enqueued element at front: %d\n", data);
                }
                else{
                    printf("Enqueue Front Fail \n");
                }
                break;
            }
            case 2: {
                printf("Enter the element to enqueue at rear: ");
                scanf("%d", &data);
                if(EnQueueRear(D, data)){
                    printf("Enqueued element at rear: %d\n", data);
                }
                else{
                    printf("Enqueue Rear Fail \n");
                }
                break;
            }
            case 3: {
                if (DeQueueFront(D, &data)){
                    printf("Dequeued element from front: %d\n", data);
                }
                else{
                    printf("Dequeue Front Fail \n");
                }
                break;
            }
            case 4: {
                if (DeQueueRear(D, &data)){
                    printf("Dequeued element from rear: %d\n", data);
                }
                else{
                    printf("Dequeue Rear Fail \n");
                }
                break;
            }
            case 5: PrintDeque(D); break;
            case 6: printf("Length of deque: %d\n", GetLength(D)); break;
            case 7: ClearDeque(D); break;
            default: printf("Invalid input!\n");
        }
    }
    return 0;
}

void InitDeque(PtrD D){
    D->Front = 0;
    D->Rear = 0;
}
void PrintDeque(PtrD D){
    if(IsEmpty(D)){
        printf("Deque is empty\n");
        return;
    }
    int pos = D->Front;
    for(int i=0; i<GetLength(D); i++){
        printf("%d ", D->Data[pos]);
        pos = (pos + 1) % MAXSIZE;
    }
    printf("\n");
}
bool EnQueueFront(PtrD D, DataType data){
    if(IsFull(D)){
        printf("Deque is full\n");
        return false;
    }
    D->Front = (D->Front - 1 + MAXSIZE) % MAXSIZE;
    D->Data[D->Front] = data;
    return true;
}
bool EnQueueRear(PtrD D, DataType data){
    if(IsFull(D)){
        printf("Deque is full\n");
        return false;
    }
    D->Data[D->Rear] = data;
    D->Rear = (D->Rear + 1) % MAXSIZE;
    return true;
}
bool DeQueueFront(PtrD D, DataType* data){
    if(IsEmpty(D)){
        printf("Deque is empty\n");
        return false;
    }
    *data = D->Data[D->Front];
    D->Front = (D->Front + 1) % MAXSIZE;
    return true;
}
bool DeQueueRear(PtrD D, DataType* data){
    if(IsEmpty(D)){
        printf("Deque is empty\n");
        return false;
    }
    D->Rear = (D->Rear - 1 + MAXSIZE) % MAXSIZE;
    *data = D->Data[D->Rear];
    return true;
}
int GetLength(PtrD D){
    return (D->Rear - D->Front + MAXSIZE) % MAXSIZE;
}
void ClearDeque(PtrD D){
    D->Front = 0;
    D->Rear = 0;
}
bool IsEmpty(PtrD D){
    return (D->Front == D->Rear);
}
bool IsFull(PtrD D){
    return ((D->Rear + 1) % MAXSIZE == D->Front);
}



