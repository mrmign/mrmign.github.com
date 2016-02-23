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
    NSLog(@"0.Current IndexPath: %@", indexPath);
    NSLog(@"1.tableViewSubViews Before dequeue:%@", [[tableView subviews][0] subviews]);
    CommonCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Cell"];
    NSLog(@"2.dequeueReusableCell:%@", cell);
    NSLog(@"3.tableViewSubViews After dequeue:%@", [[tableView subviews][0] subviews]);
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

## 下面是Demo程序首次运行起来的输出结果：

### Section-0, Row-0

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000000016> {length = 2, path = 0 - 0}
1.tableViewSubViews Before dequeue:(
)
2.CommonCell Init <CommonCell: 0x7fb858c7ac70; >
3.dequeueReusableCell:<CommonCell: 0x7fb858c7ac70; >
4.tableViewSubViews After dequeue:(
)
5.CommonCell Init <CommonCell: 0x7fb858e5f110; >
~~~

>0.上面是对于`Section 0, Row 0`的输出
>
>1.因为是第一次运行，当前tableView还没有子view，所以在`dequeue`前subview为空
>
>2.接着调用`dequeueReusableCellWithIdentifier:`来获取一个identifier为**"Cell"**类型的Cell，当前tableView没有可以复用的创建一个新的，因此可以看到Init一个Cell。
>
>3.此时打印出来的cell正是上一步通过`dequeueReusableCellWithIdentifier:`得到的cell
>
>4.`dequeue`调用结束后因为当前的cell还没有返回，tableView的subview还是空的。
>
>5.在第2处已经init过一个cell了为什么到了这里又init了一个新的cell呢？通过代码可以看到，此处需要的是一个identifier为**"Cell0"**类型的cell，与前面是不同队列里的，因为当前队列也没有可复用的就创建一个新的。


### Section-1, Row-0

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000000116> {length = 2, path = 1 - 0}
1.tableViewSubViews Before dequeue:(
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >"
)
2.CommonCell Init <CommonCell: 0x7fb858c7ac70; >
3.dequeueReusableCell:<CommonCell: 0x7fb858c7ac70; >
4.tableViewSubViews After dequeue:(
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >"
)
5.New Cell Initilization <CustomTableViewCell: 0x7fb858c83a80; >
~~~

>0.上面是对于`Section 1, Row 0`的输出
>
>1.在0-0时返回了cell<0x7fb858e5f110>, tableView有了subview，可以看出正是之前创建的cell
>
>2.尝试reuse一个identifier为**"Cell"**类型的Cell，队列里没有，创建一个新的
>
>3.得到的cell就是2中创建的
>
>4.dequeue后tableview的subview没有变
>
>5.通过代码看到在section-1中使用的cell的identifier为**"CustomCell"**，队列中没有可复用的，要创建一个新的。

### Section-1, Row-1

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000200116> {length = 2, path = 1 - 1}
1.tableViewSubViews Before dequeue:(
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >"
)
2.CommonCell Init <CommonCell: 0x7fb858e61840; >
3.dequeueReusableCell:<CommonCell: 0x7fb858e61840; >
4.tableViewSubViews After dequeue:(
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >"
)
5.New Cell Initilization <CustomTableViewCell: 0x7fb858d1c090; >
~~~

>0.上面是对于`Section 1, Row 1`的输出
>
>1.已经为table创建了2个cell了，因此subview里有两个cell
>
>2.尝试reuse一个identifier为**"Cell"**类型的Cell，队列里没有，创建一个新的
>
>3.得到的cell就是2中创建的
>
>4.dequeue后tableview的subview没有变
>
>5.在section-1中使用的cell的identifier为**"CustomCell"**，队列中没有可复用的，要创建一个新的。

### Section-1, Row-2

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000400116> {length = 2, path = 1 - 2}
1.tableViewSubViews Before dequeue:(
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >"
)
2.CommonCell Init <CommonCell: 0x7fb858c7afc0; >
3.dequeueReusableCell:<CommonCell: 0x7fb858c7afc0; >
4.tableViewSubViews After dequeue:(
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >"
)
5.New Cell Initilization <CustomTableViewCell: 0x7fb858f201b0; >
~~~

