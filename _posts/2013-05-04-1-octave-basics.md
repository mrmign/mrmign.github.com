---
layout: post
title: "1. Octave basics"
description: "This is the use of octave."
category: course
tags: [ml, octave]
---
{% include JB/setup %}

### Basic Operations

{% highlight octave %}
octave:1>%% Change working directory in windows example: 
octave:1>%% Note that it uses normal slashes and does not uses escape characters for the empty spaces.
octave:1> cd ../
octave:2> ls
Learning From Data 2nd Ed (Wiley,2007).pdf
Line Regression with multiple variables week 2.pdf
octave
Supervised and Unsupervised Learning.pdf
octave:3> pwd
ans = /home/arming/coursera/machinelearning
octave:4> cd octave
octave:5> pwd
ans = /home/arming/coursera/machinelearning/octave
octave:6> PS1('>> ') % Change Octave prompt
>>%% elementary operations
>> 5 + 6
ans =  11
>> 3 -2 
ans =  1
>> 5*8
ans =  40
>> 1/2
ans =  0.50000
>> 2^6
ans =  64
>> 1 == 2  % false
ans = 0
>> 1 ~= 2  % true.  note, not "!="
ans =  1
>> 1 && 0
ans = 0
>> 1 || 0
ans =  1
>> xor(1,0)
ans =  1
>>%% variable assignment
>> a =3; % semicolon suppresses output
a =  3
>> b ='hi'
b = hi
>> c = 3 >= 1
c =  1
>>% Displaying them:
>> a = pi
a =  3.1416
>> disp(a)
 3.1416
>> disp(sprintf('2 decimals: %0.2f', a))
2 decimals: 3.14
>> disp(sprintf('6 decimals: %0.6f', a))
6 decimals: 3.141593
>> format long 
>> a
a =  3.14159265358979
>> format short
>> a
a =  3.1416
>>%%  vectors and matrices
>> A = [1 2; 3 4; 5 6]
A =

   1   2
   3   4
   5   6

>> v = [1 2 3]
v =

   1   2   3

>> v = [1:0.1:2] % from 1 to 2, with stepsize of 0.1. Useful for plot axes
v =

 Columns 1 through 8:

   1.0000   1.1000   1.2000   1.3000   1.4000   1.5000   1.6000   1.7000

 Columns 9 through 11:

   1.8000   1.9000   2.0000

>> v = 1:6 % from 1 to 6, assumes stepsize of 1 (row vector)
v =

   1   2   3   4   5   6

>> C = 2*ones(2,3)  % same as C = [2 2 2; 2 2 2]
C =

   2   2   2
   2   2   2

>> w = ones(1,3) % 1x3 vector of ones
w =

   1   1   1

>> w = rand(1,3) % drawn from a uniform distribution 
w =

   0.64276   0.75107   0.87499

>> w = randn(1,3) % drawn from a normal distribution (mean=0, var=1)
w =

   0.26606  -1.05041   1.34285

>> w = -6 + sqrt(10)*(randn(1,10000)) % (mean = -6, var = 10)
warning: broken pipe -- some output may be lost
>> hist(w) % plot histogram using 10 bins (default)
>> hist(w,5) % plot histogram using 50 bins
>> I = eye(4) % 4x4 identity matrix
I =

Diagonal Matrix

   1   0   0   0
   0   1   0   0
   0   0   1   0
   0   0   0   1
>>
>>% help function
>> help eye 
>> help rand
>> help help
 
{% endhighlight %}