---
layout: post
title: "Swift学习笔记4"
category: "iOS"
tags: "[swift]"
description: ""
---

## Extension

Extension声明只能在文件的最顶层。也就是说不能嵌套在其他类型中声明。
`extension typeName [: protocols ] {}`

限制：

* extension不能重写已有的成员（但是你可以重载overload已有的方法）
* 不能声明存储属性，但是可以声明计算属性
* 类型的扩展不能声明designated initializer或deintializer,但是可以声明convenience initializer.

扩展可以用来组织代码，可以将要实现的协议用扩展来实现。

**当扩展Swift的struct时，可以声明initializer,并且保留隐式的初始化方法**

~~~swift
struct Digit {
    var num : Int
}

extension Digit {
    init() {
        self.init(num: 2)
    }
}
~~~

### Extending Protocols

当扩展协议时，你可以为协议添加方法和属性，跟协议声明不同，这些方法和属性不是必须要被adopter实现的。他们是真实的方法和属性，会被实现该协议的类型继承。

~~~swift
protocol Flier {
}
extension Flier {
    func fly() {
        print("flap flap flap")
    }
}
struct Bird:Flier {
}
let b = Bird()
b.fly() //flap flap flap

struct Insect : Flier {
    func fly() {
        print("whirr")
    }
}
let i = Insect()
i.fly() // whirr
~~~

**Warning: 这种继承不是多态的** adopter的实现不是重写，它是另一个实现。
如果要让它像多态继承，必须在原始的protocol中声明为必须实现的方法。

### Extending Generics

~~~swift
extension Array where Element:Comparable {

}
~~~

## Umbrella Types

### AnyObject

它实际上是一个protocol,它有特殊特征，所有的类类型都自动conform to it.

`AnyObject`是swift版本的`id`

### AnyClass

### Any

> The `Any` type is a type alias for an empty protocol that is automatically adopted by all types.
> 

## Error

在Swift中，an error必须实现`ErrorType`协议的对象，它只有一个string的`_domain`和一个Int的`_code`属性。

错误机制有两个阶段需要考虑：

* throwing an error.会打断当前的执行路径，会将一个错误对象丢给错误处理机制
* catching an error. 捕获错误异常做出响应，代码继续在捕获的地方执行。

只能在下面两处地方`throw`:

* In the do block of a `do...catch` construct

~~~swift
do {
... //throw can happen here
} catch errortype {
..
} catch {
..
}
~~~
* In a function marked `throws`

~~~swift
enum NotLongEnough : ErrorType {
    case ISaidLongMeantLong
}
func giveMeALongStinrg(s:String) throws {
    if s.characters.count < 5 {
        throw NotLongEnough.ISaidLongMeantLong
    }
    print("thanks for the string")
}
~~~

在函数声明中添加`throws`会创建一个新的函数类型。
上面函数giveMeALongStinrg的类型不是（String）->()而是String）throws ->()

对于调用有throws的函数也有要求：调用者在函数前必须加`try`。

> A function called with `try` can throw. 也就是说这里的try跟throw是一样的，因此必须在do..catch块或是标记为throws的函数中。

~~~swift
func stringTest() {
    do {
        try giveMeALongStinrg("is this long enough")
    } catch {
        print("I guess it wasn't long enough")
    }
}
~~~

如果你非常确定一个函数可以throw但实际上没有throw,你可以调用时用`try!`来代替`try`,可以在任意地方使用`try!`,这样就不需要捕获可能的异常了。但是如果你错了就可能导致程序crash

在`try`与`try!`之间的是`try?`,你可以在任意地方使用`try?`而不需要捕获异常。但是，如果有异常抛出不会crash，它会返回nil。因此当表达式有返回值的时候`try?`非常适用。如果没有异常抛出，返回结果会是Optional。