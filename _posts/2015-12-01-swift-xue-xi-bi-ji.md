---
layout: post
title: "swift学习笔记"
category: "iOS"
tags: "[swift]"
description: ""
---

Swift有三种类型的对象: class, struct, enum

## Function Parameters and Return Value

`Void`(函数没有返回值时返回的类型)在Swift中是真实的类型，没有返回任何值的函数实际返回的就是Void类型,也可以用()来表示。
`return Void`,`return ()`,`return` 是一个效果。

~~~swift
func f() -> Void {}
func f() -> () {}
func f() {}
~~~
上面三个方法都是没有返回值的。

#### 函数签名(Function Signature)

利用参数与返回值确定函数签名，例如`(Int, Int) -> Int`。对于没有参数与返回值的函数可以用`Void -> Void`,`() -> ()`, `Void -> ()`, `() -> Void`表示，为了一致，还是优先使用前两种。

## External Parameter Names

作用：

* 声明每个参数的目的
* 区分函数。两个函数名字和签名可以相同，但是外部参数名不能相同
* 帮助Swift与OC，Cocoa交互

**除了第一个参数，剩下的所有的参数默认自动是外部参数。** 

~~~swift
func say(s:String, times: Int) {}

//调用
say("hi", times:3)
~~~

如果不想要外部参数，在前面加`_`,像下面这样：

~~~swift
func say(s:String, _ times: Int) {}

//调用
say("hi", 3)
~~~

一个Swift函数的名字是括号前面的名字加上外部参数的名字，如上面的`say(_:times:)`和`say(_:_:)`。

## Overloading

两个函数如果有相同的signature但是外部参数名字不同不能说是重载；因为他们外部参数名称不同，因此他们是两个函数名不相同的函数。

## Default Parameter Values

~~~swift
func say(s: String, times: Int = 1) {}
~~~
可以用`say("hi")`和`say("hi", times:3)`来调用该函数。

## Ignored Parameters

~~~swift
func say(s:String, times:Int, loudly _:Bool) {}
//调用
say("hi",times:3,true)

func say(s:String, times:Int, _:Int){}
//调用
say("hi", 3, true)
~~~

当参数局部名称是`_`时在函数体内无法读取该参数值。

## Modifiable Parameter

~~~swift
func say(s:String, times:Int, var loudly: Bool){}
~~~
默认情况下函数参数隐式声明为常量(`let`),不能进行赋值。如果需要在函数体中对参数进行赋值，需要显式声明为`var`。虽然声明为var后可以进行赋值，但是不能修改函数体外部原来的值。如果要修改传递参数的原始的值，可以按下面操作：

1. 把想要修改的参数声明为`inout`
2. 在调用函数时，想让函数修改其值的变量必须声明为`var`
3. 不要用变量来当参数，需要传递它的地址，在变量名前加`&`

~~~swift
func removeFromeString(inout s:String, character c:Character){}

var s = "hello"
removeFromString(&s, "l")
~~~

#### `UnsafeMutablePointer` 

当需要与OC打交道而不是Swift时，需要使用`UnsafeMutablePointer `而不是`inout`

~~~swift
func CGRectDivide(rect: CGRect, _ slice: UnsafeMutablePointer<CGRect>, _ remainder: UnsafeMutablePointer<CGRect>, _ amount: CGFloat, _ edge: CGRectEdge)

var arrow = CGRectZero
var body = CGRectZero
CGRectDivide(rect, &arrow, &body, Arrow.ARHEIGHT, .MinYEdge)
~~~

当参数是class类型时，不需要声明为`inout`,因为class类型是引用类型的，其他的都是值类型。

## Function As Value

函数要作为值需要有类型，函数的类型就是它的signature.

~~~swift
func doThis(f:()->()) {
	f()
}
func whatTodo() {
	print("I did it")
}
doThis(whatTodo)
~~~

可以使用`typealis`给某个函数类型一个名字，如`typealias VoidVoidFunc = () -> ()`

## Anonymous Functions

~~~swift
func f(finished:Bool) {
	print("finished:\(finished)")
}

{
	(finished:Bool)->() in
	print("finished:\(finished)")
}
~~~

##### 匿名函数的使用：

~~~swift
UIView.animationWithDuration(0.4, animations: {
	()->() in
	self.frame.origin.y += 20
	}, completion: {
		(finished: Bool) -> () in
		print("finished:\(finished)")
})
~~~

省略返回值

~~~swift
UIView.animationWithDuration(0.4, animations: {
	() in
	self.frame.origin.y += 20
	}, completion: {
		(finished: Bool) in
		print("finished:\(finished)")
})
~~~

当没有参数时省略`in`行

~~~swift
UIView.animationWithDuration(0.4, animations: {
	self.frame.origin.y += 20
	}, completion: {
		(finished: Bool) in
		print("finished:\(finished)")
})
~~~

省略参数类型

~~~swift
UIView.animationWithDuration(0.4, animations: {
	self.frame.origin.y += 20
	}, completion: {
		(finished) in
		print("finished:\(finished)")
})
~~~

省略括号

~~~swift
UIView.animationWithDuration(0.4, animations: {
	self.frame.origin.y += 20
	}, completion: {
		finished in
		print("finished:\(finished)")
})
~~~

