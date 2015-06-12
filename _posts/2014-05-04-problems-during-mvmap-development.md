---
layout: post
title: "MVMAP开发过程中遇到的问题"
categories: iOS
tags: iOS
---

* 修改UITableViewCell中的textLabel的size [link](http://stackoverflow.com/questions/2008610/resize-uitableviewcell-textlabel)

* `numberOfSectionsInTableView`忘记返回1，结果table不显示数据，还以为是哪里写错了，找半天，都是坑啊。
* 声明了跟property同名的实例变量，忘记写`@synthesis property_name = ivar`, 导致property不能正确初始化，汗。。。
* `sizeToFit` 自动调整大小，在UIView中定义。
* UITableViewCell中的`- (void)prepareForReuse`在` tableView:cellForRowAtIndexPath:`调用前调用，可以重置cell中的值。
* 加载html时，如果有图片，且图片宽度超过屏幕宽度的话，如果不进行调整，UIWebview的宽度会与图片宽度一样，可以通过以下方法调整，把html内容加上css。

{% highlight objc %}
NSString *strTemplateHTML = [NSString stringWithFormat:@"<html><head><style>img{max-width:100%%;height:auto !important;width:auto !important;};</style></head><body style='margin:0; padding:0;'>%@</body></html>", @"insert your html content here"];
[webView loadHTMLString:strTemplateHTML baseURL:nil];
{% endhighlight %}


