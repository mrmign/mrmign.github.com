---
layout: post
title: "mastering algorithms with c"
description: "Notes about << mastering algorithms with c >>"
category: [Reading, Book]
tags: [algorithm, C]
---
{% include JB/setup %}

## Chapter 5 List
Q&A 第四个问题的答案说，如果删除一个结点用O(1)的方法会导致危险的负面影响。`Why???`

>Benign O(1) approch generates the dangerous side effect of rendering a pointer into the list invalid.

## Chapter 7 Set
Set的实现用了List来模拟。

## Chapter 8 Hash Tables
一些哈希表的应用:
1. 数据库系统
2. 符号表（编译器中用）
3. 标签缓冲区(Tagged buffers)
4. 数据字典(Data Dictionaries)
5. 关联数组(Associative arrays)
