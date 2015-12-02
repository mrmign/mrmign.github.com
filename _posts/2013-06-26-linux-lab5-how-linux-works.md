---
layout: post
title: "Linux操作系统是如何工作的?"
description: ""
category: lab
tags: [course, linux, lab]
---

## Linux启动

![linux boot.gif](/images/course/linux/linux boot.gif)

1. 机器上电后，加载BIOS里的设置，CPU执行BIOS里特定位置的程序CS:EIP=FFFF:0000H
2. 加载bootloader,找到文件系统的位置
3. 加载系统镜像，进行初始化操作，如初始化文件系统
4. 执行`head.S`及`start_kernel()`


* 现在的计算机都是冯·诺伊曼体系的，即存储程序计算机。当程序存入存储器后，计算机就可以自动的从一条指令转到执行另一条指令。计算机有条不紊的执行就是根据此存储程序原理进行的。
* 堆栈是程序执行的现场，每个函数的执行都要在堆栈上进行，函数的参数传递，函数的调用及EBP,ESP的切换都需要堆栈来完成。
* 中断机制。Linux系统的输入输出都需要中断机制来处理。内核要对连接到计算机上的所有硬件进行管理，而CPU与外设的速度差太多，就需要中断机制让外围设备需要的时候主动与内核发信号。

从以上三点可以看出Linux系统的正常运行任何一点都不可缺少。

##　中断机制
![shedule.jpg](/images/course/linux/shedule.jpg)

当进程X接收到中断信号时，CPU把当前进程的用户信息eip,esp等保存到进程x的内核堆栈中，并把esp指向内核堆栈的栈顶，eip指向中断处理程序入口，从用户态转向内核态，SAVE_ALL保存现场，
进行中断处理，如果需要进行进程切换，调用schedule()函数选择下一个进程Y进行切换，中断处理结束后，RESTORE_ALL恢复现场，返回到用户态，eip指向进程Y的下一条指令，继续执行。

进行进程的切换要用到switch_to函数，下图为switch_to函数的定义
![switch_to.jpg](/images/course/linux/switch_to.jpg)

switch_to完成的工作有：

1. 在eax和edx寄存器中分别保存prev和next的值
2. 把eflags和ebp寄存器的内容保存在prev内核栈中
3. 把esp的内容保存到prev->thread.esp中，以使该字段指向prev内核栈的栈顶
4. 把next->thread.esp装入esp。此时内核开始在next的内核栈上操作，实际上完成了从prev到next的切换。由于进程描述符的地址和内核的地址紧挨着，所以改变内核栈意味着改变当前进程。
5. 把标记为１的地址存入prev->thread.eip。当被替换的进程重新恢复执行时，进程执行被标记为１的那条指令。
6. 宏把next->thread.eip的值压入next的内核栈。
7. 跳到__switch_to()Ｃ函数。
8. 被进程Ｂ替换的进程Ａ再次获得cpu,它执行一些保存eflags和ebp寄存器内容的指令，这两条指令的第一条指令被标记为１
9. 拷贝eax寄存器的内容到switch_to宏的第三个参数last标记的内存区域中。


