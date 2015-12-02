---
layout: post
title: "iOS文档学习(1): NSObject"
categories: iOS
tags: iOS
---

* 不要重写`alloc`方法来包含初始化代码，实现init...方法。由于历史原因，`alloc`会调用`allocWithZone:`方法。alloc来初始化isa变量，指向描述该类的数据结构。
* <s>`allocWithZone:`</s>方法，该方法因为历史原因存在，Objective-C已经不再使用内存区。
* `+ (BOOL)conformsToProtocol:(Protocol *)aProtocol` 一个类如果采用某个协议或是从采用该协议的类继承，那么就说这个类遵从该协议。协议可以合并其他的协议`@protocol AffiliationRequests <Joining>`，如果一个采用合并其他协议的协议，也要实现被合并协议中的方法。至于方法有没有实现需要程序员自己去检查。`BOOL canJoin = [MyClass conformsToProtocol:@protocol(Joining)];`
* `+ (void)initialize`，在类收到第一条message之前执行。与`+ (void)load`方法关系密切。
* `+ (BOOL)resolveInstanceMethod:(SEL)name`，动态添加实例方法。
> An Objective-C method is simply a C function that take at least two arguments—self and _cmd. Using the class_addMethod function, you can add a function to a class as a method. Given the following function:

{% highlight objc %}
void dynamicMethodIMP(id self, SEL _cmd)
{
    // implementation ....
}
{% endhighlight %}

> you can use resolveInstanceMethod: to dynamically add it to a class as a method (called resolveThisMethodDynamically) like this:

{% highlight objc %}
+ (BOOL) resolveInstanceMethod:(SEL)aSEL
{
    if (aSEL == @selector(resolveThisMethodDynamically))
    {
          class_addMethod([self class], aSEL, (IMP) dynamicMethodIMP, "v@:");
          return YES;
    }
    return [super resolveInstanceMethod:aSel];
}
{% endhighlight %}

* `- (id)copy` NSObject本身不支持`NSCopying`协议，子类必须支持该协议并实现`copyWithZone:`方法。子类的`copyWithZone:`必须先调用父类的`copyWithZone:`合并父类的实现，除非子类直接继承自NSObject。
* `- (void)doesNotRecognizeSelector:(SEL)aSelector` 当一个对象收到一个不能响应也不能传递的aSlector消息时，运行时系统会触发该方法，该方法会产生`NSInvalidArgumentException`异常并生错误消息。该消息通常由运行时系统发出，但是也可以将方法用在代码中阻止方法被继承。例如 NSObject的子类可以通过包含`doesNotRecognizeSelector:`来重新实现copy和init以达到摒弃他们的效果。

{% highlight objc %}
- (id)copy
{
    [self doesNotRecognizeSelector:_cmd];
}
{% endhighlight %}

`_cmd`变量是传给每个当前选择器方法的隐藏变量。在上面 的例子中指的copy方法，这段代码阻止了子类实例响应copy消息，或父类传递copy消息，尽管` respondsToSelector:`会显示接收对象能访问copy方法。如果你重写了该方法，你必须在实现最后调用 super 或是产生`NSInvalidArgumentException`，也就是说这个方法一定不能正常返回，必须抛出异常。

