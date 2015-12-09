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



