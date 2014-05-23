---
layout: post
title: "Objective C Runtime"
categories: iOS
tags: runtime
---

> Pro Objective-C Chapter 7: Runtime System

用`NSSelectorFromString`函数在运行时创建selector. 如`SEL sel = NSSeletorFromString(@"method::")`, 这里在一个selctor中可以有空的segment,名字可以不要，但是调用时参数必须提供如`- (int)sumAdd:(NSInteger)a :(NSInteger)b;`,调用要`[cal sumAdd:a :b]`这样子。

在方法中可以通过`NSStringFromSelector(_cmd)` 打印当前的方法名。

{% highlight objc %}
SEL selector1 = @selector(sumAddend1:addend2:);
id sum1 = [cal performSelector:selector1 withObject:addend1 withObject:addend2];
NSLog(@"Sum of %@ + %@ = %@", addend1, addend2, sum1);
SEL selector2 = NSSelectorFromString(@"sumAddend1::");
id sum2 = [cal performSelector:selector2 withObject:addend1 withObject:addend3];
NSLog(@"Sum of %@ + %@ = %@", addend1, addend3, sum2);

SEL selector3 = NSSelectorFromString(@"absoluteValue:");
NSLog(@"Invoking instance method %@ on object of class %@",
      NSStringFromSelector(selector3), [cal class]);
id sum3 = [cal performSelector:selector3 withObject:sum2];
NSLog(@"Absolute value of %@ = %@", sum2, sum3);
{% endhighlight %}

当编译上面的代码时会有`PerformSelector may cause a leak because its selector is unknown`警告，因为如果没有方法与selector匹配就会抛出异常，可能会导致内存泄露。可以通过以下方法去除警告。

{% highlight objc %}
#pragma clang diagnostic push 
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
        SEL selector1 = @selector(sumAddend1:addend2:);
        id sum1 = [cal performSelector:selector1 withObject:addend1 withObject:addend2];
        NSLog(@"Sum of %@ + %@ = %@", addend1, addend2, sum1);
        SEL selector2 = NSSelectorFromString(@"sumAddend1::");
        id sum2 = [cal performSelector:selector2 withObject:addend1 withObject:addend3];
        NSLog(@"Sum of %@ + %@ = %@", addend1, addend3, sum2);
        
        SEL selector3 = NSSelectorFromString(@"absoluteValue:");
        NSLog(@"Invoking instance method %@ on object of class %@",
              NSStringFromSelector(selector3), [cal class]);
        id sum3 = [cal performSelector:selector3 withObject:sum2];
        NSLog(@"Absolute value of %@ = %@", sum2, sum3);
#pragma clang diagnostic pop
{% endhighlight %}

### 说明

1. 诊断的名字要在双引号中指定。在这个例子中，-Warc-performSelector-leaks 关闭了针对执行performSelector可能导致内存泄露的编译警告。
2. pragma clang diagnostic push 和 pragma clang diagnostic pop用来保存和恢复当前编译诊断的设置。这保证了编译器在编译其他的源文件时继续使用通常的编译选项。

## 动态类型

{% highlight objc%}
- (NSInteger)computeValue:(NSNumber<NSDecimalNumberBehaviors> *)parameter;
{% endhighlight %}

### 动态提供方法实现

{% highlight objc %}
#import <objc/runtime.h>
+ (BOOL)resolveInstanceMethod:(SEL)sel
{
    NSString *method = NSStringFromSelector(sel);
    if ([method hasPrefix:@"absoluteValue"]) {
        class_addMethod([self class], sel, (IMP)absoluteValue, "@@:@");
        NSLog(@"Dynamically added instance method %@ to class %@", method, [self class]);
        return YES;
    }
    return [super resolveInstanceMethod:sel];
}

id absoluteValue(id self, SEL _cmd, id value)
{
    NSInteger intValue = [value intValue];
    if (intValue < 0) {
        return [NSNumber numberWithInteger:(intValue * -1)];
    }
    return value;
}
{% endhighlight %}

动态添加方法可以有实例方法与类方法，resolveInstanceMethod 和 resolveClassMethod, 这里讲了添加实例方法。

> Pro Objective-C Chapter 8: Runtime Architecture

## Runtime Component

下面是一些常用的数据结构：

{% highlight objc %}
typedef struct objc_class *Class

struct objc_object
{
    Class isa;
    /* ... variable length data containing instance varibale values ... */
};

typedef struct objc_object *id;
{% endhighlight %}

下面的是一个关于上面结构的例子:

{% highlight objc %}
#import <objc/runtime.h>
@interface  TestClass1 : NSObject
{
@public int myInt;
}
@end
@implementation TestClass1
@end

