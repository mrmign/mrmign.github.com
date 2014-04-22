---
layout: post
title: "view controller间的关系"
categories: iOS
tags: iOS
---

## Parent-child relationships

Parent-child relationships are formed when using view controller containers.
Examples of view controller containers are 
**UINavigationController, UITabBarController, and UISplitViewController**。
如果它拥有viewControllers属性，就可以认为它是个viewController容器。
viewController容器是UIViewController的子类，因此都会有view属性，也就是有它自己
内置的界面，像UINavgationController有自己的导航条，还会把viewControllers里的某个
view添加到自己的view中。

从下面图中理解view controller家族：
![image](/images/ios/ios_bnr_17_5.png)

每一个UIViewController都有一个`parentViewController`属性，它指向家族中最近的view 
controller祖先。UIViewController访问祖先的方法有`navigationController`, `tabBarController`, `splitViewController`,在通过上面3种方法来访问祖先时，还是借助`parentViewController`来向上搜索
家谱图，直到找到正确类型的view Controller容器。如果没有找到正确类型的祖先，就返回nil。

## Presenting-presenter relationships

Any UIViewController can present another view controller modally.在presenter和presentee
间有两个内置的属性，`presentedViewController`和`presentingViewController`，也就是一个主动一个被动
的关系，看图![image](/images/ios/ios_bnr_17_6.png)

## Inter-family relationships

A presented view controller and its presenter are not in the same view controller family.
被显示的view controller有它自己的家族，它的家族有可能只是一个UIViewController，也有可能是有多个view controllers组成。

看下面的图，有两个家族。

![image](/images/ios/ios_bnr_17_7.png)

**注意：** 在parent-child关系中的那些关系属性不能越过家族。因此在家族2中给某个view controller发`tabBarController`消息，不会返回家族1中的UITabBarController，而是返回nil。同样的，在家族2中给某个view controller发`navigationController`返回家族2中的UINavigationController，而不是家族1中的。

或许，view controllers间的关系中最奇怪的是家族间的那种。

>**When a view controller is presented modally, the actual presenter is the oldest member of the presenting family.**

如在上面图中，UITabBarController是家族2中view controllers的presentingViewController。
家族1中不管哪个view controller调用了`presentViewController:animated:completion`，
presenter总是UITabBarController。

可以修改这种最老祖先行为(只在iPad有效)。通过此方法，你可以指定要显示的view controller家族的view在屏幕上的位置。为实现这个功能，每个UIViewController都有一个`definesPresentationContext`属性。默认该属性是NO，也就是说view controller会把它邻近的祖先传递出去，直到没有祖先。把该值设置YES，就打断了搜索最老祖先，允许view controller在它自己的view中展示modal view。同时，你必须设置
要展示的view controller的`modalPresentationStyle=UIModalPresentationCurrentContext`。

![image](/images/ios/ios_bnr_17_8.png)

如果没有修改definesPresentationContext, 最下面的view controller的presentedViewController会是UINavigationController，现在修改了该值，则是指向显示它的view controller。

本文总结自[iOS:BNR](http://book.douban.com/subject/24538384/)一书。