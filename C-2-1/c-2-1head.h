//C-2-1 head file
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 256
#define MAX_ITEMS 10

typedef struct Item* Ptr;
typedef struct LinkList* PtrL;

struct Item {
    int Id;
    char Content[MAX_SIZE];
    Ptr Next;
};

struct LinkList{
    Ptr Head, Last;
    size_t ListSize;
};

//tools functions
PtrL InitList();
bool DestoryList(PtrL L);
bool IsEmpty(PtrL List);
bool IsFull(PtrL List);
Ptr CreateItem();
Ptr SearchPrevItemById(PtrL List, int id);
void OutputItem(Ptr Item);

//operations functions
bool AddItem(PtrL List);
bool DeleteItem(PtrL List);
bool FindItem(PtrL List);
bool AlterItem(PtrL List);
bool Undo(PtrL List);
void DisplayItems(PtrL List);
