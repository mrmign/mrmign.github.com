---
layout: post
title: "Motion Design for iOS(part 3)"
category: "iOS"
tags: "iOS animation"
description: ""
---

# Motion Design for iOS(part 3)

[math around matrix transformations](https://en.wikipedia.org/wiki/Transformation_matrix)

Core Animation

* `CGAffineTransformMakeScale`


### Two Animation Frameworks

* [JNWSpringAnimation](https://github.com/jwilling/JNWSpringAnimation)
* [Pop by Facebook](https://github.com/facebook/pop)


`CAKeyframeAnimation`

### Spring animation Properties

* Damping
* stiffness
* mass

### Core Animation维护了三个层树

1. Model layer tree. 当层静止没有动的时候它显示层的所有属性。如设置`view.layer.cornerRadius=50`的时候我们是在model layer上设置的属性。model layer上的属性是接触最多的，任何时候改变layer的属性都是在model layer上改的。在动画过程中model layer上值不会改变。
2. Presentation layer tree.该层呈现动画过程中层上的属性，并且属性值都是实时的。不要在该层设置任何值，相反你可以通过该层读取当前动画的相关值。
3. Render tree.渲染树是苹果私有的值，用来做真正的图像渲染，不需要知道这些值。

当我们给层添加动画时候，是在presentation tree上计算动画的值，当动画结束后，动画自动从presentation层上移除，并且presentation tree的值马上变回model layer的值(因为这些值才真正反应了层的静态属性)。如果我们想让层的属性变为动画最后的值，我们需要显示的指定。


~~~objc
JNWSpringAnimation *scale =
    [JNWSpringAnimation animationWithKeyPath:@"transform.scale"];
scale.damping = 9;
scale.stiffness = 100;
scale.mass = 2;
scale.fromValue = @(1.0);
scale.toValue = @(2.0);

[redBall.layer addAnimation:scale forKey:scale.keyPath];
redBall.transform = CGAffineTransformMakeScale(2.0, 2.0);
~~~

上面的动画在执行完成后就被移除了，layer的实际变换值会与动画的最终值相符，ball保持2倍大小。

在使用UIView基于block的动画方法的时候我们不需要这样做，是因为 这些方法自动地维持了最终的值不需要特意去设置。使用UIView基于block的动画方法的缺点就是只能使用默认的简单动画，如果想使用复杂的动画效果还是要使用`CAAnimation`对象，像`JNWSpringAnimation`。


### UIView animation options

`UIViewAnimationOptionBeginFromCurrentState` 


### JNWSpringAnimation

相同的`damping`和`stiffness`可以缓慢的拖没有反弹效果，只是平滑渐近地变换。

~~~objc
CGFloat dampingStiffness = 16.0f;

// Scale animation for the main app background
JNWSpringAnimation *scale =
    [JNWSpringAnimation animationWithKeyPath:@"transform.scale"];
scale.damping = dampingStiffness;
scale.stiffness = dampingStiffness;
scale.mass = 1;
scale.fromValue = @([[self.appBackground.layer.presentationLayer
    valueForKeyPath:scale.keyPath] floatValue]);
scale.toValue = @(0.9);

[self.appBackground.layer addAnimation:scale forKey:scale.keyPath];
self.appBackground.transform =
    CGAffineTransformScale(CGAffineTransformIdentity, .9, .9);
~~~

上面代码中的fromValue不再是固定值了，因为presentationLayer知道动画过程中的各个属性值，防止动画还没线束又发生改变，这样就可以从当前的值执行了。不会有跳变的现象。

    

