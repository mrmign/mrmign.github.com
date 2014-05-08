---
layout: post
title: "BNR:iOS programming 笔记"
categories: iOS
tags: iOS
---

* `@import module;` 直接导入系统模块，如`@import Foundation;`不需要在linked Frameworks and Library里添加。只能针对iOS系统中的模块。自己的还是需要用`#import ...`格式导入。
* 当property指向某个有可变子类(如NSString/NSMutableString, NSArray/NSMutableArray)的实例时，应该把它的内存管理属性设置为copy. 如 `@property (noatomic, copy) NSString *str;`。
* 如果用来创建Core Graphics对象所调用的方法里有create或copy字样，必须调用相应的Release方法。
* NSDictionary中作为key的对象必须实现`NSCopying`协议，从而可以通过copy方法进行复制。
* 在用Instruments检查内存泄漏时，如果在generations间的内存大小不能减为0，就说明有内存泄漏，Leaks工具针对一些内存泄漏情况检测不到。
* 需要存档或unarchive的类必须实现NSCoding协议，并实现`encodingWithCoder:`和`initWithCoder:`方法。