即使有参数也省略`in`行。如果返回值可以省略，并且如果编译器知道参数类型，你可以省略in行，在匿名函数体内直接用$0,$1,..引用对应的参数。

~~~swift
UIView.animationWithDuration(0.4, animations: {
	self.frame.origin.y += 20
	}, completion: {
		print("finished:\($0)")
})
~~~

省略参数的名字。如果匿名函数体不需要引用参数，可以用`_`在in行替换参数列表，如果不需要引用任何参数，可以只用一个`_`来替换整个参数列表。

~~~swift
UIView.animationWithDuration(0.4, animations: {
	self.frame.origin.y += 20
	}, completion: {
		_ in
		print("finished:\(finished)")
})
~~~

**不能同时省略in行也不通过magic name引用参数！！**

省略函数参数名。如果在调用函数时匿名函数作为最后一个参数，可以在倒数第二个参数闭合函数，将没有名称的匿名函数紧跟在后面。

~~~swift
UIView.animationWithDuration(0.4, animations: {
	self.frame.origin.y += 20
	}){
		_ in
		print("finished:\(finished)")
}
~~~

省略调用函数的括号。如果你用了尾函数语法，并且你调用的函数只有一个函数作为参数，你可以在调用时省略空括号。

~~~swift
func doThis(f:()->()) {
	f()
}
doThis {
	print("hi")
}
~~~

省略关键字return

~~~swift
func sayHi() -> String {
	return "Hi"
}
func performAndPrint(f:()->String) {
	let s = f()
	print(s)
}
performAndPrint {
	sayHi()
}
~~~


## Closure

Swift函数就是闭包。

## Curried Functions（柯里化函数）

~~~swift
func makeRoundedRectangleMaker(sz:CGSize, _ r:CGFloat) -> () -> UIImage {
	return {
		imageOfSize(sz) {
			let p = UIBezierPath(
				rounderRect: CGRect(origin:CGPointZero, size: sz),
				cornerRadius:r)
			p.stroke()
		}
	}
}

let maker = makeRoundedRectangleMaker(CGSizeMake(45,20),8)
~~~

~~~swift
func makeRoundedRectangleMaker(sz:CGSize) -> (CGFloat) -> UIImage {
	return {
		r in
		imageOfSize(sz) {
			let p = UIBezierPath(
				rounderRect: CGRect(origin:CGPointZero,size: sz),
				cornerRadius:r)
			p.stroke()
		}
	}
}

let maker = makeRoundedRectangleMaker(CGSizeMake(45,20))
let image = maker(8)
~~~

~~~swift
func makeRoundedRectangleMaker(sz:CGSize)(_ r:CGFloat) -> UIImage {
	return imageOfSize(sz) {
			let p = UIBezierPath(
				rounderRect: CGRect(origin:CGPointZero, size: sz),
				cornerRadius:r)
			p.stroke()
	}
}

let image = makeRoundedRectangleMaker(CGSizeMake(45,20))(8)
~~~

## Variable

变量的类型不能改变。

#### Computed Initializer

~~~swift
let timed : Bool = {
	if val == 1 {
		return true
	} else {
		return false
	}
}()
~~~

定义并调用匿名函数通常是唯一合法的方式来计算实例属性的初始值。因为在初始化实例属性时不能调用实例的方法(此时还没有实例，你正在创建实例)。

#### Computed Variables

~~~swift
var now: String {
	get {
		return NSDate().description
	}
	set {
		print(newValue)
	}
}
~~~

**注意：**

* 变量必须声明为`var`，类型必须显式声明
* get 方法必须返回与变量类型一致的值
* setter就像是有一个参数的函数，参数的局部名称默认是`newValue`，也可以修改该参数的局部名称`set (val) {}`
* setter函数不是必需的，如果省略setter，变量就变成只读的，如果尝试赋值会报编译错误。**在swift中，一个没有setter的计算变量是创建一个只读变量的主要方式**
* **一定要有getter!!**,如果没有setter, get及后面的{}可以省略。这也是只读变量的合法声明。

	~~~swift
	var now: String {
		return NSDate().description
	}
	~~~
	
#### Setter Observer

与声明computed Variable类似。

~~~swift
var s = "whatever" {
	willSet {
		print(newValue)
	}
	didSet {
		print(oldValue)
	}
}
~~~

**注意：**

* 变量必须是var,可以有初始值。
* 默认情况下`willSet`接收新值，局部名为newValue，同样也可以改成其他名字
* 默认情况下`didSet`接收旧的值，局部名为oldValue，同样也可以改为其他名字。新值已经存储了，在didSet里可以访问到，在didSet函数里修改为其他值也是合法的。

Setter Observer函数在初始化或是在`didSet`里修改值时不会调用，否则会死循环！

Computed Variable不能有setter observer!

#### Lazy Initialization

swift中有三种类型可以initialized lazily:

* **global variables**. 自动lazy.全局变量的初始化是在第一次访问的时候进行的。通过`dispatch_once`进行保护，使初始化只进行一次且是线程安全的。
* **static properties**. 静态属性行为与全局变量相似，原因也相同。(There are no stored class properties in Swift, so class properties can't be initialized and thus can't have lazy initialization.??这句是什么意思)
* **Instance properties**. 实例属性默认不是lazy的，可以在声明时用`lazy`标记，属性必须声明为var不能是let。

Lazy initialization通常用来实现单例。