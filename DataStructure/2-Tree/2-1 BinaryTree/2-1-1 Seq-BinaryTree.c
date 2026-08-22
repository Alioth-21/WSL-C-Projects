// 2-1-1 Seq-BTree.c
// Binary Tree implemented with sequential storage

#include <stdio.h>
#include <stdbool.h>
#define MaxSize 100
#define NoData -1

typedef int DataType;
typedef struct {
    DataType Data[MaxSize];
    int size;
} BTree, *Ptr;

// Operations:

void InitBTree(Ptr T);
bool InsertNode(Ptr T, int index, DataType data);   //Insert By Level Order
bool FindByIndex(Ptr T, int index, DataType* data);
bool FindByData(Ptr T, DataType data, int* index);
bool DeleteNode(Ptr T, int index);
bool ClearTree(Ptr T);
bool UpdateNode(Ptr T, int index, DataType data);
int CountNodes(Ptr T);
int GetHeight(Ptr T);
bool IsEmpty(Ptr T);
bool IsFull(Ptr T);

//traverse the tree and print the data of each node
void PreOrder(Ptr T, int i);
void InOrder(Ptr T, int i);
void PostOrder(Ptr T, int i);
void LevelOrder(Ptr T);
void PrintTree(Ptr T);

int main(){
    int chioce = -1;
    BTree T, *pt = &T;
    InitBTree(pt);
    DataType data;
    int index;
    while(chioce != 0){
        printf("1. Print Tree\n");
        printf("2. Insert Node\n");
        printf("3. Find Node By Index\n");
        printf("4. Find Node By Data\n");
        printf("5. Update Node\n");
        printf("6. Delete Node\n");
        printf("7. Count Nodes\n");
        printf("8. Get Height\n");
        printf("9. Clear Tree\n");
        printf("0. Exit\n");
        if(scanf("%d", &chioce) != 1){
            while(getchar() != '\n');  // 清掉坏输入
            continue;
        }
        switch(chioce){
            case 1:{
                PrintTree(pt);
                break;
            }
            case 2:{
                printf("Enter index and data to insert: ");
                scanf("%d %d", &index, &data);
                if(InsertNode(pt, index, data)){
                    printf("Inserted successfully.\n");
                } else {
                    printf("Insert failed.\n");
                }
                break;
            }
            case 3:{
                printf("Enter index to find: ");
                scanf("%d", &index);
                if(FindByIndex(pt, index, &data)){
                    printf("Data at index %d is %d.\n", index, data);
                } 
                else {
                    printf("Find failed.\n");
                }
                break;
            }
            case 4:{
                printf("Enter data to find: ");
                scanf("%d", &data);
                if(FindByData(pt, data, &index)){
                    printf("Data %d found at index %d.\n", data, index);
                } 
                else {
                    printf("Find failed.\n");
                }
                break;
            }
            case 5:{
                printf("Enter index and new data to update: ");
                scanf("%d %d", &index, &data);
                if(UpdateNode(pt, index, data)){
                    printf("Updated successfully.\n");
                }
                else {
                    printf("Update failed.\n");
                }
                break;
            }
            case 6:{
                printf("Enter index to delete: ");
                scanf("%d", &index);
                if(DeleteNode(pt, index)){
                    printf("Deleted successfully.\n");
                }
                else {
                    printf("Delete failed.\n");
                }
                break;
            }
            case 7:{
                printf("Total nodes: %d\n", CountNodes(pt));
                break;
            }
            case 8:{
                printf("Height of tree: %d\n", GetHeight(pt));
                break;
            }
            case 9:{
                if(ClearTree(pt)){
                    printf("Tree cleared successfully.\n");
                }
                else {
                    printf("Clear failed.\n");
                }
                break;
            }
            case 0:{
                printf("Exiting...\n");
                break;
            }
            default:{
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }
    return 0;
}

void InitBTree(Ptr T){
    T->size = 0;
    for(int i=0; i<MaxSize; i++){
        T->Data[i] = NoData;
    }
}
bool InsertNode(Ptr T, int index, DataType data){
    if(IsFull(T) || index < 0 || index > T->size){
        return false;
    }
    if(T->Data[index] != NoData){
        return false;
    }
    T->Data[index] = data;
    T->size++;
    return true;
}
bool FindByIndex(Ptr T, int index, DataType* data){
    if(index < 0 || index >= T->size || T->Data[index] == NoData){
        return false;
    }
    *data = T->Data[index];
    return true;
}
bool FindByData(Ptr T, DataType data, int* index){
    for(int i=0; i<T->size; i++){
        if(T->Data[i] == data){
            *index = i;
            return true;
        }
    }
    return false;
}
bool DeleteNode(Ptr T, int index){
    if(IsEmpty(T) || index < 0 || index >= T->size || T->Data[index] == NoData){
        return false;
    }
    T->Data[index] = NoData;
    T->size--;
    if(index == 0){
        ClearTree(T);
    }
    int leftpos = 2 * index + 1;
    int rightpos = 2 * index + 2;
    for(int i = leftpos; i < T->size; i++){
        if(i > rightpos){
            leftpos = 2 * leftpos + 1;
            rightpos = 2 * leftpos + 2;
        }
        if((i>=leftpos && i<=rightpos) && T->Data[i] != NoData){
            T->Data[i] = NoData;
            T->size--;
        }
    }
    return true;
}
bool ClearTree(Ptr T){
    if(T==NULL){
        return false;
    }
    for(int i=0; i<T->size; i++){
        T->Data[i] = NoData;
    }
    T->size = 0;
    return true;
}
bool UpdateNode(Ptr T, int index, DataType data){
    if(T==NULL || index < 0 || index >= T->size){
        return false;
    }
    T->Data[index] = data;
    return true;
}
int CountNodes(Ptr T){
    if(T==NULL){
        return -1;
    }
    int count = 0;
    for(int i=0; i<T->size; i++){
        if(T->Data[i] != NoData) count++;
    }
    return count;
}
int GetHeight(Ptr T){
    if(T==NULL) return -1;
    if (T->size==0) return 0;
    int log= 0;
    int n = T->size;
    while(n > 0){
        n /= 2;
        log++;
    }
    return log;
}
bool IsEmpty(Ptr T){
    if(T==NULL){
        return true;
    }
    return T->size == 0;
}
bool IsFull(Ptr T){
    if(T==NULL){
        return false;
    }
    return T->size == MaxSize;
}

//traverse the tree and print the data of each node
// 先序遍历：根 → 左 → 右
void PreOrder(Ptr T, int i) {
    if (i < 0 || i >= MaxSize || T->Data[i] == NoData) return;
    printf("%d ", T->Data[i]);      // 根
    PreOrder(T, 2 * i + 1);         // 左
    PreOrder(T, 2 * i + 2);         // 右
}

// 中序遍历：左 → 根 → 右（就是你说的那个）
void InOrder(Ptr T, int i) {
    if (i < 0 || i >= MaxSize || T->Data[i] == NoData) return;
    InOrder(T, 2 * i + 1);          // 左
    printf("%d ", T->Data[i]);      // 根
    InOrder(T, 2 * i + 2);          // 右
}

// 后序遍历：左 → 右 → 根
void PostOrder(Ptr T, int i) {
    if (i < 0 || i >= MaxSize || T->Data[i] == NoData) return;
    PostOrder(T, 2 * i + 1);        // 左
    PostOrder(T, 2 * i + 2);        // 右
    printf("%d ", T->Data[i]);      // 根
}

// 层序遍历：按层从上到下，从左到右访问每个节点
void LevelOrder(Ptr T){
    for (int i = 0; i < T->size; i++) {
        if (T->Data[i] != NoData) {
            printf("%d ", T->Data[i]);
        }
    }
}

void PrintTree(Ptr T){
    if(T==NULL){
        printf("Tree is NULL\n");
        return;
    }
    printf("Tree (Level Order): ");
    LevelOrder(T);
    printf("\nTree (Pre Order): ");
    PreOrder(T, 0);
    printf("\nTree (In Order): ");
    InOrder(T, 0);
    printf("\nTree (Post Order): ");
    PostOrder(T, 0);
    printf("\n");
}