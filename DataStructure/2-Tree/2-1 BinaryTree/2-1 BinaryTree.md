---
title: "2-Tree"
tags: ["DataStructure"]
---

# 1. Binary Tree

## 1.1 Seq-Binary Tree
> Sequential Storage 

### 1.1.1 Data Array 

1. 定义

    ```c
    // Seq-Binary Tree built by DataArray
    typedef struct{
        ElemType *Data;
        int Size, Length;
    }BinaryTree;
    ```

2. 结点的存储位置

    > 设根结点的存储位置为 1，则对于任意结点 i：
    > - 左孩子结点的存储位置为 2*i
    > - 右孩子结点的存储位置为 2*i+1
    > - 双亲结点的存储位置为 i/2

3. 结构关系

    ```txt
        1        → tree[0]
       / \
      2   3      → tree[1], tree[2]
     / \ / \
    4  5 6  7    → tree[3], tree[4], tree[5], tree[6]
    ```
> 按照层序存储在数组
> 即便结点的左孩子或右孩子为空，也要在数组中占据位置。

### 1.1.2 struct array
> 
> struct {data, left, right} tree[n]

### Seq-Binary Summary

- 值数组:int tree[n]	95%	堆、优先队列、完全二叉树、算法竞赛

- 结构体数组 struct {data, left, right}	5%	静态内存池、嵌入式开发、特殊面试题

## 1.2 Link-Binary Tree

# 2. Operations

## 2.1 Traversal

```txt
树结构：
        1       ← 根节点
       / \
      2   3
     / \ / \
    4  5 6  7
```

- 先序遍历	根 → 左 → 右	根左右	1, 2, 4, 5, 3, 6, 7
- 中序遍历	左 → 根 → 右	左根右	4, 2, 5, 1, 6, 3, 7
- 后序遍历	左 → 右 → 根	左右根	4, 5, 2, 6, 7, 3, 1
- 层序遍历	按层访问   每层从左到右  1, 2, 3, 4, 5, 6, 7

### 2.1.1 PreOrder
### 2.1.2 InOrder
### 2.1.3 PostOrder
### 2.1.4 LevelOrder

---