int main(int argc, const char *argv[])
{
    @autoreleasepool {
        TestClass1 *tc1A = [[TestClass1 alloc] init];
        tc1A->myInt = 0x5a5a5a5;
        TestClass1 *tc1B = [[TestClass1 alloc] init];
        tc1B->myInt = 0x3c3c3c3;
        long tc1Size = class_getInstanceSize([TestClass1 class]);
        NSData *obj1Data = [NSData dataWithBytes:(__bridge const void *)(tc1A) length:tc1Size];
        NSData *obj2Data = [NSData dataWithBytes:(__bridge const void *)(tc1B) length:tc1Size];
        NSLog(@"TestClass1 object tc1 contains %@", obj1Data);
        NSLog(@"TestClass1 object tc2 contains %@", obj2Data);
        NSLog(@"Testclass1 memory address = %p", [TestClass1 class]);
        
        id testCl = objc_getClass("TestClass1");
        long tcSize = class_getInstanceSize([testCl class]);
        NSData *tcData = [NSData dataWithBytes:(__bridge const void *)(testCl) length:tcSize];
        NSLog(@"TestClass1 class contains %@", tcData);
        NSLog(@"TestClass1 superclass memory address = %p", [TestClass1 superclass]);
        NSLog(@"%p", [testCl class]);
        NSLog(@"%p", testCl);

        id metaClass = objc_getMetaClass("TestClass1");
        long s = class_getInstanceSize([metaClass class]);
        NSData *mc = [NSData dataWithBytes:(__bridge const void *)(metaClass) length:s];
        NSLog(@"TestClass1 metaclass contains %@", mc);
        class_isMetaClass(metaClass) ?
        NSLog(@"Class %s is a metaclass", class_getName(metaClass)):
        NSLog(@"Class %s is not a metaclass",class_getName(metaClass));
        
    }
    return 0;
}
{% endhighlight %}

输出结果：
{% highlight console %}
2014-05-23 22:56:58.085 Runtime[2759:303] TestClass1 object tc1 contains <10230000 01000000 a5a5a505 00000000>
2014-05-23 22:56:58.087 Runtime[2759:303] TestClass1 object tc2 contains <10230000 01000000 c3c3c303 00000000>
2014-05-23 22:56:58.087 Runtime[2759:303] Testclass1 memory address = 0x100002310
2014-05-23 22:56:58.087 Runtime[2759:303] TestClass1 class contains <e8220000 01000000 10c82072 ff7f0000>
2014-05-23 22:56:58.088 Runtime[2759:303] TestClass1 superclass memory address = 0x7fff7220c810
2014-05-23 22:56:58.088 Runtime[2759:303] 0x100002310
2014-05-23 22:56:58.088 Runtime[2759:303] 0x100002310
2014-05-23 22:56:58.089 Runtime[2759:303] TestClass1 metaclass contains <38c82072 ff7f0000 38c82072 ff7f0000 105f2000 01000000 07000000 03000000 801d2000 01000000>
2014-05-23 22:56:58.089 Runtime[2759:303] Class TestClass1 is a metaclass
{% endhighlight %}

因为Mac用的是小端，所以输出的地址与内容正好相反。

这里的testCl的内容为什么与前面的tc1A不同的，是因为testCl是通过objc_getClass返回一个对象的类，所以它的地址指向这个类，与前面的实例的isa所指向的地址是相同的。

metaclass是一种特殊的类对象，它存储了能够使运行时查找和触发OC类的类方法的信息。

isa 分两种：一种指描述实例的类，可以访问它的实例方法，变量等。另一种指向描述类的metaclass，访问类方法。

## Runtime Library

### runtime library data types

1. Class definition data structures(class, method, ivar, category, IMP, SEL,etc)
2. Instance data types(id, objc_object, objc_super)
3. Values (BOOL)

### functions 分类

1. Object messaging
2. Class functions
3. Instance functions
4. Protocol functions
5. Property functions
6. Selector functions

下面的图是运行时的消息操作

![runtime message](/images/ios/2014-05-22-runtime-message.svg)

方法查找是通过`vtable`,也就是分发表，在支持动态绑定的语言中常用的一种机制。一个vtable是一组IMPs,也就是OC中的方法实现。每一个运行时类实例(objc_class)有一个指向vtable的指针。

{% highlight objc %}
struct objc_method
{
    SEL method_name;
    char *method_types;//指明参数数据类型
    IMP method_imp; //函数地址
};

typedef objc_method *Method;
{% endhighlight %}

![runtime library](/images/ios/2014-05-22-runtime-library.svg)


