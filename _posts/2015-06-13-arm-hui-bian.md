---
layout: post
title: "ARM汇编"
category: ""
tags: "arm 汇编"
description: ""
---

# ARM汇编

## 特殊用途的寄存器

* R0-R3  传递参数与返回值
* R7 帧指针，指向母函数与被调用子函数在栈中的交界
* R9 iOS3以前系统保留
* R12 内部过程调用寄存器，dynamic linker会用到
* R13 SP寄存器
* R14 LR寄存器，保存函数返回地址
* R15 PC寄存器