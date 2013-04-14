---
layout: post
title: "剑指offer面试题"
description: ""
category: interview
tags: [interview, algorithm]
---
{% include JB/setup %}

## 第25题
>题目:输入一棵二叉树和一个整数，打印出二叉树中结点值的和为
输入整数的所有路径。从树的根结点开始往下一直到叶结点所经过
的结点形成一条路径。二叉树结点定义如下：
{% highlight cpp %}    
struct BinaryTreeNode
{
    int               m_nValue;
    BinaryTreeNode *  m_pLeft;
    BinaryTreeNode *  m_pRigth;
}
{% endhighlight %}

题目中的解法还可以进一步优化，即在查找路径上的和是否与输入的整数相等时，如果还没有到叶结点，而此时路径上的和已经超过输入的整数，就可以直接返回上一结点，不用再判断后续的子结点了。