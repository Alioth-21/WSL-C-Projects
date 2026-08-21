// 2-1-1 Seq-BTree.c
// Binary Tree implemented with sequential storage

#include <stdio.h>

typedef int DataType;
typedef struct {
    DataType* Data;
    Ptr Left, Right;
} BTree, *Ptr;

// Operations:

void InitBTree(){

}

//traverse the tree 
void PreOrder(Ptr T);
void InOrder(Ptr T);
void PostOrder(Ptr T);
void LevelOrder(Ptr T);


int main(){
    return 0;
}
