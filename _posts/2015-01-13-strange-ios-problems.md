---
layout: post
title: "strange iOS problems"
categories: iOS
tags: iOS
---

1. 当为view添加UIGestureRecognizer后，如果view的frame重新设置了，添加过的手势识别会清除掉，
可以通过view的gestureRecognizers(这是一个数组，存放各种手势)的大小来判断。

2. property follows cocoa naming convention for returning owned objects 

 问题的原因是因为声明的变量格式不对，`@property (nonatomic, strong) Phrase *newPhrase;`变量以new开头，Xcode/ARC不会自动生成getter/setter方法。避免类似的问题，在声明属性时不要以下面的开头：

* new
* alloc
* copy
* mutableCopy


