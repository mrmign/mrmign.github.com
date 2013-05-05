---
layout: post
title: "编程之美－3.3　计算字符串的相似度"
description: "关于编程之美中的问题。"
category: algorithm
tags: [algorithm]
---
{% include JB/setup %}

用动态规划来解，先求出字符串Ａ与字符串Ｂ的最长公共子序列lcs,然后用`max(len(A), len(B)) - len(lcs)` 得到一个长度l,也就是Ａ与Ｂ的距离，这样就可以求出相似度 $$ \frac{1}{l + 1} $$.

[网上其他人的分析](http://www.cnblogs.com/yujunyong/articles/2004724.html)