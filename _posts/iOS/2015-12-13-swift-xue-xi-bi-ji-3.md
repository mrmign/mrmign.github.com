---
layout: post
title: "Swift学习笔记3"
category: "iOS"
tags: "[swift]"
description: ""
---

## Casting

用`as!`进行转换时可能会出错，可以先用`is`进行判断，然后再转。另一种方法就是用`as?`来转，结果是Optional的。

## Type Reference

实例可以通过`dynamicType`方法来获取它的类型。

~~~swift
class Dog {
    class var whatDogSay:String {
        return "woof"
    }
    fun bark() {
        print(self.dynamicType.whatDogSay)
    }
}
~~~
用`dynaimicType`而不是硬编码用爆大锅是因为它遵循多态。

~~~swift
func dogMakerAndNamer(whattye:Dog.Type) -> Dog {
    let d = whattype.init(name:"Fido")
    return d
}
~~~

因为这里不确定是否Dog的每个子类型都实现了init(name:)初始化方法，因此会编译失败。 为了保证每个类型都有`init(name:)`初始化方法，我们需要添加`required`关键字。

### Type `Self`

~~~swift
class Dog {
    var name : String
    required init(name: String) {
        self.name = name
    }
    class fun makeAndName() -> Self {
        let d = self.init(name:"Fido")
        return d
    }
}

class NoisyDog: Dog {
}
~~~

* `.dynamicType` sent to an instance
* `.Type` sent to a type
* `.self` sent to a type: the type.如果需要Dog.Type, 可以传Dog.self
* `self` 在实例代码中表示实例；在静态或类代码中表示这个类型
* `Self` 在方法声明中，指定返回类型


## Protocols

>A protocol is an object type, but there are no protocol objects.

一个对象类型实现了一个协议也就是实现了协议中的属性和方法。

>Any type --- enum, struct, class, another protocol---can adopt protocol.

swift中最有用的一个协议就是`CustomStringConvertible`, 该协议要求我们实现`description`属性。

### Declaring a protocol

协议声明只能在文件的最顶层。协议可以包含：

* Properties. 协议中的属性声明用`var`, name, type {get} 或者 {get set}。如果是{get}，实现协议的属性也可以是writable,如果是{get set}，实现协议的属性就不能是保读的。用static声明static/class属性，类实现者可以实现为class属性，也可以是static的。
* Methods. 协议中方法的声明没有方法体，没有{}。用static声明static/class方法，类实现时可以实现为class方法。
    * 如果enum/struct实现的方法需要声明为`mutating`，协议必须指定`mutating`。如果协议没有指定，实现者不能添加`mutating`
    * 如果协议有指定`mutating`,实现者可以省略
* Type alias.
* Protocol adoption.

### Optional Protocol Members

在声明协议为`@objc`时，Swfit允许有可选的协议成员。

~~~swift
@objc protocol Flier {
    optional var song: String {get}
    optioanl func sing()
}
~~~

只有类能实现这样的协议，而且该特性只有在类是`NSObject`的子类时才管用，或者是可选的成员标识为`@objc`

~~~swift
class Bird : Flier {
    @objc func sing() {
        print("tweet")
    }
}
~~~

**如果可选方法有返回值，返回类型是Optional的**

### Class Protocol

> A protoco declared with keyword `class` after the colon after its name is a *class protocol* ,meanig that it can be adopted only by class object type.

~~~swift
protocol SecondViewControllerDelegate: class {
    func acceptData(data: AnyObject!)
}
~~~

如果协议已经标记为`@objc`就没必要再声明class，`@objc`也暗示这是个类协议。

~~~swift
class SecondViewController: UIViewController {
    weak var delegate : SecondViewControllerDelegate?
    ...
}
~~~

只有类实例才会有特殊的内存管理。

### Implicitly Required Initializer

> An initializer declared in a protocol is implicitly required, and the class is forced to make that requirement explicit.

~~~swift
protocol Flier }
    init()
}
class Bird : Flier {
    required init() {}
}
~~~

如果Bird标记为`final`就没有必要把`init`标记为`required`

## Generics

在编译时确定真正的类型。

### Generic declaration

* Generic protocol with Self.在协议中，用`Self`把协议变成一个generic.`Self`是实现协议的类型。如下面的协议，如果是`Bird`实现了该协议，在实现`flockTogetherWith`方法时需要声明参数类型为`Bird`。

~~~swift
protocol Flier {
    func flockTogetherWith(f:Self)
}
~~~
    
* Generic protocol with empty type alias.协议可以声明一个type alias但不指定代表什么类型，也就是没有包含赋值符号，这样就把协议变成了generic。实现协议的要声明一个具体的类型
* Generic functions.

~~~swift
func take<T>(t:T) -> T
{
    return t
}
~~~
    
* Generic object types

~~~swift
struct Something<T> {
    var first: T
    var second: T
}
~~~

### Type Constraints

>You can limit the types that eligible to be used for resolving a particular placeholder. 
>The simplest form of type constraint is to **put a colon and type name after the placeholder's name** when it first appears.

~~~swift
protocol Flier {
    typealias Other : Flier
    func flockTogetherWith(f:Other)
}
~~~

上面的代码是不合法的，protocol不能用自己作为类型限制。

~~~swift
protocol Superfiler {}
protocol Flier : Superflier {
    typealias Other : Superflier
    func flockTogetherWith(f:Other)
}
~~~

上面通过声明另一个protocol，让Flier adopt,并且限制Other为该Protocol。

### Explicit Specialization

#### Generic protocol with associated type

~~~swift
protocol Flier {
    typealias Other
}
struct Bird: Flier {
    typealias Other = String
}
~~~

#### Generic object type

~~~swift
class Dog<T> {
    var name : T?
}
let d = Dog<String>()

class NoisyDog<T> : Dog<T> {}

class NoisyDog : Dog<String> {}
~~~

## Associated Type Chain

~~~swift
protocol Wieldable {}
struct Sword : Wieldable {}
struct Bow : Wieldable {}

protocol Superfighter {
    typealias Weapon : Wieldable
}
protocol Fighter : Superfighter {
    typealias Enemy : Superfighter
    func steal(weapon:Self.Enemy.Weapon, from:Self.Enemy)
}
struct Soldier : Fighter {
    typealias Weapon = Sword
    typealias Enemy = Archer
    func steal(weapon:Bow, from:Archer) {
    }
}
struct Archer : Fighter {
    typealias Weapon = Bow
    typealias Enemy = Soldier
    func steal(weapon: Sword, from:Soldier) {
    }
}
~~~
