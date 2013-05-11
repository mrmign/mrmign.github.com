---
layout: post
title: "useful linux commands"
description: ""
category: linux
tags: [linux, 输入法]
---
{% include JB/setup %}

## 显示输入法图标命令
{% highlight bash %}
killall ibus-daemon
ibus-daemon -d
{% endhighlight %}