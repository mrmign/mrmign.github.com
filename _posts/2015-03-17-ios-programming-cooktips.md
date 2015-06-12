---
layout: post
title: "ios programming cookTips"
categories: iOS
tags: iOS
---

### 创建ToolBar [StackOverflow](http://stackoverflow.com/questions/2312484/uitoolbar-on-each-page-of-uinavigationcontroller)

{% highlight objc lineons%}

    CGRect frame, remain;
    CGRectDivide(self.view.bounds, &frame, &remain, 44, CGRectMaxYEdge);
    _toolbar = [[UIToolbar alloc] initWithFrame:frame];
//    _toolbar.autoresizingMask = UIViewAutoresizingFlexibleTopMargin;
    UIBarButtonItem *button1 = [[UIBarButtonItem alloc] initWithTitle:@"今天" style:UIBarButtonItemStyleDone target:self action:@selector(toolBarGotoToday)];
    UIBarButtonItem *spacer = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:self action:nil];
    
    UIBarButtonItem *button2=[[UIBarButtonItem alloc]initWithImage:[UIImage imageNamed:@"schedule_back"] style:UIBarButtonItemStylePlain target:self action:@selector(toolbarBackClick)];
    [_toolbar setItems:[[NSArray alloc] initWithObjects:button1,spacer,button2,nil]];
//    [_toolbar setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleTopMargin];
//    [self.view addSubview:_toolbar];

{% endhighlight %}

直接使用UIViewController里的toolBar
{% highlight objc lineons%}
    self.navigationController.toolbarHidden = NO;
    self.toolbarItems = @[button1,spacer,button2];
{% endhighlight %}

#### Related

* [http://stackoverflow.com/questions/227078/creating-a-left-arrow-button-like-uinavigationbars-back-style-on-a-uitoolba?rq=1](http://stackoverflow.com/questions/227078/creating-a-left-arrow-button-like-uinavigationbars-back-style-on-a-uitoolba?rq=1)


圆形UIImageView
imageView.layer.cornerRadius = imageView.width/2;
imageView.layer.maskToBounds = YEA;

