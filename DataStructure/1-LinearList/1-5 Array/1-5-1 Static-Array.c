// 1-5-1 Static-Array
// Static Storage Representation
/*
Basic Operations:
    Read
    Write
*/

#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 10
typedef int DataType;
typedef struct{
    DataType Data[MAXSIZE];
}Array, *PtrA;

void SetData(PtrA arr, int index, DataType data);
DataType GetData(PtrA arr, int index);
bool CheckIndex(int index);
void SetALL(PtrA arr, DataType data);
void PrintArray(PtrA arr);

int main(){
    Array arr;
    PtrA p = &arr;
    SetALL(p, 0); // Initialize all elements to 0

    SetData(p, 0, 10);
    SetData(p, 1, 20);
    SetData(p, 2, 30);

    PrintArray(p);

    return 0;
}

void SetData(PtrA arr, int index, DataType data){
    if (CheckIndex(index)) arr->Data[index] = data;
    else printf("Index out of bounds!\n");
}
DataType GetData(PtrA arr, int index){
    if (CheckIndex(index)) {
        return arr->Data[index];
    } else {
        printf("Index out of bounds!\n");
        return -1; // Return an invalid value or handle error as needed
    }
}
bool CheckIndex(int index){
    return (index >= 0 && index < MAXSIZE);
}
void SetALL(PtrA arr, DataType data){
    for(int i = 0; i < MAXSIZE; i++){
        arr->Data[i] = data;
    }
}
void PrintArray(PtrA arr){
    for(int i = 0; i < MAXSIZE; i++){
        printf("%d ", arr->Data[i]);
    }
    printf("\n");
}
