---
layout: post
title: "BNR Objective C Programming"
categories: iOS
tags: iOS
---

### Basics
* `BOOL`在`objc/objc.h`定义
* if/else 最好写上花括号，别像Apple那样犯低级错误 `goto fail`
* `sleep()` in `unistd.h`中
* `EXIT_SUCCESS` 和 `EXIT_FAILUR`在`stdlib.h`中
* `%zu` 打印 sizeof返回的`size_t`
* （实例变量以 _ 开头只是为了与局部变量进行区分，没有特殊含义）【好像不是这样子的！】。如果只声明property, 编译器会默认添加 _name的变量，可以显示的使用。
* %@ 符号调用相应对象的的`description`方法
* 用 `@interface ClassName()...@end`声明实例变量或属性，只有在类内部可见，对象不可见
* 子类不能访问父类的类扩展
* `__weak MyObject *obj` 声明弱引用
* 数组排序 `NSSortDescriptor`, 过滤`NSPredicate`
* `NSNumber`实例，@4, @5.6
* 用`NS_ENUM()`声明枚举类弄
{% highlight objc %}
typedef NS_ENUM([char, int, unsinged long,...], enum_name){
...
};
{% endhighlight %}
* OC中有4种形式的回调：(Demo in Callbacks)
    1. Target-action, 用`target:obj selector:@selector()`。 **为了加快运行速度，编译器为每一个方法分配唯一的数字，在运行时使用数字而不是方法名**
    2. Helper-action用delegate实现
    3. Notifications
    4. BLocks
* `__unused`  去除警告
* block 会对它引用的对象保持强引用。
    {% highlight objc %}
    mybolck = ^{
        NSLog(@"%@", self); //这种方法导致强引用
    }
    __weak MyObject *weakSelf = self;
    myblock = ^{
        NSLog(@"%@", weakSelf);
    }
    {% endhighlight %}
* 不要直接引用实例变量,使用存取器
{% highlight objc %}
__weak MyObject *weakSelf = self;
myblock = ^{
    NSLog(@"%@", _iVar); //直接访问实例变量
}
/* 上面的代码编译器会编译为 */
__weak MyObject *weakSelf = self;
myblock = ^{
    NSLog(@"%@", self->_iVar); //还是会导致self的强引用
}
/* 应该这样写 */
__weak MyObject *weakSelf = self;
myblock = ^{
    MyObject *innerSelf = weakSelf;
    NSLog(@"%@", innerself.iVar);
}
{% endhighlight %}
* block访问的外部变量默认为常量，不能修改它们的值。如果想在block中修改外部变量，要使用`__block`来声明。
* 是否响应某个方法`respondsToSelector:`
* 基于事件驱动，就是应用加载完后，开启循环坐等事件到来。
* `UITableView` `[tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"Cell"]`

### Advances
* init。`instancetype` 告诉编译器期望该方法所属的类的一个实例。任何你写的或是覆盖的初始化方法应该返回instancetype。在Xcode4.3之前，使用的是id, 但是instancetype是更好的选择。
{% highlight objc %}
- (instancetype)init
{
    //self = [super init];
    //if(self){
    if(self = [super init]){
        _var1 = ...;
    }// 养成好习惯：检查父类的初始化，用实例变量来赋值。
    return self;
}
{% endhighlight %}
* 初始化方法的写法：
    1. 如果一个类有多个初始化方法，只有一个做真正的初始化工作，也就是指定的初始化方法。其他所有的初始化方法，直接或间接的调用该指定的初始化方法（每个类只有一个指定的初始化方法。如果一个类有其他的初始化方法，这些方法必须调用指定的初始化方法。）
    2. 指定的初始化方法在初始化它的实例变量前会调用父类指定的初始化方法
    3. 如果你的类的指定初始化方法与父类的指定的初始化方法名字不同，你必须重写父类的指定的初始化方法，并调用新的指定的初始化方法
    4. 如果有多个初始化方法，在头文件中要有明显的文档指明哪个是指定的初始化方法。
* property attributes
    * `readwrite`**默认** `readonly`
    * `assign`对非对象类型是**默认**的，只是把传过来的值赋给属性
    * `strong` 对于对象指针是**默认**的
    * `weak` 没有对所指对象的拥有权，如果这个对象被释放，属性会自动被置为nil，避免野指针。
    * `unsafe_unretained` 跟 weak一样没有拥有权，但是当对象被释放时不会自动置为nil。
    * `copy` 对传进的对象的副本有强引用。
    * `copyWithZone:`和`mutableCopyWithZone:`定义在`NSCopying`和`NSMutableCopying`协议里，如果想自己的类有copy功能，要遵从这2个协议。
    * `nonatomic` 总是使`readwrite`的属性为nonatomic. **默认**的为`atomic`

{% highlight objc %}
- (id)copy
{
    return [self copyWithZone:NULL];
}
- (id)mutableCopy
{
    return [self mutableCopyWithZone:NULL];
}
{% endhighlight %}
* key-value
    * key path
{% highlight objc %}
NSStrng *num = [sales valueForKeyPath:@"manager.contacts.phone"];
[sales setValue:@"5555-555" forKeyPath:@"manager.contacts.phone"];
{% endhighlight %}
* KVO(key-value observing)用kvo context区分不同的通知，如子父与父类的。
* 显示地触发通知`willChangeValueForKey:` 和 `didChangeValueForKey:`
* 运行时查看class,methods的方法很好。
