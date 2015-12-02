---
layout: post
title: "Motion Design for iOS(part 2)"
category: "iOS"
tags: "iOS animation"
description: ""
---

# Motion Design for iOS(part 2)

### 动画属性

#### 最基本的三个属性

1. Position
2. Opacity
3. Scale

#### 其他的属性

1. Color
2. Rotation
3. 3D 用3D来变换一个对象就是控制它的第三维，也就是说动画中的3D变换要么是进入屏幕，要么是朝向用户

对于每个要进行动画的对象，在开始写代码前要考虑以下问题：

1. 对象最初的属性是什么？如是否在屏幕下方？是不是完全透明？是不是size非常小?
2. 对象的最后属性是什么？是不是在屏幕中间？对用户是不是可见？是否旋转了特定角度？是否有不同的背景色？
3. 动画要执行多长时间？
4. 执行动画期间会发生什么？
5. 一旦该对象完成了动画会发生什么？

### 动画的时间

![easing](/images/20150804/easing.png)￼

横坐标表示时间，纵坐标表示动画改变的属性

上面图中所列出的四种动画曲线是Core Animation默认支持的.

Core Animation提供的简易曲线数学上定义为贝塞尔曲线。

