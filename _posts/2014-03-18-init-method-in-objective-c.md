---
layout: post
title: "init method in Objective C"
categories: ios
tags: iOS
---

很基本的初始化方法：

{% highlight objc %}
- (instancetype)init
{
    self = [super init];
    if (self) {
        //初始化工作
    }
    return self;
}
{% endhighlight %}

初始化方法应该总是返回`instancetype`.在Xcode4.3之前，初始化方法都是返回`id`，
相比较而言，instancetype更好，可以让编译器检查返回类型。

该init方法开始有两个检查：

1. 第一行`self`赋值为父类的init方法返回的对象
2. 检查父类初始化方法返回的对象是有效的，而不是nil

为什么要做这些检查？许多类有异常的`ini`方法，有两种可能的异常方式：

1. init方法有智能优化，它可以先回收原来的对象，再分配一个不同的对象，并返回这个新对象。为处理
   这种情况，Apple要求要把self指向父类初始化方法返回的对象。
2. init方法失败，回收了该对象，返回nil。为应对这种情况，Apple建议检查父类初始化方法返回的是有效对象，而不是nil。

{% highlight objc %}
#import <Foundation/Foundation.h>

@interface BNRAppliance : NSObject
@property (nonatomic, copy) NSString *productName;
@property (nonatomic) int voltage;

- (instancetype)initWithProductName:(NSString *)pn;
@end

#import "BNRAppliance.h"

@implementation BNRAppliance
- (instancetype)init
{
//    self = [super init];
//    if (self) {
//        _voltage = 120;
//    }
//    return self;
    return [self initWithProductName:@"Unknow"];
}

- (instancetype)initWithProductName:(NSString *)pn
{
    self = [super init];
    if (self) {
        _productName = [pn copy];
        _voltage = 120;
    }
    return self;
}
- (NSString *)description
{
    return [NSString stringWithFormat:@"<%@: %d volts>", self.productName, self.voltage];
}
@end

//////BNROwnedAppliance

#import "BNRAppliance.h"

@interface BNROwnedAppliance : BNRAppliance
@property (readonly) NSSet *ownedNames;

- (instancetype)initWithProductName:(NSString *)pn firstOwnerName:(NSString *)n;
- (void)addOwnerName:(NSString *)n;
- (void)removeOwnerName:(NSString *)n;
@end

#import "BNROwnedAppliance.h"

@interface BNROwnedAppliance(){
    NSMutableSet *_ownerNames;
}

@end
@implementation BNROwnedAppliance

// designated initializer
- (instancetype)initWithProductName:(NSString *)pn firstOwnerName:(NSString *)n
{
    if (self = [super initWithProductName:pn]) { 
        _ownerNames = [[NSMutableSet alloc] init];
        
        if (n) {
            [_ownerNames addObject:n];
        }
    }
    return  self;
}

- (instancetype)initWithProductName:(NSString *)pn
{
    return  [self initWithProductName:pn firstOwnerName:nil];
}
- (void)addOwnerName:(NSString *)n
{
    [_ownerNames addObject:n];
}

- (void)removeOwnerName:(NSString *)n
{
    [_ownerNames removeObject:n];
}

- (NSSet *)ownedNames
{
    return [_ownerNames copy];
}
@end
{% endhighlight %}

![image](/images/ios/20140318_init_frame.png)

`BNROwnedAppliance *a = [[BNROwnedAppliance alloc] init]`运行正常，虽然在BNROwnedAppliance中没有实现init方法，但是在BNRAppliance有定义，将会调用`[self initWithProductName:@"Unknow"]`，self是BNROwnedAppliance的实例，因此会调用BNROwnedAppliance中的initWithProductName方法，进而调用[self initWithProductName:pn firstOwnerName:nil]方法。

每个类有且仅有一个designated initializer，如果有其他的初始化方法，必须要调用指定的初始化方法。

## Multiple initializers

![image](/images/ios/20140318_multiple_init.png)

#### The Designated Initializer

The initializer of a class that takes the full complement of initialization parameters is usually the designated initializer. The designated initializer of a subclass must invoke the designated initializer of its superclass by sending a message to super. 