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
{% highlight cpp %}
void FindPath
(
    BinaryTreeNode*   pRoot,        
    int               expectedSum,  
    std::vector<int>& path,         
    int&              currentSum
)
{
    currentSum += pRoot->m_nValue;
    /*
    在此判断currentSum是否大于输入的值，如果大于，就直接跳回父结点
    if(currentSum > expectedSum)
        return;
    
    */
    path.push_back(pRoot->m_nValue);

    // 如果是叶结点，　并且路径上结点的和等于输入的值
    // 打印出这条路径
    bool isLeaf = pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL;
    if(currentSum == expectedSum && isLeaf)
    {
        printf("A path is found: ");
        std::vector<int>::iterator iter = path.begin();
        for(; iter != path.end(); ++ iter)
            printf("%d\t", *iter);
        
        printf("\n");
    }

    // 如果不是叶结点，则遍历它的子结点
    if(pRoot->m_pLeft != NULL)
        FindPath(pRoot->m_pLeft, expectedSum, path, currentSum);
    if(pRoot->m_pRight != NULL)
        FindPath(pRoot->m_pRight, expectedSum, path, currentSum);

    // 在返回到父结点之前，在路径上删除当前结点，
    // 并在currentSum中减去当前结点的值
    currentSum -= pRoot->m_nValue;
    path.pop_back();
}
{% endhighlight %}