// 1-4-5 Dynamic-Deque.c
// Double-ended Queue in C
// Dynamic Array Implementation
// No Empty Space for Rear judge IsEmpty and IsFull
/*
Enqueue:
    Front: (Front - 1 + Capacity) % Capacity
    Rear: (Rear + 1) % Capacity
Dequeue:
    Front: (Front + 1) % Capacity
    Rear: (Rear - 1 + Capacity) % Capacity

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
}Deque, *PtrD;

/// @declarations
PtrD InitDeque();
bool Resize(PtrD D, int size);
bool EnQueueFront(PtrD D, DataType data);
bool EnQueueRear(PtrD D, DataType data);
bool DeQueueFront(PtrD D, DataType* data);
bool DeQueueRear(PtrD D, DataType* data);
void PrintDeque(PtrD D);
int GetLength(PtrD D);
void ClearDeque(PtrD D);
bool IsEmpty(PtrD D);
bool IsFull(PtrD D);
bool IsCapacityFull(PtrD D);

int main(){
    PtrD D = InitDeque();
    if(D == NULL){
        printf("Memory allocation failed!\n");
        return -1;
    }
    
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


PtrD InitDeque(){
    PtrD D = (PtrD)malloc(sizeof(Deque));
    if(D == NULL){
        return NULL;
    }
    D->Data = NULL;
    D->Front = 0;
    D->Rear = 0;
    D->Length = 0;
    D->Capacity = SIZE;
    if(! Resize(D, D->Capacity) ){
        printf("Memory allocation failed!\n");
        free(D);
        return NULL;
    }
    return D;
}
bool Resize(PtrD D, int size){
    Ptr p = (Ptr)malloc(size * sizeof(DataType));
    if(p == NULL){
        return false;
    }
    // Copy Old data to new space
    int pos = D->Front;
    for(int i=0; i<D->Length; i++){
        p[i] = D->Data[pos];
        pos = (pos + 1) % D->Capacity;
    }
    // set queue new space
    if(D->Data!=NULL) free(D->Data);
    D->Data = p;
    D->Front = 0;
    D->Rear = D->Length;
    D->Capacity = size;     // capacity changes, Length not change 
    return true;
}
bool EnQueueFront(PtrD D, DataType data){
    if(IsFull(D)){
        printf("Deque is full\n");
        return false;
    }
    if(IsCapacityFull(D) ){
        if(Resize(D, D->Capacity + SIZE)) {
            printf("Get More Space\n");
        }
        else{
            printf("Get More Space Failed\n");
            return false;
        }
    }
    D->Front = (D->Front - 1 + D->Capacity) % D->Capacity;
    D->Data[D->Front] = data;
    D->Length++;
    return true;
}
bool EnQueueRear(PtrD D, DataType data){
    if(IsFull(D)){
        printf("Deque is full\n");
        return false;
    }
    if(IsCapacityFull(D) ){
        if(Resize(D, D->Capacity + SIZE)) {
            printf("Get More Space\n");
        }
        else{
            printf("Get More Space Failed\n");
            return false;
        }
    }
    D->Data[D->Rear] = data;
    D->Rear = (D->Rear + 1) % D->Capacity;
    D->Length++;
    return true;
}
bool DeQueueFront(PtrD D, DataType* data){
    if(IsEmpty(D)){
        printf("Deque is empty\n");
        return false;
    }
    *data = D->Data[D->Front];
    D->Front = (D->Front + 1) % D->Capacity;
    D->Length--;
    return true;
}
bool DeQueueRear(PtrD D, DataType* data){
    if(IsEmpty(D)){
        printf("Deque is empty\n");
        return false;
    }
    D->Rear = (D->Rear - 1 + D->Capacity) % D->Capacity;
    *data = D->Data[D->Rear];
    D->Length--;
    return true;
}
void PrintDeque(PtrD D){
    if(IsEmpty(D)){
        printf("Deque is empty\n");
        return;
    }
    int i = D->Front;
    for(int j=0; j<D->Length; j++){
        printf("%d ", D->Data[i]);
        i = (i + 1) % D->Capacity;
    }
    printf("\n");
}
int GetLength(PtrD D){
    return D->Length;
}
void ClearDeque(PtrD D){
    D->Front = 0;
    D->Rear = 0;
    D->Length = 0;
}
bool IsEmpty(PtrD D){
    return D->Length == 0;  // D->Front == D->Rear
}
bool IsFull(PtrD D){
    return D->Length == MAXSIZE;
}
bool IsCapacityFull(PtrD D){
    return D->Length == D->Capacity && D->Capacity < MAXSIZE;
}