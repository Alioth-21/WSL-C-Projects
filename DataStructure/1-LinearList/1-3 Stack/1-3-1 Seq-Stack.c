// 1-3-1 Seq-Stack.c

#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 5
typedef int DataType;
typedef struct {
    DataType Data[MAXSIZE];
    int Top;
} Stack;

void InitStack(Stack* S);
void PrintStack(Stack* S);
int GetLength(Stack* S);
void ClearStack(Stack* S);
DataType GetTop(Stack* S);
bool IsEmpty(Stack* S);
bool IsFull(Stack* S);
bool Push(Stack* S, DataType data);
bool Pop(Stack* S, DataType* data);


int main() {
    Stack S;
    InitStack(&S);
    int choice = -1;
    DataType data=0;
    while (choice)  {
        printf("1. PrintStack\n");
        printf("2. GetTop\n");
        printf("3. Push\n");
        printf("4. Pop\n");
        printf("5. ClearStack\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1: PrintStack(&S); break;
            case 2: printf("Top element: %d\n", GetTop(&S)); break;
            case 3: {
                printf("Enter the element to push: ");
                scanf("%d", &data);
                if(Push(&S, data)){
                    printf("Pushed %d onto the stack.\n", data);
                } 
                else {
                    printf("Stack is full! Cannot push %d.\n", data);
                }
                break;
            }
            case 4: {
                if(Pop(&S, &data)){
                    printf("Popped %d from the stack.\n", data);
                } 
                else {
                    printf("Stack is empty! Cannot pop.\n");
                }
                break;
            }
            case 5: ClearStack(&S); break;
            default: printf("Invalid input!\n");
        }
    }

    return 0;
}

void InitStack(Stack* S){
    S->Top = -1;
}
void PrintStack(Stack* S){
    if (IsEmpty(S)) return;
    printf("Stack elements (from top to bottom):\n");
    for(int i = S->Top; i >= 0; i--){
        printf("%d ", S->Data[i]);
    }
    printf("\n");
}
void ClearStack(Stack* S){
    S->Top = -1;
}
DataType GetTop(Stack* S){
    return S->Top >= 0 ? S->Data[S->Top] : -1; // Return 0 if stack is empty
}
bool IsEmpty(Stack* S){
    return S->Top == -1;
}
bool IsFull(Stack* S){
    return S->Top == MAXSIZE-1;
}
bool Push(Stack* S, DataType data){
    if(IsFull(S)){
        return false;
    }
    S->Top++;
    S->Data[S->Top] = data;
    return true;
}
bool Pop(Stack* S, DataType* data){
    if(IsEmpty(S)){
        return false;
    }
    *data = S->Data[S->Top];
    S->Top--;
    return true;
}
