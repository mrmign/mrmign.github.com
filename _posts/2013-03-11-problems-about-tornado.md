---
layout: post
title: "problems about tornado"
categories: programming
tags: python tornado
---

This is for these problems ever came across.
-------------
## 1. Parameters' name in template extend
In `me.html` there is a 
{% highlight python %}
for group in user.groups
...
end
{% endhighlight %}
In `megroup.html`, it extends from `me.html`
and has a parameter named *group*, it is overridden by the *group* in me for-loop.
So, the parameters passed to template files must be specified uniquely, in case conflict with 
the variables in super template file.

>**NOTE**: In my view, the parameters passed to template files are assigned firstly, 
then produce the output with these parameters, so the local variables may override the parameters if they have the same name.

## 2. **Empty link url**
In the html content, if there is a empty link like `<a href="">link</a>` or `style="background-image:url();"`, 
such links are refered to the page's url as default, such that, when the images is requested, it will request 
the page's url, since there is nothing changed, it will return 304(Not modified),
In our pages, there was such a problem, it requests the same url twice. It's a very low level fault that is ignored easily.
