---
layout: post
title: "Swift学习笔记5"
category: "iOS"
tags: "[swift]"
description: ""
---

## Memory Management

### Weak Reference

- only an `Optional` reference can be marked as weak.
- the reference must be a `var` reference.

对于循环引用的情况，只需要其中一者是weak的就可以，规则

>The one that is not the "owner" will have a weak reference to its "owner".

### Unowned Reference

该引用在下面的例子中特别有用，如果一个对象没有对其他对象的引用就不能存在，但是这个引用又不需要一直存在。 就像人与小狗，小狗必须有主人，但是人不一定有小狗。
可以把小狗的主人声明为`unowned`.

Unowned reference可以是Optional也可以是let的。但是用unowned是有风险的，有可能后面访问对象时为空。

只有对类类型的引用才能声明为`weak`或`unowned`。

### 匿名函数中的weak与unowned引用

~~~swift
class FunctionHolder {
    var function : (Void -> Void)?
    deinit {
        print("deinit")
    }
}
func testFunctionHolder() {
    let f = FunctionHolder()
    f.function = {
        [weak f] in
        print(f)
    }
}
~~~

传入匿名函数的引用是Optional的，通常是进行一个weak-strong转换

~~~swift
class FunctionHolder {
    var function : (Void -> Void)?
    deinit {
        print("deinit")
    }
}
func testFunctionHolder() {
    let f = FunctionHolder()
    f.function = {
        [weak f] in //weak
        guard let f = f else { return }
        print(f) //strong
    }
}
~~~

`unowned`用的最多的场景还是针对`self`引用的情况。

~~~swift
class MyDropBounceAndRollBehavior : UIDynamicBehavior {
    let v : UIView
    init(view v:UIView) {
        self.v = v
        super.init()
    }
    override func willMoveToAnimator(dynamicAnimator: UIDynamicAnimator?) {
        if dynamicAnimator == nil { return }
        let sup = self.v.superview!
        let grav = UIGravityBehavior()
        grav.action = {
            [unowned self] in
            let items = dynamicAnimator?.itemsInRect(sup.bounds) as! [UIView]
            if items.indexOf(self.v) == nil {
                dynamicAnimator?.removeBehavior(self)
                self.v.removeFromSuperview()
            }
        }
        self.addChildBehavior(grav)
        grav.addItem(self.v)
    }
}
~~~

对于协议类型的引用只有当它是类协议(**标记为@objc或class**)的时候才可以声明`weak`或`unowned`

Obejctive-C中声明的协议已经隐式标记为@objc，因此是类协议。