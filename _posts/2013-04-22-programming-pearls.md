---
layout: post
title: "programming pearls"
description: ""
category: algorithm
tags: [algorithm]
---

## 1.2位逻辑运算实现位向量
>输入的是一个文件，至多包含n个正整数,每个正整数都要小于n，这里n=10^7.
每个正整数都不一样。大概只有1MB的可用内存。

在第一题中假设没有内存的限制，可以用`qsort`进行排序或是用C++模板库的`set`容器来完成。
在这里有内存的限制，考虑用位图来实现。

书上的实现：
{% highlight c %}
#include <stdio.h>
#define BITPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define N 10000000
int a[1+N/BITPERWORD];//一个int可以标志32个数

//设置数组第i位为1
void set(int i)
{
        a[i>>SHIFT] |= (1<<(i&MASK));
}

//清空数组第i位为0
void clr(int i)
{
        a[i>>SHIFT] &= ~ (1<<(i&MASK));
}
//查询数组第i位数字
void test(int i)
{ 
     return a[i>>SHIFT] &(1<<(i&MASK));
}
int main()
{
	int in;
	int i;
	for(i = 0; i< N; i++)
		clr(i);
	while(scanf("%d", &in) && in != -1)
		set(in);
	for(i = 0; i< N; i++)
		if(test(i))
			printf("%d\n",i);
	return 0;
}
{% endhighlight %}

`i>>SHIFT`　相当于i/32，计算出i在数组的哪一行中。`i&MASK`相当于`i%32`计算出i在行中的第几列。在i的二进制表示中，第６位之后的都会是32的倍数，会根据i>>SHIFT计算出行数，对于列数只需要计算前５位即可。

## 2.6.3 向量旋转算法（数组元素向左旋转若干位置）
* 方法１：每次向左旋转一个，多次旋转。效率低。
* 方法２：块交换法。将数组前i个元素复制到临时数组中，将余下的n-i个元素向左移动i个位置，再将临时数组中的i个元素复制到原数组后面。存储空间的消耗。
* 方法３："杂技"算法。**很巧妙！！！**
![杂技算法](/images/programmingpearl/2-6-3.png)
算法实现：
{% highlight c %}
/将str数组中的元素向左移动rotdist个位置
void forward(char* str, int n, int rotdist)
{
	int i = 0;
	//数组个数n与要移动的位数rotdist的最大公约数是外层循环的个数
	for(i = 0; i < gcd(n, rotdist); i++)
	{
		int temp = str[0];
		int j = i;
		while(1)
		{
			int k = j + rotdist;
			if(k >= n)
			{
				k = k - n;
			}
			if(k == i)
			{
				break;
			}
			str[j] = str[k];
			j = k;
		}	
		str[j] = temp;
	}
}
 
//求两个数的最大公约数
int gcd(int i, int j)
{
	while(i != j)
	{
		if(i > j)
		{
			i = i - j;
		}
		else
		{
			j = j - i;
		}
	}
	return i;
}
{% endhighlight %}

* 方法４：镜像翻转。[code](/mycode/propearl/2_mirror_array.c)
{% highlight c%}
reverse(0, i-1);
reverse(i, n-1);
reverse(0, n-1);
{% endhighlight %}