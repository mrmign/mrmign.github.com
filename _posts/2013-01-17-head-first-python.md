---
layout: post
title: "Head First Python"
category: learning 
tags: [python]
description: Reading Head First Python book notes. It's based on Python 3.
---

## 1 meet python  -- **Everyone loves lists**

### P20 
`isinstance(var, type)` 判断变量是哪个类型,类型匹配，返回True,否则,False。    
{% highlight python %}
>>> names = ['Michael', 'Terry']
>>> isinstance(names, list)
True
>>> num_names = len(names)
>>> isinstance(num_names, list)
False
{% endhighlight %}

### P21 
查看built-in functions `(__builtins__)`,查看帮助文档`help(BIF_name)`。 
{% highlight python %}
>>>a = 1 
>>>dir(a)
['__abs__', '__add__', '__and__', '__class__', '__cmp__', '__coerce__', '__delattr__', '__div__', '__divmod__', '__doc__', '__float__', '__floordiv__', '__format__', '__getattribute__', '__getnewargs__', '__hash__', '__hex__', '__index__', '__init__', '__int__', '__invert__', '__long__', '__lshift__', '__mod__', '__mul__', '__neg__', '__new__', '__nonzero__', '__oct__', '__or__', '__pos__', '__pow__', '__radd__', '__rand__', '__rdiv__', '__rdivmod__', '__reduce__', '__reduce_ex__', '__repr__', '__rfloordiv__', '__rlshift__', '__rmod__', '__rmul__', '__ror__', '__rpow__', '__rrshift__', '__rshift__', '__rsub__', '__rtruediv__', '__rxor__', '__setattr__', '__sizeof__', '__str__', '__sub__', '__subclasshook__', '__truediv__', '__trunc__', '__xor__', 'conjugate', 'denominator', 'imag', 'numerator', 'real']
>>>a = []
['__add__', '__class__', '__contains__', '__delattr__', '__delitem__', '__delslice__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__', '__getslice__', '__gt__', '__hash__', '__iadd__', '__imul__', '__init__', '__iter__', '__le__', '__len__', '__lt__', '__mul__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__reversed__', '__rmul__', '__setattr__', '__setitem__', '__setslice__', '__sizeof__', '__str__', '__subclasshook__', 'append', 'count', 'extend', 'index', 'insert', 'pop', 'remove', 'reverse', 'sort']
{% endhighlight %}


### P31
Python default recursion limit 1000, 可以用`sys.getrecursionlimit()`查看。如果需要更大，可以修改。

## 2 sharing your code -- **Modules of functions**

`PyPI` is short for Python Package Index.

### P38 
查看Python模块路径，`import sys; sys.path`,用`;`可以把多行放在一行中。 or 

{% highlight python  %}
>>>import sys
>>>sys.path
{% endhighlight %}

### P40 
distribute module:

1. Create a folder and put module files into it.
2. Create a file called `setup.py` in the new folder, and input the following code.
3. Build a distribution file.`python3 setup.py sdist`.
4. Install your distribution into your local coypy of Python.`sudo spython3 setup.py install`.    
{% highlight python %}
from distutils.core import setup

setup(
        name            = 'module name',
        version         = '1.0.0',
        py_modules      = ['module name'],
        author          = '',
        author_email    = '',
        url             = '',
        description     = '',
    )
{% endhighlight %}   

files structure:

~~~
nester
|-- MANIFEST
|-- build
|   |-- lib
|   |   |-- nester.py
|-- dist
|   |-- nester-1.0.0.tar.gz
|-- nester.py
|-- nester.pyc
`-- setup.py
~~~

### P63 

`def func(argv_1, argv_2=0)`, argv_2是可选的，`func(arg,1)`与`func(arg)`都可以。带默认值的参数要在最后。
if function is like `def func(argv_1, argv_2 = 0, argv_3 = 0, argv_4 = 0)`, you just want set `argv_4` a new value and leave the others default, you must call like this `func(argv_1_value, argv_4=1)`.

### P71
>* BIFs have their own namespaces called `__builtins__`, and they are alutomatically included in every python program.
>* `range()` returns an iterator.
>* `print("\t", end='')`, including `end=''` as an argument to `print()` switches off its automatic inclusion of a new-line on output.

## 3 files and exceptions -- **Dealing with errors**

### P75
`open()` creates an iterator to feed the lines of data from your file to your code one line at one time.

### P77
`split()` returns a list of strings. See the doc of split with `help(s.split)`.

{% highlight python  %}
>>>s = "aaaaa:bbbbb"
>>>(first, second) = s.split(":")
['aaaaa', 'bbbbb']
>>>help(s.split) 
{% endhighlight %}

### P86
Keyword `not` negates the value, eg `if not a== -1`

### P93
Ignore errors by `pass`.

## 4 persistence -- **Saving data to files**

### P110
Write things to file.
{% highlight python %}
# if you want to use print to file, you must import the following.
from __future__ import print_function
out = open("data", "w")
print("This is the thing to be written.", file=out)
out.close() #flushing
{% endhighlight %}
By default, `print()` use standard output(usually screen), to write data to a file, using the `file` argument to specify the file object.

File access mode:
<table border="1">
    <tr>
        <td>r</td>
        <td>reading (default)</td>
    </tr>
    <tr>
        <td>w</td>
        <td>writing, clear the contents of existing file, or create file, then to write</td>
    </tr>
    <tr>
        <td>w+</td>
        <td>reading & writing</td>
    </tr>
    <tr>
        <td>a</td>
        <td>append</td>
    </tr>
    <tr>
        <td>b</td>
        <td>in binary mode</td>
    </tr>
</table>

### P115
{% highlight python %}
try:
    ...
except :
    ...
finally:
    ...
{% endhighlight %}

### P118
The `locals()` BIF returns a collection of names defined in the current scope.

### P119
print exception object.
{% highlight python %}
try:
    ...
except IOError as err:
    print("File Error: " + str(err))
{% endhighlight %}

### P120
The `with` statement, when used with files, it negates the need to include a `finally` suite to handle the closing of a potentially opened file.
The usual `try/except/finally` pattern:
{% highlight python %}
try:
    data = open('its.txt', 'w')
    print("it's ...", file=data)
except IOError as err:
    print('File error: ' + str(err))
finally:
    if 'data' in locals():
        data.close()
{% endhighlight %}
The use of `with` negates the need for the `finally` suite.
{% highlight python %}
try:
    with open('its.txt', 'w') as data:
        print("it's ...", file=data)
except IOError as err:
    print('File error: ' + str(err))
{% endhighlight %}

### P133
Standard library `pickle` (support only for Python 3, not rigth!!) can save and load almost any python data object. The file must be opened in `b` mode.
{% highlight python %}
import pickle
    ...
with open('mydata.pickle', 'wb') as mysavedata:
    pickle.dumb([1, 2, 'three'], mysavedata)
    ...
with open('mydata.pickle', 'rb') as myrestoredata:
    a_list = pickle.load(myrestoredata)

print(a_list)
{% endhighlight %}

## 5 comprehending data -- **Work that data!**

### P144
Two kinds of sort. By default, they are in ascending order, pass `reverse=True` to order in descending.

* In-place sorting. `sort()`, the original data is lost.
* Copied sorting. `sorted()`, return a sorted copy, the original data is still there.

### P146  <!-- <span class="question"> difference between them????</span> -->
* method chaining. `data.strip().split(',')`, read it from **left to rigth**.
* function chaining. `print(sorted(names))`.Apply a series of functions to your data, each function takes your data and performs some operation on it, then passes the transformed data onto the next function. read from ** right to left**

### P155
List comprehensions. `new_data = [item * 2 for item in data]`.

### P166
`set` data structure, data items in a `set` are unordered and duplicates are not allowed.
{% highlight python %}
#Factory function is used here
dist = set()
dis = {1, 2, 3, "four", 2} #there will be only one 2
dis = set(jame_list)
{% endhighlight %}

## 6 custom data objects -- **Bundling code with data**

### P176 
`pop(0)` returns and removes data from the fornt of a list.

### P180
{% highlight python %}
#create a dictionary
>>>a = {}
>>>b = dict()
>>>type(a)
<class, 'dict'>
>>>a['name'] = 'aaaa'
>>>a['name']
'aaaa'
{% endhighlight %}

### P191
define class:
{% highlight python %}
class Myclass:
    def __init__(self, value=0):
        self.thing = value  #class attribute

a = Myclass() # Myclass().__init__(a)
{% endhighlight %}

**Every method defined in class requires `self` as the first argument.** `self` is used to identify the calling of object instance.

### P206
Inherit from other class.
{% highlight python %}
class Myclass(list):
    def __init__(self, a_name):
        list.__init__([])
        self.name = a_name
{% endhighlight %}

## 7 web development -- Putting it all together

### P224
The standard library `string` module includes a class called `Template` , which supports simple string substitutions.

### P234
~~~~
webapp
|-- cgi-bin
|-- data
|-- images
|-- templates
~~~~

### P235
The standard library `http.server` can be used to build a simple web server in python.
{% highlight python %}
from http.server import HTTPServer, CGIHTTPRequestHandler

port = 8080
httpd = HTTPServer(('', port), CGIHTTPRequestHandler)
print("starting simple_httpd in port: " + str(httpd.server_port))
httpd.server_forever()
{% endhighlight %}

### 238
The standard library `glob` can be used list of filenames.
{% highlight python %}
import glob
files = glob.glob("data/*.txt")
{% endhighlight %}

### P244
Get the form data

{% highlight python  %}
import cgi
form_data = cgi.FieldStorage()
value = form_data['value_name'].value
{% endhighlight %}

### P248
The standard library `cgitb` module, when enabled, can show you CGI coding errors in your browser.
{% highlight python %}
import cgitb
cgitb.enable()
{% endhighlight %}

### P250
`@property`, a decorator that lets arrange for a class method to appear as if it is a class attribute.
{% highlight python %}
@property
def top1(self):
    return sorted(self.score_list)[0]
#This method can be used like print("top 1 " + str(top1))
{% endhighlight %}

## 8 mobile app development -- Small devices
[Scripting Layer for Android(SL4A)](http://code.google.com/p/android-scripting)

### P263
Install and configure Android scripting.
1. Open emulator's or mobile's browser, surt to (http://code.google/com/p/android-scripting).
2. Download and intsall `sl4a_r*.apk`.
3. Download and install `python_for_android_r*.apk`.

### P269
The usage of JSON.
{% highlight python %}
>>> import json
>>> alpha = ['aaa', ['bbb', 'ccc'], 'ddd', ['eee', 'fff', 'ggg']]
>>> alpha
['aaa', ['bbb', 'ccc'], 'ddd', ['eee', 'fff', 'ggg']]
>>> 
>>> to_transfer = json.dumps(alpha)
>>> to_transfer
'["aaa", ["bbb", "ccc"], "ddd", ["eee", "fff", "ggg"]]'
>>> 
>>> from_transfer = json.loads(to_transfer)
>>> from_transfer
[u'aaa', [u'bbb', u'ccc'], u'ddd', [u'eee', u'fff', u'ggg']]
>>> alpha
['aaa', ['bbb', 'ccc'], 'ddd', ['eee', 'fff', 'ggg']]
{% endhighlight %} 

### P291
The `sys` module provides the `sys.stdin`, `sys.stdout`, `sys.stderr` inpurt streams.

## 9 manage your data -- Handling input
### P302
The standard `os` library includes the `environ` dictionary providing convenient access to your program's environment settings.
{% highlight python %}
import os
addr = os.environ['REMOTE_ADDR']
host = os.environ['REMOTE_HOST']
{% endhighlight %}

#### The usage of `sqlite3`.

## 10 scaling your webapp -- Getting real
This chapter talks about how to build your webapp based on GAE.

## 11 dealing with complexity -- Data wrangling
It's about reading data from csv file.