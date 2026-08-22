---
title: "3-1 Graph Storage Structures"
tags: ["DataStructure", "Graph"]
---

# 1. Graph Storage Structures

## 1.1 Adjacency List

### 1.1.1 Introduction

1. 邻接表（Adjacency List）
    - 标准术语：Adjacency List
    - 常用缩写：AL

    - 代码变量：通常叫 adjList 或 adj

2. 含义：用一组链表（或动态数组）存储每个顶点的邻居。

3. 地位：绝对霸主（约 70% ~ 80%）
    
    工业界和算法竞赛的默认首选。

4. 原因：

    - 现实世界中的图（社交网络、网页链接、路网）都是稀疏图（边数远小于顶点数的平方）。

    - 邻接表存储空间为 O(V+E)，极其节省内存。

5. 出现场景：

    - 90% 的 LeetCode 图论题

    - 所有的 vector<int> adj[n] 写法

    - Spark GraphX 等大数据框架。


## 1.2 Adjacency Matrix

### 1.2.1 Introduction

1. 邻接矩阵（Adjacency Matrix）
    标准术语：Adjacency Matrix
    常用缩写：AM 或 Mat

    代码变量：通常叫 adjMat 或 matrix

2. 含义：用一个二维网格表示顶点之间是否有边。

3. 特定领域的王牌（约 15% ~ 25%）

4. 地位：在特定场景下无法被替代。

5. 原因：

    稠密图（边非常多）时，矩阵的 O(1) 边查询速度优于邻接表。

    硬件加速：矩阵运算极其适合 GPU 和 AI 框架（如 GNN 中的邻接矩阵乘法）。

6. 出现场景：

    图神经网络（GNN）、动态规划（如 Floyd 算法）、传递闭包计算。

    在算法竞赛中，当顶点数 V≤500 时，选手也会毫不犹豫地用矩阵（简单好写）。

## 1.3 Orthogonal List

### 1.3.1 Introduction

1. 十字链表（Orthogonal List）
    标准术语：Orthogonal List 或 Orthogonal Linked List
    常用缩写：OL （极少见，通常直接写全称）

    代码变量：通常叫 orthList 或 crossList

2. 含义：专用于有向图，同时记录出度和入度弧。因为链表交叉成网状，所以叫十字。

3. 地位：特定有向图的利器（约 2% ~ 3%）
    教科书意义大于工程意义，但在特定数据库中有奇效。

4. 原因：它同时维护了出边和入边，虽然很强大，但实现极其复杂（需要定义弧头、弧尾、同头指针、同尾指针）。

5. 出现场景：
    仅出现在底层图数据库（如 Neo4j 的部分索引结构）、编译原理中的语法分析，以及高校的数据结构大作业中。

    在普通后端开发中极少手写。

## 1.4 Adjacency Multilist

### 1.4.1 Introduction

1. 邻接多重表（Adjacency Multilist）
    标准术语：Adjacency Multilist （也有写成 Multi-list 的）
    常用缩写：AML

    代码变量：通常叫 multiList 或 adjMultilist

2. 含义：专用于无向图，边只存一份，避免重复，方便增删边。

3. 地位：无向图的“删边神器”（约 1% ~ 2%）
    最不常用的教科书结构。

4. 原因：
    它解决了无向图中邻接表存一条边要存两次的冗余问题，使得删除一条边非常快。
    
    但在现代高级语言中，程序员更愿意用 set 或哈希集合来处理边的删除，而非手动维护这么复杂的指针。

5. 出现场景：仅在计算几何（处理平面图）或网络流算法（需要频繁回溯增删边）的底层优化中使用。