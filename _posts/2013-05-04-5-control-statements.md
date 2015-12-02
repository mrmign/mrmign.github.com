---
layout: post
title: "5. Control Statements, Functions, Vectorization"
description: "octave"
category: course
tags: [ml, octave]
---

## Control statements: for, while, if statements

{% highlight octave %}
v = zeros(10,1);
for i=1:10, 
    v(i) = 2^i;
end
% Can also use "break" and "continue" inside for and while loops to control execution.

i = 1;
while i <= 5,
  v(i) = 100; 
  i = i+1;
end

i = 1;
while true, 
  v(i) = 999; 
  i = i+1;
  if i == 6,
    break;
  end;
end

if v(1)==1,
  disp('The value is one!');
elseif v(1)==2,
  disp('The value is two!');
else
  disp('The value is not one or two!');
end
{% endhighlight %}

## Functions
To create a function, type the function code in a text editor (e.g. gedit or notepad), and save the file as "functionName.m"

Example function:
{% highlight octave %}
function y = squareThisNumber(x)

y = x^2;
{% endhighlight %}

To call the function in Octave, do either:

1) Navigate to the directory of the functionName.m file and call the function:
{% highlight octave %}
% Navigate to directory:
    cd /path/to/function

    % Call the function:
    functionName(args)
{% endhighlight %}
2) Add the directory of the function to the load path and save it:
{% highlight octave %}
% To add the path for the current session of Octave:
    addpath('/path/to/function/')

    % To remember the path for future sessions of Octave, after executing addpath above, also do:
    savepath
    
{% endhighlight %}

## Vectorization
Vectorization is the process of taking code that relies on loops and converting it into matrix operations. It is more efficient, more elegant, and more concise.

As an example, let's compute our prediction from a hypothesis. Theta is the vector of fields for the hypothesis and x is a vector of variables.

With loops:
{% highlight octave %}
prediction = 0.0;
for j = 1:n+1,
  prediction += theta(j) * x(j);
end;
{% endhighlight %}

With vectorization:
{% highlight octave %}
prediction = theta' * x;
{% endhighlight %}
If you recall the definition multiplying vectors, you'll see that this one operation does the element-wise multiplication and overall sum in a very concise notation.

>When you're working in one directory, you can use`addpath(pwd)` to add current directory to octave's search path.