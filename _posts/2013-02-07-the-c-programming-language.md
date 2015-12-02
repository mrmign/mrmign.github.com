---
layout: post
title: "The C programming language"
category: learning 
tags: [c]
description: The code on the book, and the exercises.
---


###  P39

{% highlight c %}
/* 返回x 中从右边数第p位开始向右数n位的字段 */
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}
{% endhighlight %}

