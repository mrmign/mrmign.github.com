---
layout: post
title: "swift学习笔记-2"
category: "iOS"
tags: "swift"
description: ""
---


# Object Types

函数参数可以有默认值

**property必须在声明时或是在初始化方法中被初始化**

## Referring to self

在实例属性没有初始化完成前，初始化方法不能显式或隐匿的引用self(An initializer may not refer to self, explicitly or implicitly, until all instance properties have been initialized).

~~~swift
struct Cat {
	var name: String
	var license: Int
	init(name:String, license:Int) {
		self.name = name
		meow() //compile error
		self.license = license
	}
	func meow() {
		print("meow")
	}
}
~~~

## Delegating initializer

An intializer that calls another initializer is called a delegating initializer.

A delegating initailzer cannot set an immutable property(a `let` variable).因为只有在调用了其他初始化方法后才能引用属性，这个时候实例已经完全初始化了，已经无法再初始化let的属性了。

~~~swift
struct Digit {
	var number: Int
	var meaningOfLife: Bool
	//let meaningOfLife :Bool
	init(number:Int) {
		self.number = number
		self.meaningOfLife = false
	}
	init() {
		self.init(number:43)
		self.mearningOfLife = true //如果meaningOfLife声明为let这里就编译错误了
	}
}
~~~

## Failable initailizer

有可能返回nil的初始化方法。An initializer can return an Optional wrapping the new instance.

~~~swift
calss Dog {
	let name: String
	let license: Int
	init!(name:String, license:Int) {
		self.name = name
		self.license = license
		if name.isEmpty {
			return nil
		}
		if license <= 0 {
			return nil
		}
	}
}
~~~

上面的返回值是`Dog!`, the Optional is implicitly unwrapped.
可以直接使用返回的结果，但是如果返回nil， 直接使用就会导致crash

~~~swift
let fido = Dog(name:"", license:0)
let name = fido.name //crash
~~~

`UIImage`的初始化方法`init?(named:)`也是failable initializer,它没有implicitly unwrapped,所以返回是`UIImage?`,在使用前必须unwrapped.

## Properties

* 有固定的类型
* 可以是var或let
* 可以是stored或computed
* 可以有setter observer
* 实例属性可以声明为lazy

存储型(stored)的实例属性必须有初始值(可以在声明时赋，也可以在初始化方法中赋值)。在属性初始化时不会调用Setter observer。

**初始化属性的代码不能获取实例属性也不能调用实例方法**，因为会显式或隐匿的引用到`self`，但是在初始化时还没有`self`。

~~~swift
class Moi {
	let first = "mat"
	let last = "Nur"
	let whole = self.first + " " + self.last //compile error
	let who : String { //改用计算型的
		return self.first + " " + self.last
	}
	lazy var who2: String = self.first + " " + self.last
}
~~~

上面在初始化时访问了其他属性导致编译错误，可以改为用计算型的，因为计算型的不会真正计算直到`self`存在。

另外，还可以通过声明whole为lazy来解决。同样只有在self存在的时候才执行。

同样，计算型的和lazy的可以调用实例方法。

属性的初始化方法可以有多行代码，你可以定义执行匿名函数。如果代码有访问其他的属性或是实例方法，必须声明为`lazy`

~~~swift
class Moi {
	let first = "mat"
	let last = "Nur"
	lazy var whole2: String = {
        var s = self.first
        s.appendContentsOf(" ")
        s.appendContentsOf(self.last)
        return s
    }()
}
~~~

静态属性初始化时可以引用其他静态属性，因为静态属性的初始化是`lazy`的。

## Methods

静态方法和类方法是通过`type`来访问的，`self`也就是type.

静态方法和类方法不能引用实例，因为根本就没有实例。因此静态方法和类方法不能直接引用任何实例属性和调用实例方法。反过来，实例方法可以访问静态属性和类属性，同样也可以调用静态方法和类方法。

#### 关于实例方法的一个私密

**实例方法实际上是静态/类方法**

下面的代码是合法的

~~~swift
class MyClass {
	var s = ""
	func store(s:String) {
		self.s = s
	}
}
let m = MyClass()
let f = MyClass.store(m)
~~~

