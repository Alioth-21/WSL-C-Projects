// 1-3-2 Link-Stack.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 5
typedef int Datatype;
typedef struct Node{
    Datatype Data;
    struct Node* Next;
}Node, *Ptr;
typedef struct Stack{
    Ptr Top;
    int Length;
}Stack, *PtrS;

PtrS InitStack();
void PrintStack(PtrS S);
Ptr GetTop(PtrS S);
int GetLength(PtrS S);
Ptr CreateNode(Datatype data);
bool Push(PtrS S, Datatype data);
bool Pop(PtrS S, Datatype* data);
void ClearStack(PtrS S);
bool IsEmpty(PtrS S);
bool IsFull(PtrS S);



int main() {
    PtrS S = NULL;
    if(( S=InitStack()) == NULL){
        printf("Memory allocation failed!\n");
        return -1;
    }
    int choice = -1;
    Ptr top = NULL;
    Datatype data=0;
    while (choice)  {
        printf("1. PrintStack\n");
        printf("2. StackTop\n");
        printf("3. Length\n");
        printf("4. Push\n");
        printf("5. Pop\n");
        printf("6. ClearStack\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1: PrintStack(S); break;
            case 2: {
                if((top=GetTop(S)) != NULL) printf("Top: %d\n", top->Data);
                else printf("Stack is empty!\n"); 
                break;
            }
            case 3: printf("Length: %d\n", GetLength(S)); break;
            case 4: {
                printf("Enter the element to push: ");
                scanf("%d", &data);
                if(Push(S, data)) printf("Push successful!\n");
                else printf("Push failed!\n");
                break;
            }
            case 5: {
                if(Pop(S, &data)) printf("Popped: %d\n", data);
                else printf("Pop failed!\n");
                break;
            }
            case 6: {
                ClearStack(S);
                printf("Stack cleared!\n");
                break;
            }
            default: printf("Invalid input!\n");
        }
    }
    return 0;
}


PtrS InitStack(){
    PtrS S = (PtrS)malloc(sizeof(Stack));
    if(S == NULL){
        return NULL;
    }
    S->Top = NULL;
    S->Length = 0;
    return S;
}
void PrintStack(PtrS S){
    Ptr p = S->Top;
    while(p != NULL){
        printf("%d ", p->Data);
        p = p->Next;
    }
    printf("\n");
}
Ptr GetTop(PtrS S){
    if(IsEmpty(S)){
        return NULL;
    }
    return S->Top;
}
int GetLength(PtrS S){
    return S->Length;
}
Ptr CreateNode(Datatype data){
    Ptr p = (Ptr)malloc(sizeof(Node));
    if(p == NULL){
        return NULL;
    }
    p->Data = data;
    p->Next = NULL;
    return p;
}
bool Push(PtrS S, Datatype data){
    if(IsFull(S)){
        return false;
    }
    Ptr p = CreateNode(data);
    if(p == NULL){
        return false;
    }
    p->Next = S->Top;
    S->Top = p;
    S->Length++;
    return true;
}
bool Pop(PtrS S, Datatype* data){
    if(IsEmpty(S)){
        return false;
    }
    Ptr p = S->Top;
    *data = p->Data;
    S->Top = p->Next;
    free(p);
    S->Length--;
    return true;
}
void ClearStack(PtrS S){
    while (!IsEmpty(S)){
        Datatype data;
        Pop(S, &data);
    }
}

bool IsEmpty(PtrS S){
    return (S->Length == 0);    //return S->Top == NULL;
}
bool IsFull(PtrS S){
    return S->Length == MAXSIZE;
}


