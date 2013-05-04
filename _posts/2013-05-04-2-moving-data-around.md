---
layout: post
title: "2. Moving Data Around"
description: "Octave"
category: course
tags: [ml, octave]
---
{% include JB/setup %}

{% highlight octave %}
>>%% dimensions
>> sz=size(A) % 1x2 matrix: [(number of rows) (number of columns)]
sz =

   3   2

>> size(A,1) % number of rows
ans =  3
>> size(A,2) % number of cols
ans =  2
>> length(v) % size of longest dimension
ans =  6 
>> pwd % show current directory (current path)
ans = /home/arming/coursera/machinelearning/octave
>>%% loading data
>> load q1x.dat  % alternatively, load('q1y.dat')
>> load q1y.dat 
>> who % list variables in workspace
Variables in the current scope:

A    C    I    a    ans  b    c    q1x   q1y  sz   v    w

>> whos % list variables in workspace (detailed view) 
Variables in the current scope:

  Attr Name        Size                     Bytes  Class
  ==== ====        ====                     =====  ===== 
       A           3x2                         48  double
       C           2x3                         48  double
       I           4x4                         32  double
       a           1x1                          8  double
       ans         1x44                        44  char
       b           1x2                          2  char
       c           1x1                          1  logical
       q1x        10x2                        160  double
       q1y         9x3                        216  double
       sz          1x2                         16  double
       v           1x6                         24  double
       w           1x10000                  80000  double

Total is 10131 elements using 80599 bytes

>> clear q1y % clear w/ no argt clears all
>> whos
Variables in the current scope:

  Attr Name        Size                     Bytes  Class
  ==== ====        ====                     =====  ===== 
       A           3x2                         48  double
       C           2x3                         48  double
       I           4x4                         32  double
       a           1x1                          8  double
       ans         1x44                        44  char
       b           1x2                          2  char
       c           1x1                          1  logical
       q1x        10x2                        160  double
       sz          1x2                         16  double
       v           1x6                         24  double
       w           1x10000                  80000  double

Total is 10104 elements using 80383 bytes
>> v = q1x(1:5) % first 5 elements of q1x (counts down the columns)
v =

   1   2   3   4   5

>> save hello v; % save variable v into file hello.mat
>> ls % list files in current directory 
hello  q1x.dat	q1y.dat
>> save hello.txt v -ascii; % save as ascii
>>% fopen, fread, fprintf, fscanf also work  [[not needed in class]]
>>%% indexing
>> A(3,2) % indexing is (row,col)
ans =  6
>> A
A =

   1   2
   3   4
   5   6

>> A(2,:) % get the 2nd row. 
          % ":" means every element along that dimension
ans =

   3   4

>> A(:,2) % get the 2nd col
ans =

   2
   4
   6

>> A([1 3],:) % print all  the elements of rows 1 and 3
ans =

   1   2
   5   6
>>A(;,2) = [10; 11; 12] % change second column
A =

     1     10
     3     11
     5     12

>> A = [A, [100; 101; 102]] % append column vec
A =

     1     2   100
     3     4   101
     5     6   102

>> A
A =

     1     2   100
     3     4   101
     5     6   102

>> A(:) % Select all elements as a column vector.
ans =

     1
     3
     5
     2
     4
     6
   100
   101
   102
>>% Putting data together 
>> A = [1 2; 3 4; 5 6]
A =

   1   2
   3   4
   5   6

>> B = [11 12; 13 14; 15 16]
B =

   11   12
   13   14
   15   16

>> c = [A B]
c =

    1    2   11   12
    3    4   13   14
    5    6   15   16

>> C = [A; B]
C =

    1    2
    3    4
    5    6
   11   12
   13   14
   15   16

>> C = [B A]
C =

   11   12    1    2
   13   14    3    4
   15   16    5    6

>> C = [B; A]
C =

   11   12
   13   14
   15   16
    1    2
    3    4
    5    6

>> 

{% endhighlight %}