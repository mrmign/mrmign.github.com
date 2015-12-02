---
layout: post
title: "KVC Programming基础"
category: "iOS"
tags: "iOS kvc"
description: ""
---

# KVC(Key-value Coding) Programming基础

KVC是KVO(Key-value Observeing)的基础。

## 什么是KVC?

KVC是一种间接访问对象属性的机制，使用字符串来区分属性，而不是通过访问方法调用或是直接通过实例变量访问。实质上KVC定义了你的应用的访问方法实现的模式和方法签名。

KVC必需的方法在`NSKeyValueCoding`中声明的，默认的实现是在`NSObject`中提供。

> Key-value coding supports properties with object values, as well as the scalar types and structs. Non-object parameters and return types are detected and automatically wrapped, and unwrapped, as described in Scalar and Structure Support.

## 使用KVC简化代码

不使用KVC时的代码：

~~~objc
- (id)tableView:(NSTableView *)tableview
      objectValueForTableColumn:(id)column row:(NSInteger)row {
 
    ChildObject *child = [childrenArray objectAtIndex:row];
    if ([[column identifier] isEqualToString:@"name"]) {
        return [child name];
    }
    if ([[column identifier] isEqualToString:@"age"]) {
        return [child age];
    }
    if ([[column identifier] isEqualToString:@"favoriteColor"]) {
        return [child favoriteColor];
    }
    // And so on.
}

~~~
使用KVC的代码：

~~~objc
- (id)tableView:(NSTableView *)tableview
      objectValueForTableColumn:(id)column row:(NSInteger)row {
 
    ChildObject *child = [childrenArray objectAtIndex:row];
    return [child valueForKey:[column identifier]];
}
~~~

从上面的两段代码比较看出，KVC可以明显的简化代码。

## 术语(Terminology)

除了已经有的术语，KVC定义了它自己的特殊术语。

KVC可以用来获取3类不同类型的对象值：`attributes`, `to-one relationships`, 和 `to-many relationships` 。术语*`property`*就是指这些类型的任意一种。

* attribute, 简单的值，如scalar(char, NSTimeInterval, int, float, or double等), string, 布尔值， **Value objects**也是
* to-one relationship.不太理解，直接引用原文
 
> A property that specifies a to-one relationship is an object that has properties of its own. These underlying properties can change without the object itself changing. For example, an NSView instance’s superview is a to-one relationship.

*  a property that specifies a to-many relationship consists of a collection of related objects

## KVC基础

### keys和key Paths

key,是用来识别一个对象的特定属性的字符串。必须用ASCII编码，以小写字母开头，不能有空格。

key path是用`.`来分隔的keys的字符串，指定要遍历的对象属性序列。

### 用KVC获取属性值

`valueForKey:`返回指定key的值，如果没有与指定key的方法或实例变量，接收者会给自己发送`valueForUndefinedKey:`消息，默认的`valueForUndefinedKey:`实现触发**NSUndefinedKeyException**异常，子类可以重写这个行为。

`valueForKeyPath:`返回指定的key path的值，如果没有对应的key对象就会收到`valueForUndefinedKey:`消息。

`dictionaryWithValuesForKeys:` 返回一个数组keys的值。返回的NSDictionary包含对应的key和value.

### 用KVC设置属性值

`setValue:forKey:`设置指定key的值，`setValue:forKey:`的默认实现会自动展开表示scalar和结构体的`NSValue`对象，并给属性赋值。如果指定的key不存在，接收者会收到`setValue:forUndefinedKey:`消息，默认的实现也会触发**NSUndefinedKeyException**异常，子类可以重写该方法。

`setValue:forKeyPath:`跟单个key差不多的做法。

`setValuesForKeysWithDictionary:`用NSDictionary的keys来指定相应属性的值，默认实现会调用`setValue:forKey:`，如果需要用nil来替换NSNull对象。

如果尝试给一个非对象属性设置nil值，接收者会给自己发送`setNilValueForKey:`消息，默认实现会触发**NSInvalidArgumentException**异常。应用可以重写该方法替换一个默认值或标记值，然后调用`setValue:forKey:`来设置新值。

### 简单属性的访问方法搜索模式

#### `setValue:forKey:`的默认搜索模式

1. 搜索接收者的类是否有方法的名字匹配`set<Key>:`
2. 如果没有找到相应的方法，并且接收者的类方法`accessInstanceVariablesDirectly`返回YES，搜索接收者的实例变量的名字是否有按下面顺序匹配的，`_<key>, _is<Key>, <key>, or is<Key>`
3. 如果找到了访问方法或实例变量，就对它进行赋值
4. 如果没有找到对应的访问方法或实例变量，调用接收者的`setValue:forUndefinedKey:`

#### `valueForKey:`的默认搜索模式

1. 搜索接收者类的访问方法名称是否有按`get<Key>, <key>, or is<Key>`这个顺序匹配的。如果有这样的方法就调用。如果方法的返回值类型是对象指针就直接返回。如果返回值类型是scalar(简单)类型，并且可以转换为NSNumber，就返回NSNumber。其他的就转化为NSValue并返回。
2. Otherwise (no simple accessor method is found), searches the class of the receiver for methods whose names match the patterns `countOf<Key>` and `objectIn<Key>AtIndex:` (corresponding to the primitive methods defined by the NSArray class) and `<key>AtIndexes:` (corresponding to the NSArray method `objectsAtIndexes:`).
    If the `countOf<Key>` method and at least one of the other two possible methods are found, a collection proxy object that   responds to all NSArray methods is returned. Each NSArray   message sent to the collection proxy object will result in  some combination of `countOf<Key>`, `objectIn<Key>AtIndex:`, and `<key>AtIndexes:` messages being sent to the original receiver of `valueForKey:`. If the class of the receiver also    implements an optional method whose name matches the pattern `get<Key>:range:` that method will be used when appropriate for best performance.
3. Otherwise (no simple accessor method or set of array access methods is found), searches the class of the receiver for a threesome of methods whose names match the patterns `countOf<Key>`, `enumeratorOf<Key>`, and `memberOf<Key>:` (corresponding to the primitive methods defined by the NSSet class).
    If all three methods are found, a collection proxy object   that responds to all NSSet methods is returned. Each NSSet  message sent to the collection proxy object will result in  some combination of `countOf<Key>`, `enumeratorOf<Key>`, and    `memberOf<Key>:` messages being sent to the original    receiver of `valueForKey:`.
4. 如果没有找到简单的访问方法或集合访问方法，如果接收者的类方法`accessInstanceVariablesDirectly`返回YES，就按下面的顺序搜索接收者类的实例变量，` _<key>, _is<Key>, <key>, or is<Key>`，如果找到了就返回对应实例变量的值，返回值类型如1中所描述的
5. 如果上面的任何一种都没找到就返回`valueForUndefinedKey:`默认实现的值。

上面的2，3中是针对集合的，这里只对简单的属性进行描述，集合的先略过。