`store`是一个实例方法，但是可以按类方法的方式来调用，参数是该类的一个实例。

原因是**An instance method is actually a curried static/class method composed of two functions - one function that takes an instance, and another function that takes the parameters of the instance method.**

因此，上面代码执行后`f`是第二种函数，can be called as a way of passing a parameter to the `store` method of the instance `m`.

~~~swift
f("howdy")
print(m.s) //howdy
~~~

## Enums

可以用`rawValue:`的实例化方法来初始化有初始值的enum.`let type = Filter(rawValue:"Album")`,因为这里给的raw value可能没有对应的case,因此这是个failable initializer,返回值是Optional的。

### Enum Property

enum可以有实例属性和静态属性，但是enum的实例属性不能是存储型的(stored),因为如果相同case的两个实例如果存储了不同的实例属性值，它们就不再相同了。computed的属性是可以的。

## Struct

自动会有一个无参的`init()`,但是如果显式地添加了你自己的初始化方法，就不能再访问`init()`了，但是可以添加`init()`方法。

如果结构体有存储型属性但是没有显式的初始化方法，就会有一个根据实例属性衍生来的隐式初始化方法。

~~~swift
struct Digit {
	var number : Int
	var str : String
}

let d = Digit(number:2, str:"strut")
~~~

如果实例方法要设置属性值，该方法必须标识为`mutating`,调用该方法的实例必须是`var`类型的。

### Struct As Namespace

~~~swift
struct Default {
	static let Rows = "Rows"
	static let Columns = "Columns"
}
~~~

**many Objective-C enums are bridged to Swift as this kind of Struct**

## Classes

在Objective-C中，类是唯一的对象类型。Some built-in Swift struct are magically bridged to Objective-C class types, **but your custom struct types dont't have that magic.** 这也是在与OC和Cocoa交互时，声明类而不是结构体的主要原因。

**递归引用**

值类型与引用类型的区别：值类型不能结构上递归，也就是值类型的实例属性不能是相同类型的实例，如下代码就会编译失败

~~~swift
struct Dog {
    var puppy : Dog?
}
~~~

In Swift 2.0 an enum case's associated value can be an instance of that enum, provided the case( or the entire enum)is marked `indirect`

~~~swift
enum Node {
    case None(Int)
    indirect case Left(Int, Node)
    indirect case Right(Int, Node)
    indirect case Both(Int, Node, Node)
}
~~~

子类可以继承父类的属性，也可以添加自己的属性，也可覆盖继承来的属性。

* **通过`final`声明类可以阻止子类继承自该类。**
* **同样也可以用`final`防止类成员被子类重写**

### Class Initializer

* Implicit initializer.如果一个类没有存储属性，亦或存储属性在声明时就初始化了，并且没有显式的初始化方法，就会有一个隐匿的初始化方法`init()`
* Designated initializer.如果一个类有存储属性并且在声明时没有进行初始化，该类必须至少有一个designated initializer，当类初始化的时候所有的存储属性必须被初始化了。
* Convenience initializer.用`convenience`修饰。必须有`self.init(...)`调用。在当前类中，必须调用一个designated initializer或是调用另一个convenience初始化方法。

~~~swift
class Dog {
	var name : String
	var license : Int
	inti(name: String, license: Int) {
		self.name = name
		self.license = license
	}
	convenience init(license: Int) {
		self.init(name:"Fido", license:license)
	}
	convenience init() {
		self.init(license:1)
	}
}
~~~

### Subclass initializer

* No declared initializer. 初始化方法由父类继承来的组成
* Convenience initializer only. 
* Designated initializer. **不再有继承的初始化方法了！**显式的designated initializer 阻止了初始化方法的继承。现在子类有的唯一的初始化方法就是显式定义的。子类的designated initializer必须做下面的事:
	1. 必须保证子类所有的属性被初始化
	2. 必须调用`super.init(...)`，而且该方法必须是父类的designated initializer
	3. 然后才能使用`self`来调用实例方法，或访问继承来的属性。
	
### Override initializer