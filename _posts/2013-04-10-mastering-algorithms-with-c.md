---
layout: post
title: "mastering algorithms with c"
description: "Notes about  mastering algorithms with c"
category: Reading
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

## Chapter 12 Sort & Search
+ 插入排序 最佳应用场景是对一个小的数据集合进行递增排序
+ 快速排序 最佳应用场景是大数据集
+ 归并排序 最佳应用场景是**超大数据集** ???
+ 计数排序 稳定的线性时间排序算法，需要知道数据集中整数的最大值，主要用来实现基数排序
+ 基数排序 逐位对元素进行排序的线性时间排序算法，适用于固定大小的元素集
+ 其他排序：冒泡排序，选择排序，堆排序，**内省排序**(一种类似快速排序的排序算法，只是在检测时它会切换到堆排序，从而提高排序效率，由于这点改进，在某些情况下比快速排序效率略高)， 桶排序
+ 二分查找

应用：

* 次序统计，寻找集合中第i小的元素
* 二分搜索
* 目录列表
* 数据库系统
* 拼写检查器
* 电子表格


1 在快速排序中，用median-of-three method 找用来分割的值。
{% highlight c %}
int partition(void *data, int esize, int i, int k, int (*compare)(const void *key1, const void *key2))
{
	....
	r[0] = (rand() % (k - i + 1)) + 1;
	r[1] = (rand() % (k - i + 1)) + 1;
	r[2] = (rand() % (k - i + 1)) + 1;
	/* 对r进行排序，取r[1]作为分割的值*/
	....
}
{% endhighlight %}
2 计数排序
要知道数据集中最大的元素值，设为K, 申请K大的数组count[K]，遍历数组统计每个元素出现的次数，对count中的每个加上前一个元素出现的次数，再遍历数据中的元素，放到临时数组temp的相应位置上，遍历结束后，把值复制到原来的数据集中。该算法需要额外的空间，统计数组count需要至少K个空间，临时数组需要n个空间。**可以通过遍历统计数组count找到第i小的元素。**
3 基数排序 对每个p位置的数值使用计数排序，如对123，p＝0,1,2，分别对0位，1位，2位上的数字进行排序。
{% highlight c %}
int rxsort(int *data, int size, int p, int k)
{
	...
	for(n = 0; n < p; n++)
	{
		.....
		pval = (int)pow((double)k,(double)n);
		for(j = 0; j < size; j++)
		{
			/* 为什么计算index的这样做？ */
			index = (int)（data[j] / pval) % k;
			count[index] = count[index] + 1;
		}
		...
	}
	...
}
{% endhighlight %}