>0.上面是对于`Section 1, Row 2`的输出
>
>1.已经为table创建了3个cell了，因此subview里有3个cell
>
>2.尝试reuse一个identifier为**"Cell"**类型的Cell，队列里没有，创建一个新的
>
>3.得到的cell就是2中创建的
>
>4.dequeue后tableview的subview没有变
>
>5.在section-1中使用的cell的identifier为**"CustomCell"**，队列中没有可复用的，要创建一个新的。

### Section-2, Row-0

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000000216> {length = 2, path = 2 - 0}
1.tableViewSubViews Before dequeue:(
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >"
)
2.CommonCell Init <CommonCell: 0x7fb858d1c470; >
3.dequeueReusableCell:<CommonCell: 0x7fb858d1c470; >
4.tableViewSubViews After dequeue:(
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >"
)
~~~

>0.上面是对于`Section 2, Row 0`的输出
>
>1.已经为table创建了4个cell了，因此subview里有4个cell
>
>2.尝试reuse一个identifier为**"Cell"**类型的Cell，队列里没有，创建一个新的
>
>3.得到的cell就是2中创建的
>
>4.dequeue后tableview的subview没有变。
>

### Section-2, Row-1

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000200216> {length = 2, path = 2 - 1}
1.tableViewSubViews Before dequeue:(
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >"
)
2.CommonCell Init <CommonCell: 0x7fb858d1e820; >
3.dequeueReusableCell:<CommonCell: 0x7fb858d1e820; >
4.tableViewSubViews After dequeue:(
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >"
)
~~~

>0.上面是对于`Section 2, Row 1`的输出
>
>1.已经为table创建了5个cell了，因此subview里有5个cell
>
>2.尝试reuse一个identifier为**"Cell"**类型的Cell，队列里没有，创建一个新的
>
>3.得到的cell就是2中创建的
>
>4.dequeue后tableview的subview没有变。

在Section-2里少了`5.`这一输出，因为在Section-0和Section-1中cell的identifier与`2.`中创建的cell的identifier不同，在这两个Section虽然创建了**"Cell"**类型的cell，
但是都没有用到，而在Section-2中正好需要这种类型的cell，就不会创建新的cell了。因此没有`5.`这一步。在`Section 2, Row 1`输出中也可以看到`Section 2, Row 0`中`2.`的cell。

### 当前tableView的subviews

~~~
tableView All Cells (
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; tag = 3001>"
)
~~~

上面详细分析了首次运行时cell的创建过程。下面对当前tableView进行`reloadData`操作。

## `reloadData`操作Cell的复用分析

~~~objc
@implementation UITableView (Swizzle)
- (void)swizzleReloadData
{
    NSLog(@"TableView ReloadData Before: %@", [self.subviews[0] subviews]);
    [self swizzleReloadData];
    NSLog(@"TableView ReloadData After: %@", [self.subviews[0] subviews]);
}
@end
~~~

这里我们hook了tableView的`reloadData`方法，便于打log。

下面开始分析Log。

~~~
TableView ReloadData Before: (
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; tag = 3001>"
)
~~~

从上面的输出可以看出在调用`reloadData`前，tableView的subviews跟前面我们看到的是一样的。

