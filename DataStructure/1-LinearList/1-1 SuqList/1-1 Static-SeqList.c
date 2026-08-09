// 1-1 Static-SeqList.c
#include<stdio.h>
#include<stdbool.h>
#define MAXSIZE 100
#define NotFound 1000

typedef int ElemType;

struct SeqList{
    ElemType Data[MAXSIZE];
    int Length;
}SList;

struct SeqList* Sp = &SList;

//Basic Operations
void InitList();
bool IsEmpty();
bool IsFull();
bool CheckIndex(int Index);
bool CheckInsertIndex(int Index);
int GetLength();
bool InsertHead(ElemType Elem);
bool InsertAtIndex(int Index, ElemType Elem);
bool InsertTail(ElemType Elem);
ElemType GetElem(int Index);
bool InputeElem(int Index, ElemType Elem);
ElemType FindByIndex(int Index);
int FindByElem(ElemType Elem);

//Operations
void PrintList();
bool Insert();
bool FindElem();
bool UpdeteElem();
ElemType DeleteElem();
void ClearList();
void DestoryList();

int main(){
    InitList();
    int chioce = -1;
    while(chioce){
    printf("1. Insert\n2. Find\n3. Update\n4. Delete\n5. Print\n6. Clear\n0. Exit\n");
    scanf("%d", &chioce);
        switch(chioce){
            case 1: Insert(); break;
            case 2: FindElem(); break;
            case 3: UpdeteElem(); break;
            case 4: DeleteElem(); break;
            case 5: PrintList(); break;
            case 6: ClearList(); break;
            case 0: DestoryList(); break;
            default: printf("Invalid input!\n"); 
        }
    }
    return 0;
}

void InitList(){
    Sp->Length = 0;
}
bool IsEmpty(){
    return Sp->Length == 0;
}
bool IsFull(){
    return Sp->Length == MAXSIZE;
}
bool CheckIndex(int Index){
    if(Index >= 0 && Index < Sp->Length){
        return true;
    }
    else{
        printf("Index out of bounds!\n");
        return false;
    }
}
bool CheckInsertIndex(int Index){
    if(Index >= 0 && Index <= Sp->Length){
        return true;
    }
    else{
        printf("Insert index out of bounds!\n");
        return false;
    }
}
int GetLength(){
    return Sp->Length;
}
bool InsertHead(ElemType Elem){
    if(IsFull()){
        printf("List is full!\n");
        return false;
    }
    for(int i = Sp->Length; i > 0; i--){
        Sp->Data[i] = Sp->Data[i - 1];
    }
    Sp->Data[0] = Elem;
    Sp->Length++;
    return true;
}
bool InsertAtIndex(int Index, ElemType Elem){
    if(IsFull()){
        printf("List is full!\n");
        return false;
    }
    if(CheckInsertIndex(Index) == false){
        return false;
    }
    for(int i = Sp->Length; i > Index; i--){
        Sp->Data[i] = Sp->Data[i - 1];
    }
    Sp->Data[Index] = Elem;
    Sp->Length++;
    return true;
}
bool InsertTail(ElemType Elem){
    if(IsFull()){
        printf("List is full!\n");
        return false;
    }
    Sp->Data[Sp->Length] = Elem;
    Sp->Length++;
    return true;
}
ElemType GetElem(int Index){
    return (CheckIndex(Index)) ? Sp->Data[Index] : NotFound;
}
bool InputeElem(int Index, ElemType Elem){
    if(CheckIndex(Index) == false){
        return false;
    }
    Sp->Data[Index] = Elem;
    return true;
}
ElemType FindByIndex(int Index){
    return GetElem(Index);
}
int FindByElem(ElemType Elem){
    for(int i = 0; i < Sp->Length; i++){
        if(Sp->Data[i] == Elem){
            return i;
        }
    }
    return NotFound;
}

//Operations
void PrintList(){
    if(IsEmpty()){
        printf("List is empty!\n");
        return;
    }
    for(int i = 0; i < Sp->Length; i++){
        printf("%d ", Sp->Data[i]);
    }
    printf("\n");
}
bool Insert(){
    int Index;
    ElemType Elem;
    printf("Enter the index to insert: ");
    scanf("%d", &Index);
    printf("Enter the element to insert: ");
    scanf("%d", &Elem);
    return InsertAtIndex(Index, Elem);
}
bool FindElem(){
    ElemType Elem;
    int Index;
    int choice=0;
    printf("Find by:\n1. Index\n2. Element\n");
    printf("Enter the chioce: ");
    scanf("%d", &choice);
    if(choice == 1){
        printf("Enter the index: ");
        scanf("%d", &Index);
        Elem = FindByIndex(Index);
        if(Elem != NotFound){
            printf("Element at index %d is %d\n", Index, Elem);
            return true;
        }
    }
    else if(choice == 2){
        printf("Enter the element: ");
        scanf("%d", &Elem);
        Index = FindByElem(Elem);
        if(Index != NotFound){
            printf("Element %d found at index %d\n", Elem, Index);
            return true;
        }
    }
    return false;
}
bool UpdeteElem(){
    int Index;
    ElemType Elem;
    printf("Enter the index to update: ");
    scanf("%d", &Index);
    printf("Enter the new element: ");
    scanf("%d", &Elem);
    return InputeElem(Index, Elem);
}
ElemType DeleteElem(){
    int Index;
    printf("Enter the index to delete: ");
    scanf("%d", &Index);
    if(FindByIndex(Index) == NotFound){
        printf("Element not found at index %d\n", Index);
        return NotFound;
    }
    ElemType DeletedElem = Sp->Data[Index];
    for(int i = Index; i < Sp->Length - 1; i++){
        Sp->Data[i] = Sp->Data[i + 1];
    }
    Sp->Length--;
    return DeletedElem;
}
void ClearList(){
    for (int i = 0; i < Sp->Length; i++){
        Sp->Data[i] = 0;
    }
    Sp->Length = 0;
}
void DestoryList(){
    ClearList();
}