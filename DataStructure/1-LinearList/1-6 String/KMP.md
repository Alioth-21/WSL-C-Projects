---
title: KMP算法
date: 2024-06-10 20:00:00
categories:
- DataStructure
- LinearList
- String
---

# 1. Next数组的构建

## 1.1 长度型的Next数组

1. 定义

    - next数组长度为模式串长度
    
    - next[i]表示模式串的子串 P[0..i] 的最长公共前后缀的长度

    - next数组的下标i

2. 构建过程
    
    > 求模式串的各个前缀子串的最长公共前后缀长度

    - 设置next[0] = 0：单元素（长度为1）的子串没有前后缀

    - 设置两个下标指针分别指向模式串的前缀和后缀，分别为i和j，初始值为0和1

    - 循环从短到长遍历模式串的前缀子串

    - 判断：
        
        - P[i] == P[j]：j++, next[i] = j;

        - P[i] != P[j]:
            - i=0: next[j] = 0, j++
            - i>0: j = next[i-1]        //循环回退

3. 代码实现

    ```C
    void SetNext(char* P, int* next, int plen){
        next[0] = 0;
        int i = 0, j = 1;
        for(int i=1; i<len; i++){ 
            while(j>0 && P[i] != P[j]){     //回退
                j = next[j-1];
            }
            if(P[i] == P[j]){
                j++;                 //最长公共前后缀长度加1
            }
            next[i] = j;             //更新当前next数组元素
        }
    }
    ```


## 1.2 下标型的Next数组


# 2. KMP算法的实现

## 2.1 长度型next数组对应的KMP算法

1. 实现

    - 设置遍历指针
        
        - i: 主串S[slen]的指针，初始值为0

        - j: 模式串P[plen]的指针，初始值为0

    - 主循环判断主串和模式串遍历下标分别小于各自长度

    - 匹配成功时：i++, j++

    - 匹配失败时：

        - 主串指针`i`不回退

        - 模式串指针`j`回退到next[j-1]，即模式串回退到最长公共前后缀的下一个位置

## 2.2 下标型next数组对应的KMP算法