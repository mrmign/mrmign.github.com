---
layout: post
title: "object c questions"
description: "This is records for wrong questions about OC on wenda60.com"
category: programming
tags: [object-c]
---
{% include JB/setup %}

1. 关于固化(archive)和解固(unarchive)的理解。
	+ 所有的对象都支持固化
	+ 固化和解固可以保存并还原整个对象图
	+ XIB文件是通过固化/解固机制实现的
	+ 固化和解固可以更新数据的局部变化，不用重新保存整个文件(错误)
2. objective-c 不支持多继承
3. 关于范畴(Catagory)
	+ 在范畴中覆盖父类的方法后，就没有办法调用父类的实现
	+ 范畴可以作用在任何已存的类上
	+ 范畴可以为类增加新的实例变量(不对??)
4. 指针变量可以由整数赋，不能用浮点赋(错误,意思说可以用浮点给指针变量赋值？？)

