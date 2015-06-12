---
layout: post
title: "wax for iOS"
categories: iOS
tags: iOS, wax
---


Lua与objc集成的原理：

###  基础
* Objective-C Runtime API:
    * <objc/runtime.h>, <objc/message.h>
    * objc_allocateClassPair
    * class_addIvar
    * class_addMethod
    * ...
* Lua的meta特性:
    * UserData: C struct
    * __index(lua_State *L)
    * __call(lua_State *L)
    * C Function Closure

###  需要解决的两个问题

1. 在Lua在生成Objc的Class。利用UserData, Objc Runtime API
2. 将Lua的调用转换为Objc的调用。利用Lua的C Function Closure, NSInvocation

wax_start是执行lua脚本的入口，在执行lua之前要创建wax的环境，

{% highlight objc %}
void wax_setup() {
	NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler); 
	
    NSFileManager *fileManager = [NSFileManager defaultManager];
    [fileManager changeCurrentDirectoryPath:[[NSBundle mainBundle] bundlePath]];
    
    lua_State *L = wax_currentLuaState();
	lua_atpanic(L, &wax_panic);
    
    luaL_openlibs(L); 

	luaopen_wax_class(L);
    luaopen_wax_instance(L);
    luaopen_wax_struct(L);
	
    addGlobals(L);
	
	[wax_gc start];
}
{% endhighlight %}

在wax_class中创建`wax.class`表，wax_instance创建`wax.instance`表，wax_struct创建`waxt.struct`表。

运行wax的stdlib, 这个stdlib是用lua写的，

{% highlight c %}
wax_start(char *initScipt, lua_CFunction extension, ...)
    wax_setup();
        luaopen_wax_class(L);        //lua访问Cocoa
            Finds an objc class      //__index
            Creates a new Objc class //__call

        luaopen_wax_instance(L);     //Cocoa对象
        luaopen_wax_struct(L);       //Cocoa struct
    Load extension, stdlib           //lua的json, xml, http等
    luaL_dostring(L, initScipt);     //加载用户代码

...

wax_end();  //lua_close(wax_currentLuaState());
{% endhighlight %}

运行到`waxClass{"StatesTable", UITableViewController, protocols = {"UITableViewDataSource", "UITableViewDelegate"}}`时，


wax在lua中进行OC对象的注册过程

waxClass.lua中定义了`waxClass`方法，当在lua文件中通过`waxClass{"MyClass",NSObject， protocols={}}`定义类的时候，就会调用waxClass.lua中的方法，在该方法中会进行类的注册，protocol的注册。

`waxClass`方法调用`waxInlineclass`方法，调用`wax.class(className, superclassName)`实际上调用的是wax_class.m中的定义的元方法`__call`。

![](path "opt title")

于为什么每个对象都按类对象来查找，是因为在wax的stdlib的init.lua中设置了_G的元方法__index, `local class = wax.class[key]`因此为一直调用查找类的方法来寻找对象。

在waxClass创建对象时查找父类对象的操作要比创建类对象的动作时间早。

lvm处理lua脚本中的方法时都会调用 __newindex 来添加到相应的userdata中，传递参数为userdata, key(方法名), value(方法地址)

overrideMethod, 从当前对象中查找是否有该方法，如果没有从protocol中找。 找到后

