---
layout: post
title: "编程之美－3.8　求二叉树中结点的最大距离"
description: "关于编程之美中的问题。"
category: algorithm
tags: [algorithm]
---
{% include JB/setup %}

> **题目：**　写一个程序求一棵二叉树中相距最远的两个结点之间的距离。这里的“距离”指两个结点之间的边的个数。

思路：计算每个节点的左子树和右子树的高度和，取最大值 。

书中代码实现(递归方法)：

{% highlight c %}
01        // 数据结构定义
02        struct NODE
03        {
04            NODE* pLeft;        // 左子树
05            NODE* pRight;      // 右子树
06            int nMaxLeft;      // 左子树中的最长距离
07            int nMaxRight;      // 右子树中的最长距离
08            char chValue;      // 该节点的值
09        };
10        
11        int nMaxLen = 0;
12        
13        // 寻找树中最长的两段距离
14        void FindMaxLen(NODE* pRoot)
15        {
16            // 遍历到叶子节点，返回
17            if(pRoot == NULL)
18            {
19                return;
20            }
21        
22            // 如果左子树为空，那么该节点的左边最长距离为0
23            if(pRoot -> pLeft == NULL)
24            {
25                pRoot -> nMaxLeft = 0;
26            }
27        
28            // 如果右子树为空，那么该节点的右边最长距离为0
29            if(pRoot -> pRight == NULL)
30            {
31                pRoot -> nMaxRight = 0;
32            }
33        
34            // 如果左子树不为空，递归寻找左子树最长距离
35            if(pRoot -> pLeft != NULL)
36            {
37                FindMaxLen(pRoot -> pLeft);
38            }
39        
40            // 如果右子树不为空，递归寻找右子树最长距离
41            if(pRoot -> pRight != NULL)
42            {
43                FindMaxLen(pRoot -> pRight);
44            }
45        
46            // 计算左子树最长节点距离
47            if(pRoot -> pLeft != NULL)
48            {
49                int nTempMax = 0;
50                if(pRoot -> pLeft -> nMaxLeft > pRoot -> pLeft -> nMaxRight)
51                {
52                    nTempMax = pRoot -> pLeft -> nMaxLeft;
53                }
54                else
55                {
56                    nTempMax = pRoot -> pLeft -> nMaxRight;
57                }
58                pRoot -> nMaxLeft = nTempMax + 1;
59            }
60        
61            // 计算右子树最长节点距离
62            if(pRoot -> pRight != NULL)
63            {
64                int nTempMax = 0;
65                if(pRoot -> pRight -> nMaxLeft > pRoot -> pRight -> nMaxRight)
66                {
67                    nTempMax = pRoot -> pRight -> nMaxLeft;
68                }
69                else
70                {
71                    nTempMax = pRoot -> pRight -> nMaxRight;
72                }
73                pRoot -> nMaxRight = nTempMax + 1;
74            }
75        
76            // 更新最长距离
77            if(pRoot -> nMaxLeft + pRoot -> nMaxRight > nMaxLen)
78            {
79                nMaxLen = pRoot -> nMaxLeft + pRoot -> nMaxRight;
80            }
81        }

{% endhighlight %}

[非递归实现方法](http://wangyun854150.blog.163.com/blog/static/8076261020098411293064/)

>如果题目是给出二叉树的两个结点，求这两个结点的距离？


类似题目：[二叉树两结点的最低共同父结点](http://zhedahht.blog.163.com/blog/static/25411174201081263815813/)

