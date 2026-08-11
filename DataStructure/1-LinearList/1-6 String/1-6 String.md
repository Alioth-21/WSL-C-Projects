---
title: "1-6 String"
tags: [C, DataStructure, LinearList, String]
---

# 1. Define

## 1.1 Static String

1. define

    ```C
    #define MAXSIZE 100
    typedef struct{
        char ch[MAXSIZE];
        int length;
    }String, *PtrS;
    ```

## 1.2 Dynamic String

1. define

    ```C
    typedef struct{
        char *ch;
        int length;
    }String, *PtrS;
    ```

## 1.3 Linked String

1. define

    ```C
    typedef struct Node *Ptr;

    struct Node{
        char Data;
        Ptr Next;
    };
    ```

---

# 2. Operations

## 2.1 Basic functions

| 操作 | 函数名 | 本质 | 时间复杂度|
|---|---|---|---|
| 读字符 | CharAt(S, pos) | 返回 S.ch[pos] | O(1) | 
| 写字符 | SetChar(S, pos, c) | S.ch[pos] = c | O(1) | 
| 分配空间 | AllocString(S, len) | S.ch = (char*)malloc(len) | O(1) | 
| 释放空间 | FreeString(S) | free(S.ch) | O(1) | 

---

## 2.2 tools functions


| 操作 | 函数名 | 本质 | 时间复杂度|
|---|---|---|---|
| 求长度 | StrLength(S) | 返回 S.length 字段 | O(1) |
| 判空 | StrEmpty(S) | return S.length == 0 | O(1) |
| 复制 | StrCopy(&T, S) | for(...) T.ch[i] = S.ch[i] | O(n) |
| 比较 | StrCompare(S, T) | for(...) if(S[i]!=T[i]) return S[i]-T[i] | O(n) |
| 清空 | ClearString(&S) | free(S.ch); S.ch=NULL; S.length=0 | O(1) |
| 连接 | Concat(&T, S1, S2) | T.ch = malloc(len1+len2); 拷贝S1; 拷贝S2 | O(n+m) |

---

## 2.3 Advanced functions

| 操作 | 函数名 | 本质 | 时间复杂度|
|---|---|---|---|
| 子串定位（BF） | Index_BF(S, T, pos) | 暴力双重循环 | O(n*m) |
| 子串定位（KMP） | Index_KMP(S, T, pos) | 计算next数组 | O(n+m) |
| 求子串 | SubString(&Sub, S, pos, len) | for(...) Sub[i] = S[pos+i] | O(len) |
| 插入 | StrInsert(&S, pos, T) | Index（先定位） + 挪动字符 + 拷贝T | O(n+m) |
| 删除 | StrDelete(&S, pos, len) | Index（先定位） + 挪动字符 | O(n) |
| 替换 | StrReplace(&S, T, V) | Index（循环定位） + StrDelete + StrInsert | O(k*(n+m)) |
| 反转 | ReverseString(S) | 双指针交换，while(i<j) swap(S[i], S[j]) | O(n) |
| 去重 | RemoveDuplicate(S) | 哈希表记录已出现字符 | O(n) |
| 最长回文子串 | LongestPalindrome(S) | 中心扩展或马拉车算法 | O(n²) ~ O(n) |
| 编辑距离 | EditDistance(S, T) | 二维DP | O(n*m) |

---

# 3. Patterns Matching

## 3.1 Brute Force (BF) Algorithm

## 3.2 Knuth-Morris-Pratt (KMP) Algorithm