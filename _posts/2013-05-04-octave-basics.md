---
layout: post
title: "1.Octave basics"
description: "This is the use of octave."
category: course
tags: [ml, octave]
---
{% include JB/setup %}

### Basic Operations

{% highlight octave %}
octave:2>  PS1('>> ');
>> a = 3
a =  3
>> a = 3; % semlicolon superss
>> a=3
a =  3
>> a=3;
>> a
a =  3
>> a=pi;
>> a
a =  3.1416
>> disp(a)
 3.1416
>> disp(sprintf("%0.2f",a))
3.14
>> format long
>> a
a =  3.14159265358979
>> format short
>> a
a =  3.1416
>> A=[1 2; 3 4; 5 6]
A =

   1   2
   3   4
   5   6

>> a = [1 2;
> 3 4;
> 5 6]
a =

   1   2
   3   4
   5   6

>> v = [1 2 3]
v =

   1   2   3

>> v =[1; 2; 3]
v =

   1
   2
   3

>> v = 1:0.1:2
v =

 Columns 1 through 7:

    1.0000    1.1000    1.2000    1.3000    1.4000    1.5000    1.6000

 Columns 8 through 11:

    1.7000    1.8000    1.9000    2.0000

>> v =1:6
v =

   1   2   3   4   5   6

>> ones(2,3)
ans =

   1   1   1
   1   1   1

>> w = ones(1,3)
w =

   1   1   1

>> w = zeros(1,3)
w =

   0   0   0

>> w = rand(1,3)
w =

   0.713368   0.273003   0.038422

>> rand(3,3)
ans =

   0.54012   0.21376   0.83726
   0.78187   0.39773   0.64907
   0.44332   0.47828   0.88306

>> rand(3,3)
ans =

   0.253882   0.359688   0.444935
   0.068178   0.960570   0.580992
   0.677249   0.375301   0.844699

>> rand(3,3)
ans =

   0.54693   0.56135   0.70687
   0.63751   0.34712   0.69665
   0.48635   0.64882   0.64993

>> randn(1,3)
ans =

   0.22759  -0.74945  -0.32080

>> randn(1,3)
ans =

   0.31565  -0.36675  -0.63792

>> w = -6 + sqrt(10)*(randn(1,10000))
warning: broken pipe -- some output may be lost
>> hist(w)
>> hist(w,50)
>> eye(4)
ans =

Diagonal Matrix

   1   0   0   0
   0   1   0   0
   0   0   1   0
   0   0   0   1

>> help eye
>> help rand
>> 
{% endhighlight %}