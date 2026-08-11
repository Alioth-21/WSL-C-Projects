---
title: "1-4 Queue"
tags: [C, DataStructure, LinearList, Queue]
---

# 1. Introduction

1. Concept
     Queue is a linear data structure that follows the First In First Out (FIFO) principle. Elements are added at the rear and removed from the front.

2. Types of Queue
    -storage structures:
        - Sequential Queue (Array-based)
        - Linked Queue (Linked List-based)
    - Purpose:
        - Circular Queue
        - Priority Queue
        - Double-ended Queue (Deque)

# 2. Cricular Queue

> 主要由顺序存储实现，使用数组模拟循环队列。

## 1.1 statci

1. define

    ```C
    #define MAXSIZE 5
    typedef struct{
        DataType Data[MAXSIZE];
        int Front, Rear;
    }Queue, *PtrQ;
    ```
2. Judgement

    ```C
    bool IsEmpty(PtrQ Q){
        return Q->Front == Q->Rear;
    }
    bool IsFull(PtrQ Q){
        return (Q->Rear + 1) % MAXSIZE == Q->Front;
    }
    int GetLength(PtrQ Q){
        return (Q->Rear - Q->Front + MAXSIZE) % MAXSIZE;
    }
    ```


## 1.2 dynamic

1. define

    ```C
    typedef struct{
        DataType *Data;
        int Front, Rear;
        int Length;
        int Capacity;
    }Queue, *PtrQ;
    ```

# 3. Deque

# 4. Priority Queue


---
