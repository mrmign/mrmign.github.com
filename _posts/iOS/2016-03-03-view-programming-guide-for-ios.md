---
layout: post
title: "View Programming Guide for iOS"
category: "iOS"
tags: "[iOS]"
description: ""
---

重新学习View相关文档，记录学到的新知识。

## View and Window结构

## Windows

## Views

`convertPoint:fromView:`和`convertRect:fromView:`把其他view的坐标系的坐标转换为当前view的坐标系中的坐标。
`convertPoint:toView:`和`convertRect:toView:`把坐标从当前view的坐标系转换到指定view的坐标系。在以上4个方法中如果参照的view为`nil`，转换就在包含当前view的Window和当前view的坐标系间进行。

在处理View的Autoresizing时，父view的`autoresizesSubviews`属性决定了子view是否可以resize。只有当父view的属性为YES的时候，子view才可以resize。

## Animations

