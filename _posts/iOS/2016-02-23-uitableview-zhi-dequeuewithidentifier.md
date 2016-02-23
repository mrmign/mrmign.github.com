---
layout: post
title: "UITableView之dequeueReuseCellWithIdentifier:"
category: "iOS"
tags: "iOS, UITableView"
description: ""
---

做过iOS App开发的都用过UITablveView，这个View也是在展示列表类型的数据时用的最多的一个。这个View的实现使用了**复用**的原理。
其实这个**复用**也是挺好理解的，手机屏幕就那么大，如果我们要展示几千几万行的数据，没必要去创建几千几万个cell，而且手机内存有限，也
不允许这样做。因为Table可以滚动，当上下滚动Table时，总会有Cell进入屏幕有Cell离开屏幕，已经离开的Cell就可以准备更新下数据再次进入屏幕了，
即将离开的Cell就进入等待再次进入屏蔽的队列，就像是一个循环队列一样，这就是UITableView的复用机制。
但是有一点要说明的是，TableView里可能会有多种Cell来展示不同类型的数据，这些不同类型的Cell队列如何维护呢？ 使用identifier唯一区分不同类型的Cell，
也就是说每种类型的Cell都有一个唯一的identifier与之对应，然后把这些有相同identifier的Cell组成一个循环队列，需要的时候根据identifier来取相应队列中
的可用Cell.

这里不详细说UITableView的具体使用方法，直接上代码，下面代码是根据项目中的代码进行还原的。

~~~ objc

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 3;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    NSInteger rows = 0;
    switch (section) {
        case 0:
            rows = 1;
            break;
        case 1:
            rows = 3;
            break;
        case 2:
            rows = 2;
            break;
        default:
            break;
    }
    return rows;
    
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSLog(@"Current IndexPath: %@", indexPath);
    NSLog(@"cellForRowAtIndexPath dequeue Before:%@", [[tableView subviews][0] subviews]);
    CommonCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Cell"];
    NSLog(@"cellForRowAtIndexPath equeueReusableCell:%@", cell);
    NSLog(@"cellForRowAtIndexPath dequeue After:%@", [[tableView subviews][0] subviews]);
    NSString *title = [NSString stringWithFormat:@"Section %zi, Row %zi", indexPath.section ,indexPath.row];
    if (indexPath.section == 0) {
        cell = [tableView dequeueReusableCellWithIdentifier:@"Cell0"];
        if (cell == nil) {
            cell = [[CommonCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"Cell0"];
        }
        cell.textLabel.text = title;
    }
    else if (indexPath.section == 1) {
        CustomTableViewCell *customCell = [tableView dequeueReusableCellWithIdentifier:@"CustomCell"];
        if (customCell == nil) {
            customCell = [[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"CustomCell"];
        }
        customCell.titleLabel.text = title;
        customCell.tag = 2000+indexPath.row;
        return customCell;
    }
    else {
        cell.tag = 3000 + indexPath.row;
    }
    cell.textLabel.text = title;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSLog(@"tableView All Cells %@", [[tableView subviews][0] subviews]);
}
~~~

在上面的Table中我们返回3个Section,每个Section对应的行数为1，3，2。代码运行效果如下图所示，



看到上面的运行结果，好像没有任何问题哈。其实不然的，我们可以通过神器Reveal来看下真实情况。

刚刚运行起来的结果图

reloadData后的视图

从第二张图中可以看出内存里已经有了垃圾对象。下面分析导致该问题的原因。

在`tableView:cellForRowAtIndexPath:`方法中我加了一些Log输出当前TableView的子view，也就是Cells。当点击任意一行Cell的时候输出TableView当前的子Views。

下面开始分析TableView复用Cell的过程。

下面是Demo程序首次运行起来的输出结果：

~~~
Current IndexPath: <NSIndexPath: 0xc000000000000016> {length = 2, path = 0 - 0}
cellForRowAtIndexPath dequeue Before:(
)
CommonCell Init <CommonCell: 0x7fb9a8f00400; baseClass = UITableViewCell; frame = (0 0; 320 44); layer = <CALayer: 0x7fb9aa812680>>
cellForRowAtIndexPath equeueReusableCell:<CommonCell: 0x7fb9a8f00400; baseClass = UITableViewCell; frame = (0 0; 320 44); layer = <CALayer: 0x7fb9aa812680>>
cellForRowAtIndexPath dequeue After:(
)
CommonCell Init <CommonCell: 0x7fb9a8c47c30; baseClass = UITableViewCell; frame = (0 0; 320 44); layer = <CALayer: 0x7fb9a8c20c70>>
~~~

上面是对于`Section 0, Row 0`的输出，
