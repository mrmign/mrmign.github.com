---
layout: post
title: "iOS development tools"
categories: iOS
tags: iOS tool
---

## 查看打包好的iOS应用中的png图片

在编译iOS应用时，Xcode会优化应用程序包中的png文件，因此用Preview查看不会显示。
优化是通过`pngcrush`工具实现的，可以在XCode中找到，该工具支持命令行参数
`-revert-iphone-optimizations` ，对优化过的图片的一个逆向，下面示例就是将一个
优化过的iOS png文件转化为标准的png文件。
{% highlight bash %}
$ xcrun -sdk iphoneos pngcrush \
        -revert-iphone-optimizations -q Local.png Local-standard.png
{% endhighlight %}
