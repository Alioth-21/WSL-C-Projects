// 1-2 Dynamic-SeqList.c
// No head node
// malloc

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 20
#define SIZE 5
#define NotFound -1

typedef int ElemType;

struct SeqList{
    ElemType* Data;
    int Length;
    int Capacity;
};
typedef struct SeqList* Sptr;

//Basic Operations
bool GetSpace(Sptr Sp);
bool IsEmpty(Sptr Sp);
bool IsFull(Sptr Sp);
int GetLength(Sptr Sp);
int GetCapacity(Sptr Sp);
bool CheckIndex(Sptr Sp, int Index);
ElemType GetElem(Sptr Sp, int Index);

//Operations
Sptr InitList();
bool Insert(Sptr Sp);
int FindByElem(Sptr Sp);
ElemType FindByIndex(Sptr Sp);
bool UpdeteElem(Sptr Sp);
bool DeleteElem(Sptr Sp);
void ClearList(Sptr Sp);
void DestoryList(Sptr Sp);
void PrintList(Sptr Sp);

int main(){
    int chioce = -1;
    Sptr Sp = InitList();
    while (chioce){
        printf("1. PrintList\n2. ListLength\n3. ListSize\n4. Insert\n5. FindByElem\n6. FindByIndex\n7. Update\n8. Delete\n9. Clear\n0. Exit\n");
        scanf("%d", &chioce);
        switch (chioce){
        case 1: PrintList(Sp); break;
        case 2: printf("Length:%d\n",GetLength(Sp)); break;
        case 3: printf("Size:%d\n",GetCapacity(Sp)); break;
        case 4: Insert(Sp); break;
        case 5: FindByElem(Sp); break;
        case 6: FindByIndex(Sp); break;
        case 7: UpdeteElem(Sp); break;
        case 8: DeleteElem(Sp); break;
        case 9: ClearList(Sp); break; 
        case 0: DestoryList(Sp); break;
        default: printf("Invalid input!\n");
        }
    }

    return 0;
}

//Basic Operations
bool GetSpace(Sptr Sp){
    Sp->Capacity += SIZE;
    ElemType* np = (ElemType*)malloc((Sp->Capacity) * sizeof(ElemType));
    for(int i = 0; i < Sp->Length; i++){
        np[i] = Sp->Data[i];
    }
    free(Sp->Data);
    Sp->Data = np;
    return true;
}
bool IsEmpty(Sptr Sp){
    return Sp->Length == 0;
}
bool IsFull(Sptr Sp){
    return (Sp->Capacity + SIZE > MAXSIZE);
}
int GetLength(Sptr Sp){
    return Sp->Length;
}
int GetCapacity(Sptr Sp){
    return Sp->Capacity;
}
bool CheckIndex(Sptr Sp, int Index){
    if(Index >= 0 && Index <= Sp->Length){
        return true;
    }
    else{
        printf("Index out of bounds!\n");
        return false;
    }
}
ElemType GetElem(Sptr Sp, int Index){
    return (CheckIndex(Sp, Index)) ? Sp->Data[Index] : NotFound;
}


//Operations
Sptr InitList(){
    Sptr Sp = (Sptr)malloc(sizeof(struct SeqList));
    Sp->Capacity = SIZE;
    Sp->Length = 0;
    Sp->Data = (ElemType*)malloc(Sp->Capacity * sizeof(ElemType));
    return Sp;
}
bool Insert(Sptr Sp){
    if(IsFull(Sp)){
        printf("List is full!\n");
        return false;
    }
    else if(Sp->Length == Sp->Capacity){
        GetSpace(Sp);
    }
    int Index;
    ElemType Elem;
    printf("Enter the index to insert: ");
    scanf("%d", &Index);
    printf("Enter the element to insert: ");
    scanf("%d", &Elem);
    if(CheckIndex(Sp, Index) == false){
        return false;
    }
    for(int i = Sp->Length; i > Index; i--){
        Sp->Data[i] = Sp->Data[i - 1];
    }
    Sp->Data[Index] = Elem;
    Sp->Length++;
    return true;
}
int FindByElem(Sptr Sp){
    ElemType Elem;
    printf("Enter the element to find: ");
    scanf("%d", &Elem);
    for(int i = 0; i < Sp->Length; i++){
        if(Sp->Data[i] == Elem){
            printf("Element %d found at index %d\n", Elem, i);
            return i;
        }
    }
    printf("Element %d not found!\n", Elem);
    return NotFound;
}
ElemType FindByIndex(Sptr Sp){
    int Index;
    printf("Enter the index to find: ");
    scanf("%d", &Index);
    if(CheckIndex(Sp, Index) == false){
        return NotFound;
    }
    printf("Element at index %d is %d\n", Index, GetElem(Sp, Index));
    return GetElem(Sp, Index);
}
bool UpdeteElem(Sptr Sp){
    int Index;
    ElemType Elem;
    printf("Enter the index to update: ");
    scanf("%d", &Index);
    printf("Enter the new element: ");
    scanf("%d", &Elem);
    if(CheckIndex(Sp, Index) == false){
        return false;
    }
    Sp->Data[Index] = Elem;
    return true;
}
bool DeleteElem(Sptr Sp){
    int Index;
    printf("Enter the index to delete: ");
    scanf("%d", &Index);
    if(CheckIndex(Sp, Index) == false){
        return false;
    }
    for(int i = Index; i < Sp->Length - 1; i++){
        Sp->Data[i] = Sp->Data[i + 1];
    }
    Sp->Length--;
    return true;
}
void ClearList(Sptr Sp){
    for(int i = 0; i < Sp->Length; i++){
        Sp->Data[i] = 0;
    }
    Sp->Length = 0;
}
void DestoryList(Sptr Sp){
    for(int i = 0; i < Sp->Length; i++){
        free(&(Sp->Data[i]));
    }
    free(Sp);
}
void PrintList(Sptr Sp){
    for(int i = 0; i < Sp->Length; i++){
        printf("%d ", Sp->Data[i]);
    }
    printf("\n");
}
