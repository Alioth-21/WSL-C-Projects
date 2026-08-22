---
title: "5-Sort"
tags: ["DataStructure"]
---

# 排序算法（Sorting Algorithms）

> 排序算法的核心分类逻辑：比较类排序（基于比较） vs 非比较类排序（基于分配）。

1. 插入类排序（Insertion Sorts）—— 像打牌理牌
中文名称	标准英文名称	别名 / 变种	稳定性	特点
直接插入排序	Insertion Sort	Straight Insertion Sort	✅ 稳定	数据基本有序或数据量小时极快
折半插入排序	Binary Insertion Sort	在插入时用二分查找定位	✅ 稳定	比较次数减少，但移动次数不变
希尔排序	Shell Sort	Diminishing Increment Sort（递减增量排序）	❌ 不稳定	第一个突破 O(n²)，增量序列（Gap Sequence）是关键
2. 交换类排序（Exchange Sorts）—— 通过交换归位
中文名称	标准英文名称	别名 / 变种	稳定性	特点
冒泡排序	Bubble Sort	Sinking Sort（下沉排序）	✅ 稳定	可加 flag 优化提前终止
快速排序	Quick Sort	Hoare's Partition（以发明人 Hoare 命名）	❌ 不稳定	工业界最常用。核心是 Partition 函数。最坏 O(n²)（基准差）
3. 选择类排序（Selection Sorts）—— 每次选最值
中文名称	标准英文名称	别名 / 变种	稳定性	特点
简单选择排序	Selection Sort	Straight Selection Sort	❌ 不稳定	交换次数最少（最多 n-1 次）
堆排序	Heap Sort	基于二叉堆（Binary Heap） 实现	❌ 不稳定	空间 O(1)，取 Top K 神器。操作：Build Heap + Sift Down
4. 归并类排序（Merge Sorts）—— 分治法的典范
中文名称	标准英文名称	别名 / 变种	稳定性	特点
归并排序	Merge Sort	递归版：Top-Down Merge Sort
迭代版：Bottom-Up Merge Sort	✅ 稳定	空间 O(n)，牺牲内存换稳定。链表排序首选
5. 非比较类排序（Non-Comparison Sorts）—— 突破 O(n log n) 下限
中文名称	标准英文名称	别名 / 变种	稳定性	适用场景
计数排序	Counting Sort	鸽巢排序的泛化	✅ 稳定	数据范围（k）小且密集，O(n+k)
基数排序	Radix Sort	LSD（Least Significant Digit，最低位优先）/ MSD（Most Significant Digit，最高位优先）	✅ 稳定（通常实现）	整数或定长字符串，O(d(n+r))
桶排序	Bucket Sort	Bin Sort（箱排序）	✅（取决于桶内排序）	数据分布均匀，O(n+k)
6. 混合排序（Hybrid Sorts）—— 工程中的王者
中文名称	标准英文名称	别名 / 实现	设计思路
内省排序	Introsort	Introspective Sort	C++ STL std::sort 采用。快排 + 堆排 + 插入排序的混合体。递归深度过大时切到堆排，小数据量切到插入排序
Timsort	Timsort	Python list.sort() / Java Arrays.sort() (对象数组) 采用	归并 + 插入。利用数据中已有的有序片段（Run） 进行归并，非常高效
三、速查表（面试/考试前看一眼）
查找速查
数据结构	算法	平均时间	是否有序
数组	Binary Search	O(log n)	✅ 必须有序
BST / AVL / RBT	Tree Search	O(log n)	树中序有序
哈希表	Hash Search	O(1)	❌ 不要求
索引表	Block Search	O(log m + n/m)	索引有序
排序稳定性和复杂度速查
算法	平均	最坏	空间	稳定性
Quick Sort	O(n log n)	O(n²)	O(log n)	❌
Merge Sort	O(n log n)	O(n log n)	O(n)	✅
Heap Sort	O(n log n)	O(n log n)	O(1)	❌
Shell Sort	O(n^1.3)	O(n²)	O(1)	❌
Insertion Sort	O(n²)	O(n²)	O(1)	✅
Bubble Sort	O(n²)	O(n²)	O(1)	✅
Selection Sort	O(n²)	O(n²)	O(1)	❌
Counting / Radix / Bucket	O(n+k)	O(n+k)	O(k)	✅（通常）
