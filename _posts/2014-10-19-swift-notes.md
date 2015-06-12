---
layout: post
title: "swift notes"
categories: iOS
tags: swift
---

## Strings and Character

> A Unicode scalar is any Unicode code point in the range U+0000 to U+D7FF inclusive or U+E000 to U+10FFFF inclusive. Unicode scalars do not include the Unicode surrogate pair code points in the range U+D800 to U+DFFF inclusive.

An arbitrary Unicode scalar, written as \u{n}, where n is between one and eight hexadecimal digits

the length property from NSString is called utf16Count when it is accessed on a Swift String value
 
* 单字节 \xnn
* 双字节 \unnnn
* 四字节 \Unnnnnnnn

> 值类型的在传递给函数，方法，赋值时都进行拷贝。


if let old = dict.updateValue("aaa", forKey: "aaa") {
    println("not nil")
}
else {
    println("nil")
}

这里updateValue返回optional value，这里为什么可以在if中直接声明常量？条件判断里应该只允许使用Bool值？
