---
layout: post
title: "Motion Design for iOS(part 4)"
category: "iOS"
tags: "iOS animation"
description: ""
---

# Motion Design for iOS(part 4)

### Pop animation Framework

在Core Animation中一旦动画结束，presentation layer就被移除，如果不想让层突然回到起始位置，需要设置model layer的属性与动画的最后状态相符(UIView的动画方法不用，它自动帮设置了最终的属性值)。像JNWSpringAnimation这种动画，依然使用了CA中的对象`CAKeyframeAnimation`，我们需要设置Model layer的最终值。

Pop完全不同。Pop不用CA来执行它所提供的动画功能。它所做的是建立一个定时器对象每1/60秒就执行一次，定时器一秒执行60次的代码会直接更新你定义的弹性动画中的下一位置所依赖的所有属性。没有特殊的，额外的层添加到你的元素上，Pop直接修改UIView或CAlayer上的属性，甚至是其他任意你想要的类型。也就是说，你可以在动画过程中直接获得正在改变的属性的当前值，而不需要通过Presentation Layer.更棒的是，你不需要单独设置最终的值来保持状态，因为动画一直在修改真正的值。

Pop所使用的定时器对象是`CADisplayLink`，是`NSTimer`更高级的版本，`CADisplayLink`不设置时间间隔来调用代码，它调用方法的速度完全取决于屏幕的刷新速率。
