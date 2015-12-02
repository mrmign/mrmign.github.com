---
layout: post
title: "iOS单例实现方式"
categories: iOS
tags: iOS, pattern
---

单例模式常用在工具类中，现在探讨几种实现方式：

下面的实现方式都是线程安全的：
{% highlight objc %}
+ (instancetype)shared
{
    static SharedObject *_sharedObject = nil;
    static dispatch_once_t once;
    dispatch_once(&once, ^{
        _sharedObject = [[SharedObject alloc] init];
    });
    return _sharedObject;
}
{% endhighlight %}


{% highlight objc %}
+ (instancetype)shared
{
    static SharedObject *_sharedObject = nil;
    @synchronized(self)
    {
        if(_sharedObject == nil){
            _sharedObject = [[SharedObject alloc] init];
        }
    }
    return _sharedObject;
}
{% endhighlight %}

下面的是非线程安全的。很多人都会这样子写。
{% highlight objc %}
+ (instancetype)shared
{
    static SharedObject *_sharedObject = nil;
    if(_sharedObject == nil){
        _sharedObject = [[SharedObject alloc] init];
    }
    return _sharedObject;
}

{% endhighlight %}