~~~
TableView ReloadData After: (
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; hidden = YES; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; hidden = YES; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; hidden = YES; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; hidden = YES; >",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
~~~

上面的输出是在调用了`reloadData`后，每一个view的hidden属性都成了YES。因此可以肯定在`reloadData`方法执行过程中进行hidden属性的设置。

下面对每一行reoload过程进行分析:

### Section-0, Row-0

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000000016> {length = 2, path = 0 - 0}
1.tableViewSubViews Before dequeue:(
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; hidden = YES; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; hidden = YES; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; hidden = YES; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; hidden = YES; >",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
2.dequeueReusableCell:<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>
3.tableViewSubViews After dequeue:(
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; hidden = YES; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; hidden = YES; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; hidden = YES; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; hidden = YES; >",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
~~~

>1.因为前面调用了`reloadData`，因此view的hidden都是YES
>
>2.尝试reuse一个identifier为**"Cell"**类型的Cell，队列有该类型的，因此返回它并复用，但是，从代码中看出此时真正需要的是**"Cell0"**类型的。
>

说明：在Section-0, Row-0这里，所需要的cell的identifier是**"Cell0"**，从前面我们知道tableview里有这样的cell可以复用，这里就是复用的该cell。
在下一行的输出中就可以看到结果。

### Section-1, Row-0

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000000116> {length = 2, path = 1 - 0}
1.tableViewSubViews Before dequeue:(
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; hidden = YES; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; hidden = YES; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; hidden = YES; tag = 2000>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
2.dequeueReusableCell:<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>
3.tableViewSubViews After dequeue:(
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; hidden = YES; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; hidden = YES; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; hidden = YES; tag = 2000>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
~~~

>1.在上一个Section-0, Row-0的时候就说明过了，会复用**"Cell0"**这个类型的cell，从现在的输出看的确是这样的，`text = 'Section 0, Row 0';`的cell的hidden已经不是YES了
>
>2.尝试reuse一个identifier为**"Cell"**类型的Cell，队列有该类型的，因此返回它并复用。但是，从代码中看出此时真正需要的是**"CustomCell"**类型的。

### Section-1, Row-1

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000200116> {length = 2, path = 1 - 1}
1.tableViewSubViews Before dequeue:(
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; hidden = YES; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; hidden = YES; tag = 2001>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
2.CommonCell Init <CommonCell: 0x7fb858e651b0; >
3.dequeueReusableCell:<CommonCell: 0x7fb858e651b0; >
4.tableViewSubViews After dequeue:(
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; hidden = YES; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; hidden = YES; tag = 2001>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
~~~

>
>

### Section-1, Row-2

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000400116> {length = 2, path = 1 - 2}
1.tableViewSubViews Before dequeue:(
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; hidden = YES; tag = 2002>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
2.CommonCell Init <CommonCell: 0x7fb858c75570; >
3.dequeueReusableCell:<CommonCell: 0x7fb858c75570; >
4.tableViewSubViews After dequeue:(
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; hidden = YES; tag = 2002>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
~~~

>

### Section-2, Row-0

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000000216> {length = 2, path = 2 - 0}
1.tableViewSubViews Before dequeue:(
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
2.CommonCell Init <CommonCell: 0x7fb858e651b0; >
3.dequeueReusableCell:<CommonCell: 0x7fb858e651b0; >
4.tableViewSubViews After dequeue:(
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
~~~

>

### Section-2, Row-1

~~~
0.Current IndexPath: <NSIndexPath: 0xc000000000200216> {length = 2, path = 2 - 1}
1.tableViewSubViews Before dequeue:(
    "<CommonCell: 0x7fb858e651b0; text = 'Section 2, Row 0'; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
2.CommonCell Init <CommonCell: 0x7fb858e65580; >
3.dequeueReusableCell:<CommonCell: 0x7fb858e65580; >
4.tableViewSubViews After dequeue:(
    "<CommonCell: 0x7fb858e651b0; text = 'Section 2, Row 0'; tag = 3000>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
~~~

>


### 当前tableView的subviews

~~~
tableView All Cells (
    "<CommonCell: 0x7fb858e65580; text = 'Section 2, Row 1'; tag = 3001>",
    "<CustomTableViewCell: 0x7fb858f201b0; text = 'Section 1, Row 2'; tag = 2002>",
    "<CustomTableViewCell: 0x7fb858d1c090; text = 'Section 1, Row 1'; tag = 2001>",
    "<CustomTableViewCell: 0x7fb858c83a80; text = 'Section 1, Row 0'; tag = 2000>",
    "<CommonCell: 0x7fb858e5f110; text = 'Section 0, Row 0'; >",
    "<CommonCell: 0x7fb858e651b0; text = 'Section 2, Row 0'; tag = 3000>",
    "<CommonCell: 0x7fb858d1c470; text = 'Section 2, Row 0'; hidden = YES; tag = 3000>",
    "<CommonCell: 0x7fb858d1e820; text = 'Section 2, Row 1'; hidden = YES; tag = 3001>"
)
~~~