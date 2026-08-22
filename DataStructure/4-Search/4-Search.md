---
title: "4 Search"
tags: ["DataStructure"]
---

# 查找算法（Searching Algorithms）

>查找算法的核心分类逻辑：静态查找（数据不动） vs 动态查找（数据常变）。

分类	中文名称	标准英文名称	别名 / 工程叫法	核心特点
顺序表查找	顺序查找	Sequential Search	Linear Search（线性查找）	暴力遍历，O(n)，不要求有序
折半查找	Binary Search	Half-Interval Search	必须有序，O(log n)，用判定树分析ASL
分块查找	Block Search	Index Sequential Search（索引顺序查找）	块间有序，块内无序。查索引表（折半）+ 入块（顺序）
树形查找	二叉排序树	Binary Sort Tree (BST)	Binary Search Tree	左小右大，中序有序。删除操作最复杂
平衡二叉树	Balanced Binary Tree / AVL Tree	以发明者 Adelson-Velsky 和 Landis 命名	严格平衡（平衡因子 |bf| ≤ 1），旋转修复（LL/RR/LR/RL）
红黑树	Red-Black Tree (RBT)	近似平衡的BST	插入/删除旋转次数少，Java HashMap / C++ std::map 底层
B-树	B-Tree	Balanced Multi-way Tree（多路平衡树）	m阶，节点有多个分叉，磁盘I/O友好
B+树	B+ Tree	经典变种	所有数据在叶子，叶子间有链表指针，MySQL InnoDB 索引 底层
散列查找	哈希查找	Hash Search	散列查找	通过哈希函数直接定位，O(1) 平均
Open Addressing（开放地址法）	Linear Probing（线性探测）、Quadratic Probing（平方探测）、Double Hashing（再哈希）	冲突时找下一个空位
Separate Chaining（链地址法）	Closed Addressing（闭散列），拉链法	冲突位置挂链表，最常用
字符串查找	KMP 算法	KMP Algorithm	Knuth-Morris-Pratt	字符串匹配，利用部分匹配表（PMT，Partial Match Table，即next数组） 避免回溯
二