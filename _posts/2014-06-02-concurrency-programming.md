---
layout: post
title: "concurrency programming"
categories: iOS
tags: 并发
---

## 并发实现

* 分布式计算
* 并行编程
* 多进程
* 多线程

## 并发挑战

* 同步操作
* 共享信息

## Objective-C中的并发编程 

### 1. 语言上的特点: `@synchronized`可以创建锁，`atomic`可以保证访问属性的原子操作。

{% highlight objc %}
@synchronized(uniquOjb)
{
    // critical section - code protected by the directive
}
{% endhighlight %}

`atomic`提供访问属性的原子操作，但不是线程安全的。如：

{% highlight objc %}
@interface Person : NSObject
@property NSString *firstName;
@property NSString *lastName;
@end
{% endhighlight %}

尽管firstName和lastName是原子操作，但是Person对象不是线程安全的，`@property Person *person`, person中的firstName和lastName可以单独修改，这个可以通过`@synchronized`指令或同步原语(synchronization primitive)实现。

### 2. 消息传递: NSObject类有几个方法可以给其他线程传递消息。

这些方法把消息排在目标线程的run loop上，可以同步或异步地执行。

* `performSelector:onThread:withObject:waitUntilDone:`
* `performSelector:onThread:withObject:waitUntilDone:modes:`
* `performSelectorOnMainThread:withObject:waitUntilDone:`
* `performSelectorOnMainThread:withObject:waitUntilDone:modes:`

当创建一个线程时，你可以配置它的运行环境，如栈大小，优先级。通过用下面的方法实现线程入口程序来配置线程上下文也很重要。

* autorelease pool。在入口程序开始创建，程序最后销毁。
* 异常处理。入口程序应该捕获任何可能发生的异常。
* run loop。为使线程处理请求动态进行，可以在入口程序创建run loop。

Demo:

{% highlight objc %}
@implementation ConcurrentProcessor
...
- (void)downloadTask
{
    @autorelease
    {
        NSURL *url = [NSURL URLWithString:@"http://www.baidu.com"];
        NSString *str = [NSString stiringWithContentsOfURL:url encoding:NSUTF8StringEncoding error:nil];
        NSLog(@"URL Contents:\n %@", str);
        self.isLoaded = YES;
    }
}
@end

//call demo
ConcurrentProcessor *processor = [ConcurrentProcessor new];
[processor performSelector:@selector(downloadTask) onThread:secondaryThread withObject:nil waitUntilDone:NO];

{% endhighlight %}

`waitUntilDone` 指定异步/同步操作，如果是NO，当前线程立即返回。

`performSelector:onThread:...`方法往往用来从secondary线程对象往main线程对象返回值(状态，结果等)。

### 3. 线程: 通过基础库提供的方法直接创建和管理线程。


### 4. 操作队列(Operation Queue): 基于消息传递机制。


### 5. Dispatch queue: 基于C的异步并发方法。


在此挖了各种坑。。。




