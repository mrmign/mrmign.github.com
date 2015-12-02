---
layout: post
title: "KVO Programming基础"
category: "iOS"
tags: "iOS kvo"
description: ""
---

# Key-Value Observing Programming

## 一个属性观察者的设置步骤：

1. 首先要想想有没有场景使用KVO比较好，如一个对象的某个特定属性修改了需要通知另一个对象时。如当BankObject中的`accountBalance`修改了就要通知PersonObject。
![](/images/20150723/14376628801388.jpg)￼
2. PersonObject必须通过`addObserver:forKeyPath:options:context:` 注册为BankObject的accountBalance的观察者。`addObserver:forKeyPath:options:context:`在这两个实例对象之间建立一个关联，该关联不是在这两个类之间，而是这两个特定的实例对象间。
![](/images/20150723/14376633250086.jpg)￼
3. 为了响应值改变时的通知，观察者必须实现`observeValueForKeyPath:ofObject:change:context: `方法，，这个方法实现定义了观察者如何响应通知。![](/images/20150723/14376636509368.jpg)￼
4. 当被观察的属性或是所依赖的一个key发生改变时，`observeValueForKeyPath:ofObject:change:context:`方法会自动触发。

## 注册KVO

### 要符合下面三条：

1. 你想观察的属性所属的类必须符合KVC规范
2. 必须通过`addObserver:forKeyPath:options:context:`方法给观察者注册被观察者
3. 观察者必须实现`observeValueForKeyPath:ofObject:change:context:`

#### 注册观察者

`addObserver:forKeyPath:options:context:`的options参数指定传递给观察者的值类型，有`NSKeyValueObservingOptionOld`和`NSKeyValueObservingOptionNew`两种，可以两个都传用or操作。该方法对观察者，被观察者，及contex没有强引用，需要自己管理好。

#### 接收变化通知

根据change字典的`NSKeyValueChangeKindKey`判断是哪种改变类型，有`NSKeyValueChangeSetting`，`NSKeyValueChangeInsertion`, `NSKeyValueChangeRemoval`, or `NSKeyValueChangeReplacement`。
#### 移除观察者

`[observedObject removeObserver:inspector forKeyPath:@"openingBalance"];`，如果context是一个对象，在移除观察者前一定要保持强引用。
