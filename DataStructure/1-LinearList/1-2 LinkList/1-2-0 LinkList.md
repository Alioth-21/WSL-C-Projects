// LinkList

# 1. 链表的定义 Define

## 1.1 单链表

1. 节点Node

    ```c
    typedef struct Node *Ptr;

    struct LNode{
        ElemType Data;
        Ptr Next;
    };
    ```

2. 链表List

    ```c
    typedef struct LNode *PtrL;

    struct LinkList{
        Ptr Head, Tail;
        int Length;
    };
    ```

## 1.2 双链表 Double Linked List

1. 节点Node

    ```c
    typedef struct Node *Ptr;

    struct Node{
        ElemType Data;
        Ptr Prior, Next;
    };
    ```

2. 链表List

    ```c
    typedef struct LinkList *PtrL;

    struct LinkList{
        Ptr Head, Tail;
        int Length;
    };
    ```

# 2. 操作功能 Operations

## 2.1 高层函数（编排调度）High-level functions

### 2.1.1 初始化链表 InitList

1. 给链表分配内存空间 Allocate memory for the linked list
2. 初始化数据成员 Initialize the data members
3. 返回链表指针 Return the pointer to the linked list

```c
PtrL InitList(){
    PtrL P = (PtrL)malloc(sizeof(struct LinkList));
    P->Length = 0;
    P->Head = P->Tail = NULL;
    return P;
}
```

### 2-1-2 插入节点

1. 判断链表是否已满 IsFull

2. 输入插入节点的数据和位置 Data and Index of the inserted node  

3. index是否合法，
    - 插入位置: [0, Length]
    
    ```C
    bool CheckIndex(PtrL L, int index){
        return (index >= 0 && index <=> L->Length);
    }
    ```

    - 空表插入第一个节点

4. 创建新节点 Create a new node
    - 动态分配新节点内存空间
    - 初始化新节点数据成员
    - 返回新节点指针 Return the pointer to the new node

    ```c
    Ptr CreateNode(ElemType data){
        Ptr P = (Ptr)malloc(sizeof(struct LNode));
        P->Data = data;
        P->Next = NULL;
        return P;
    }
    ``` 
    
4. 插入节点 Insert the node
    - 空表插入
    - 头部插入
    - 尾部插入
    - 中间插入

### 2-1-3 删除节点

1. 判断链表是否为空 IsEmpty

2. 输入删除节点的位置 delete node index

3. 位置是否合法
    - 删除位置: [0, Length-1]
    
    ```C
    bool CheckIndex(PtrL L, int index){
        return (index >= 0 && index < L->Length);
    }
    ```

4. 删除节点 Delete the node
    - 删除最后一个节点
    - 头部删除
    - 尾部删除
    - 中间删除

### 2-1-4 查找节点 Find node

1. 数据查找 FindByData
    - 返回index
2. 位置查找 FindByIndex
    - 检查 index是否合法 CheckIndex
### 2.1.5 更新节点 Update node

1. 查找节点 Find node by index
2. 更新节点数据 Update node data
### 2.1.6 遍历表 Traverse the list

### 2.1.7 清空节点和销毁链表 

1. 清空链表 ClearList
    - 遍历删除全部节点
    - Length = 0

2. 销毁链表 DestoryList
    - ClearList
    - Free(List)

## 2-2 底层函数（具体执行）Low-level functions

### 2-2-1 判断 Judge

1. 判断链表是否为空 IsEmpty
2. 判断链表是否已满 IsFull
3. 判断index是否合法 CheckIndex
4. 判断插入index是否合法 CheckInsertIndex

### 2-2-2 读取 Get
1. 获取链表长度 GetLength
2. 获取节点 GetNode
3. 获取节点前驱 GetPrevNode/GetPriorNode
3. 获取节点数据 GetElem

### 2-2-3 节点创建修改 Create&Set

1. 创建新节点 CreateNode
2. 设置节点数据 SetData

### 2.2.4 查找
1. 数据查找 FindByData
2. 位置查找 FindByIndex 

### 2.2.5 插入
1. 表头插入 InsertHead
2. 表尾插入 InsertTail
3. 中间插入 InsertAtIndex

### 2-2-4 删除
1. 表头删除 DeleteHead
2. 表尾删除 DeleteTail
3. 中间删除 DeleteAtIndex



# 3. 交互

> Main 函数使用 `while(chioce)` + `scanf` + `switch` 的 CLI 菜单循环。

```C
int main(){
    PtrL L = InitList();
    int chioce;
    while(chioce){
        printf("1. InsertNode\n");
        printf("2. DeleteNode\n");
        printf("3. FindNode\n");
        printf("4. UpdateNode\n");
        printf("5. ClearList\n");
        printf("0. Exit\n");
        scanf("%d", &chioce);
        switch(chioce){
            case 1:
                // InsertNode
                break;
            case 2:
                // DeleteNode
                break;
            case 3:
                // FindNode
                break;
            case 4:
                // UpdateNode
                break;
            case 5:
                // ClearList
                break;
            case 0:
                // DestoryList & Exit
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
```

# 4. 宏定义 

1. 链表长度上限 MAXSIZE

2. 找不到 NotFound

# 5. Notes

## 5.1 Inset和Delete的高低层函数划分

1. List作为参数判断
    - List为空指针：初始化函数中解决，后续不需要判断

2. 插入删除
    - 表的空和满
    - index是否合法
    - 插入时表是否为空表
    - 删除时表是否只有一个节点

3. 函数分层
    - 原本计划：
        - 高层函数负责所有判断
        - 低层函数负责执行，为void
        但是为了程序的健壮性，两层都需要对表的空满、index范围、插入第一个节点、删除最后一个节点，进行判断

    - 现在情况：
        - 高层函数判断：表的空满、index范围（false输出信息）
        - 低层函数判断：表的空满、index范围、插入第一个节点和删除最后一个节点的特殊处理分支
        - 低层函数中对表的空满、index范围、插入第一个节点、删除最后一个节点，进行判断，并打印错误信息 