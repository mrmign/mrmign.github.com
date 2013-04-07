---
layout: post
title: "Basic python"
category: learning 
tags: [python]
description: This is record of python basics.
---
{% include JB/setup %}

## python's 29 keywords
{% highlight python %}
 and      def    exec    if     not   return
 assert   del    finally import or    try
 break    elif   for     in     pass  while
 class    else   from    is     print yield
 continue except global  lambda raise
 {% endhighlight %}

## Use module
Before we can use the functions from a module, we have to import them.To call one of the functions, we have to specify the name of the module and the name of the function, separated by a dot.`module.func`.

## Fibonacci
{% highlight python %}
previous = {0:1, 1:1}
def fibonacci(n):
	if previous.has_key(n):
		return previous[n]
	else:
		newValue = fibonacci(n-1) + fibonacci(n-2)
		previous[n] = newValue
		return newValue
{% endhighlight %}

## To signal an exception using the `raise` statement.
{% highlight python %}
def inputNumber () :
    x = input (’Pick a number: ’)
    if x == 17 :
        raise ValueError, ’17 is a bad number’
    return x
{% endhighlight %}

## `__str__`
Printing a Point object implicitly invokes `__str__` on the object, so defining `__str__` also changes the behavior of print.

## Python Data Structures
### Stack
{% highlight python %}
class Stack:
	def __init__(self):
		self.items = []

	def push(self, item):
		self.items.append(item)

	def pop(self):
		return self.items.pop()

	def isEmpty(self):
		return (self.items == [])
{% endhighlight %}

Postfix example with statck.
{% highlight python %}
def evalPostfix(expr):
  	import re
  	tokenList = re.split("([^0-9])", expr)
  	stack = Stack()
  	for token in tokenList:
    	if token == ’’ or token == ’ ’:
      		continue
    	if token == ’+’:
      		sum = stack.pop() + stack.pop()
      		stack.push(sum)
    	elif token == ’*’:
      		product = stack.pop() * stack.pop()
      		stack.push(product)
    	else:
      		stack.push(int(token))
  	return stack.pop()
{% endhighlight %}
## Recommendations for further readings
* Core Python Programming
* Python Essential Reference
* Python Pocket Reference

## Recommended general computer science books
* The Practice of Programming
* [The Open Book Project](http://www.ibiblio.com/obp)
* The New Turing Omnibus
* Turtles, Termites and Traffic
* Programming Pearls