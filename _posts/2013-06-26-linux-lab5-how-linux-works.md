---
layout: post
title: "Linux操作系统是如何工作的?"
description: ""
category: lab
tags: [course, linux, lab]
---
{% include JB/setup %}

## Linux启动

![linux boot.gif](/images/course/linux/linux boot.gif)

1. 机器上电后，加载BIOS里的设置，CPU执行BIOS里特定位置的程序CS:EIP=FFFF:0000H
2. 加载bootloader,找到文件系统的位置
3. 加载系统镜像，进行初始化操作，如初始化文件系统
4. 执行｀head.S｀及｀start_kernel()｀


* 现在的计算机都是冯·诺伊曼体系的，即存储程序计算机。当程序存入存储器后，计算机就可以自动的从一条指令转到执行另一条指令。计算机有条不紊的执行就是根据此存储程序原理进行的。
* 堆栈是程序执行的现场，每个函数的执行都要在堆栈上进行，函数的参数传递，函数的调用及EBP,ESP的切换都需要堆栈来完成。
* 中断机制。Linux系统的输入输出都需要中断机制来处理。内核要对连接到计算机上的所有硬件进行管理，而CPU与外设的速度差太多，就需要中断机制让外围设备需要的时候主动与内核发信号。

从以上三点可以看出Linux系统的正常运行任何一点都不可缺少。

当发生系统调用或是中断时系统从用户态切换到内核态，内核线程执行SAVW_ALL保存现场，进行相应的中断处理程序，完成处理后执行RESTORE_ALL恢复现场，返回用户态程序。

