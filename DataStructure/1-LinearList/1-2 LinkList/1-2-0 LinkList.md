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

## 1.3 循环链表 Circular Linked List

### 1.3.1 循环单链表 Circular Single Linked List

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
    typedef struct LinkList *PtrL;

    struct LinkList{
        Ptr Head, Tail;
        int Length;
    };
    ```

### 1.3.2 循环双链表 Circular Double Linked List

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
    typedef struct{
        Ptr Head, Tail;
        int Length;
    }LinkList;
    ```

---

## 1.4 静态链表 Static Linked List

### 1.4.1 静态链表：结构数组AoS（Array of Structures）

1. 节点Node

    ```c
    typedef struct Node{
        ElemType Data;
        int Next;
    }Node;
    ```
2. 链表List

    ```c
    typedef struct LinkList{
        Node Nodes[MAXSIZE];
        int Head, Tail;
        int Length;
    }LinkList;
    ```

### 1.4.2 静态链表：数组结构体SoA（Structure of Arrays）
> 双数组实现，数据和指针分离为两个数组

1. 定义

    ```c
    typedef struct LinkList{
        ElemType Data[MAXSIZE];
        int Next[MAXSIZE];
        int Head, Tail;
        int Length;
    }LinkList;
    ```

---

# 2. 操作功能 Operations

> C - Create  (增)  → 插入、添加、创建
> R - Read    (查)  → 查找、访问、遍历  
> U - Update  (改)  → 修改、更新、替换
> D - Delete  (删)  → 删除、移除、销毁


## 2.1 关键功能


### 2.1.1 插入节点 Insert node

1. 分析
    - 插入位置index的范围：[0, Length]，index==Length表示尾插

    - 插入的三种情况
        1. 插入位置index==0，头插
        2. 插入位置index==Length，尾插
        3. 插入位置0<index<Length，中间插入

    - 插入的特殊情况：
        - 插入第一个节点：表为空，index==0，头插
        - 有尾指针的链表，尾插时不需要遍历到尾节点，直接使用尾指针即可
    
2. 设计
    - 高层函数：`bool InsertNode(PtrL List)`
        - 判断表是否已满
        - 输入插入位置index和数据data
        - 判断index是否合法
        - 调用低层函数执行插入操作
    - 低层函数：
        - 头插：`bool InsertHead(PtrL List, ElemType data)`
        - 尾插：`bool InsertTail(PtrL List, ElemType data)`
        - 中间插入：`bool InsertMiddle(PtrL List, int index, ElemType data)`
3. 实现

    ```c
    bool InsertNode(PtrL List){
        if(IsFull(List)){
            printf("List is full, cannot insert node.\n");
            return false;
        }
        int index;
        ElemType data;
        printf("Enter the index to insert (0 to %d): ", List->Length);
        scanf("%d", &index);
        if(!CheckIndex(List, index)){
            printf("Invalid index, cannot insert node.\n");
            return false;
        }
        printf("Enter the data to insert: ");
        scanf("%d", &data);
        if(index == 0){
            return InsertHead(List, data);
        } else if(index == List->Length){
            return InsertTail(List, data);
        } else {
            return InsertMiddle(List, index, data);
        }
    }
    bool InsertHead(PtrL List, ElemType data){
        Ptr newNode = CreateNode(data);
        if(!newNode) return false;
        newNode->Next = List->Head;
        List->Head = newNode;
        if(List->Length == 0){
            List->Tail = newNode;
        }
        List->Length++;
        return true;
    }
    bool InsertTail(PtrL List, ElemType data){
        Ptr newNode = CreateNode(data);
        if(!newNode) return false;
        newNode->Next = NULL;
        List->Tail->Next = newNode;
        List->Tail = newNode;
        List->Length++;
        return true;
    }

    bool InsertAt(PtrL List, int index, ElemType data){
        //...
    }
    ```

### 2.1.2 删除节点 Delete node


1. 分析
    - 删除位置`index`的范围：[0, Length-1]
        - `index`==`Length`-1 表示删除尾节点
        - `index`==`Length` 删除位置不合法，报错

    - 删除的三种情况
        1. 删除位置：`index`==0，头删
        2. 删除位置：`index`==`Length`-1，尾删
        3. 删除位置：0<`index`<`Length`-1，中间删除

    - 删除的特殊情况:
        - 删除唯一节点, 既是头节点又是尾节点，删除位置`index`==0，头删
        - 非头节点的删除，需要遍历到前一个节点维持链表逻辑
2. 设计
    - 高层函数：`bool DeleteNode(PtrL List)`
        - 判断表是否为空
        - 输入删除位置`index`
        - 判断`index`是否合法
        - 调用低层函数执行删除操作
    - 低层函数：
        - 头删：`bool DeleteHead(PtrL List)`
        - 尾删：`bool DeleteTail(PtrL List)`
        - 中间删除：`bool DeleteAt(PtrL List, int index)`

3. 实现

    ```c
    bool DeleteNode(PtrL List){
        if(IsEmpty(List)){
            printf("List is empty, cannot delete node.\n");
            return false;
        }
        int index;
        printf("Enter the index to delete (0 to %d): ", List->Length - 1);
        scanf("%d", &index);
        if(!CheckIndex(List, index)){
            printf("Invalid index, cannot delete node.\n");
            return false;
        }
        if(index == 0){
            return DeleteHead(List);
        } 
        else if(index == List->Length - 1){
            return DeleteTail(List);
        } 
        else {
            return DeleteAt(List, index);
        }
    }
    // 低层函数实现
    //
    //
    ```
---

## 2.2 其他主要功能

### 2.2.1 初始化

1. 初始化链表 InitList
2. 初始化节点 InitNode

### 2.2.2 判断

1. 判断链表是否为空 IsEmpty
2. 判断链表是否已满 IsFull
3. 判断index是否合法 CheckIndex

### 2.2.3 遍历和查找

1. 遍历链表 TraverseList
2. 输出链表 PrintList
3. 按位查找 FindByIndex
4. 按值查找 FindByData

### 2.2.4 获取和设置节点数据
> Get返回能修改的指针，Set直接修改数据成员
1. 获取链表长度 GetLength
2. 获取节点 GetNode
3. 获取节点数据 GetElem
4. 获取节点前驱 GetPrevNode/GetPriorNode
5. 设置节点数据 SetData

### 2.2.5 删除和销毁链表

1. 删除节点 DeleteNode
2. 清空链表 ClearList
3. 销毁链表 DestoryList

## 2.3 功能划分：高层+底层

### 2.3.1 高层函数（编排调度）High-level functions
> 总体功能划分

## 2-2 底层函数（具体执行）Low-level functions

> 具体基本功能实现


# 3. Main 函数



# 4. 宏定义 

1. 链表长度上限 MAXSIZE

2. 找不到 NotFound

# 5. Notes

## 5.1 循环链表的特殊情况

1. 循环导致头插和尾插结构上等价，逻辑上不等价

2. 特殊情况
    - 插入第一个节点：插入位置index==0，只能是头插，所以只需要头插判断表是否为空
    - 删除表中唯一节点：删除位置index==0，只能是头删，所以只需要头删判断表是否只有一个节点

## 5.3 静态链表的两种实现方式
>AoS是主流80%，SoA在特定领域统治。

### 5.3.1 AoS（Array of Structures）

- 结构体数组

### 5.3.2 SoA（Structure of Arrays）
- 数组结构体
- 双数组
    - 数据数组
    - 指针数组

---
