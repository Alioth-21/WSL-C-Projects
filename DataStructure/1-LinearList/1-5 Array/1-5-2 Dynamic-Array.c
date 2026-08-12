// 1-5-2 Dynamic-Array
// Dynamic Storage Representation
/*
Basic Operations:
    Read
    Write
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
    int Capacity;
}Array, *PtrA;

PtrA InitArray(int size);
bool CopyArray(Ptr src, int s_size, Ptr dest, int d_size);
bool Resize(PtrA arr, int size);
void SetData(PtrA arr, int index, DataType data);
DataType GetData(PtrA arr, int index);
bool CheckIndex(PtrA arr, int index);
void SetALL(PtrA arr, DataType data);
void PrintArray(PtrA arr);

int main(){
    PtrA p = InitArray(SIZE);
    SetALL(p, 0); // Initialize all elements to 0
    PrintArray(p);

    SetData(p, 0, 10);
    SetData(p, 1, 20);
    SetData(p, 2, 30);
    PrintArray(p);

    SetALL(p, 10);
    PrintArray(p);
    
    Resize(p, MAXSIZE);
    PrintArray(p);

    SetALL(p, 100);
    PrintArray(p);

    SetData(p, 5, 500);
    SetData(p, 7, 700);
    SetData(p, 9, 999);
    PrintArray(p);

    return 0;
}
PtrA InitArray(int size){
    PtrA arr = (PtrA)malloc(sizeof(Array));
    arr->Data = NULL;
    arr->Capacity = size;
    if(Resize(arr, size)){
        printf("Array initialized with size %d\n", size);
        arr->Capacity = size;
        return arr;
    } else {
        printf("Failed to initialize array.\n");
        return NULL;
    }
}
bool CopyArray(Ptr src, int s_size, Ptr dest, int d_size){    //copy src to dest
    if(src == NULL || dest == NULL){
        printf("Copy Fail\n");
        return false;
    }
    else{
        for(int i = 0; i < (s_size<d_size? s_size:d_size); i++){
            dest[i] = src[i];
        }
        printf("Copy Success\n");
        return true;
    }
}
bool Resize(PtrA arr, int size){
    if(size <= 0){
        printf("Invalid size!\n");
        return false;
    }
    Ptr p = (Ptr)malloc(size * sizeof(DataType));
    if(p==NULL){
        printf("Memory allocation failed!\n");
        return false;
    }
    if(arr->Data != NULL && CopyArray(arr->Data, arr->Capacity, p, size)){
        free(arr->Data);
    }
    arr->Data = p;
    arr->Capacity = size;
    return true;
}
void SetData(PtrA arr, int index, DataType data){
    if(CheckIndex(arr, index)) arr->Data[index] = data; 
    else printf("SetData Fail: Invalid index %d\n", index);
}
DataType GetData(PtrA arr, int index){
    if(CheckIndex(arr, index)){
        return arr->Data[index];
    } else {
        printf("GetData Fail: Invalid index %d\n", index);
        return -1; // Return an invalid value
    }
}
bool CheckIndex(PtrA arr, int index){
    if(index < 0 || index >= arr->Capacity){
        printf("CheckIndex Fail: Invalid index %d\n", index);
        return false;
    }
    return true;
}
void SetALL(PtrA arr, DataType data){
    for(int i = 0; i < arr->Capacity; i++){
        arr->Data[i] = data;
    }
}
void PrintArray(PtrA arr){
    printf("Array elements: ");
    for(int i = 0; i < arr->Capacity; i++){
        printf("%d ", arr->Data[i]);
    }
    printf("\n");
}
