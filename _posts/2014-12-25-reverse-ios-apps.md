---
layout: post
title: "reverse iOS apps"
categories: iOS
tags: iOS, reverse
---


# 准备工作：

## 越狱 ##

网上自己找相关教程

## 安装逆向需要的工具 ##

[一些越狱软件](http://reverseengineeringapps.blogspot.de/2014/11/reverse-engineering-ios-mobile.html?m=1)

根据上面的链接安装了Rasticrac之后，运行的时候是 `rc.sh -m`, 我的机器是iOS 8.1，该脚本安装在`/usr/bin/`目录下，
与文章里说的不一样。下面在运行`rc.sh -m`会列出已经安装的app, 并且会给每个应用加个快选的菜单，这一点很人性啊。
这个软件破解成功率还是蛮高的，但是在尝试微信的时候出错了，所以还得需要其他的破解方式，下面解释另一种方式。

安装dumpdecrypt手动进行破解, [参考这里](http://bbs.iosre.com/forum.php?mod=viewthread&tid=7&extra=page%3D1)

## 其他一些方便的工具 ##

通过USB来SSH登录手机，这种方式比通过wifi要快。 [参考这里](http://bbs.iosre.com/forum.php?mod=viewthread&tid=185&highlight=usb)

有时候自己来写个脚本减少点体力活还是必须的，安装Python必须的，如何安装 [参考这里](http://www.reddit.com/r/jailbreak/comments/1yl39t/tutorial_how_to_install_python_2763_pip_on_ios/)

当然，可以写shell脚本，但是我不是很熟，python还是比较熟手的。也想用过Lua，但是Lua的系统支持不是很好，好处就是解释器那个小啊。


### CPU架构 ###

* iPhone4, 4S, iTouch 5 armv7
* iPhone5 armv7s
* iPhone5s, iPhone6 arm64



## 重新签名iOS二进制文件 ##

1. 进入到应用目录中如，/var/mobile/Containers/Bundle/Application/xxxx/xxx.app 
2. ldone xxx(应用名) -s, 使用ldone重新签名可执行文件
3. chmod 755  xxx
4. chown mobile.mobile xxx


