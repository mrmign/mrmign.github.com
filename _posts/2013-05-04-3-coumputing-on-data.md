---
layout: post
title: "3. coumputing on data"
description: "octave"
category: course
tags: [ml, octave]
---

{% highlight octave %}
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

>> c = [1 1; 2 2]
c =

   1   1
   2   2

>>%% matrix operations
>> A*B
error: operator *: nonconformant arguments (op1 is 3x2, op2 is 3x2)
>> C = [1 1; 2 2]
C =

   1   1
   2   2

>> A*C  % matrix multiplication
ans =

    5    5
   11   11
   17   17

>> A .* B % element-wise multiplcation A(i,i)*B(i,i)
          % A .* C  or A * B gives error - wrong dimensions
ans =

   11   24
   39   56
   75   96

>> A .^ 2 % element-wise square of each element in A
ans =

    1    4
    9   16
   25   36

>> v = [1; 2; 3]
v =

   1
   2
   3

>> 1 ./ v % element-wise reciprocal
ans =

   1.00000
   0.50000
   0.33333

>> 1 ./ A
ans =

   1.00000   0.50000
   0.33333   0.25000
   0.20000   0.16667

>> log(v) % functions like this operate element-wise on vecs or matrices 
ans =

   0.00000
   0.69315
   1.09861

>> exp(v)
ans =

    2.7183
    7.3891
   20.0855

>> v
v =

   1
   2
   3

>> abs(v)
ans =

   1
   2
   3

>> abs([-1; 2; -3])
ans =

   1
   2
   3

>> -v  % -1*v
ans =

  -1
  -2
  -3

>> -1 * v
ans =

  -1
  -2
  -3

>> v + ones(length(v),1) % v + 1
ans =

   2
   3
   4

>> length(v)
ans =  3
>> v + 1
ans =

   2
   3
   4

>> A
A =

   1   2
   3   4
   5   6
 
>> A'  % matrix transpose
ans =

   1   3   5
   2   4   6

>> (A')'
ans =

   1   2
   3   4
   5   6

>>%% misc useful functions
>> a = [1 15 2 0.5]
a =

    1.00000   15.00000    2.00000    0.50000

>> val = max(a)
val =  15
>> [val, ind] = max(a) % val -  maximum element of the vector a and index - index value where maximum occur
val =  15
ind =  2
>> max(A) % if A is matrix, returns max from each column
ans =

   5   6

>> a
a =

    1.00000   15.00000    2.00000    0.50000

>> a < 3
ans =

   1   0   1   1

>> find(a < 3)
ans =

   1   3   4

>> A = magic(3)
A =

   8   1   6
   3   5   7
   4   9   2

>> [r,c ] = find(A > 7)
r =

   1
   3

c =

   1
   2

>> [r,c ] = find(A >= 7) % row, column indices for values matching comparison
r =

   1
   3
   2

c =

   1
   2
   3

>>% sum, prod
>> a
a =

    1.00000   15.00000    2.00000    0.50000

>> sum(a)
ans =  18.500
>> prod(a)
ans =  15
>> floor(a)
ans =

    1   15    2    0

>> ceil(a)
ans =

    1   15    2    1

>> rand(3)
ans =

   0.31868   0.91598   0.51921
   0.96554   0.27133   0.35385
   0.42620   0.32065   0.18019

>> max(rand(3), rand(3))
ans =

   0.46646   0.97470   0.11691
   0.96954   0.98368   0.91132
   0.56436   0.16409   0.55678

>> A
A =

   8   1   6
   3   5   7
   4   9   2

>> max(A, [], 1)
ans =

   8   9   7

>> max(A, [], 2)
ans =

   8
   7
   9

>> max(A)
ans =

   8   9   7

>> max(max(A))
ans =  9
>> A(:)
ans =

   8
   3
   4
   1
   5
   9
   6
   7
   2

>> max(A(:))
ans =  9
>> A = magic(9)
A =

   47   58   69   80    1   12   23   34   45
   57   68   79    9   11   22   33   44   46
   67   78    8   10   21   32   43   54   56
   77    7   18   20   31   42   53   55   66
    6   17   19   30   41   52   63   65   76
   16   27   29   40   51   62   64   75    5
   26   28   39   50   61   72   74    4   15
   36   38   49   60   71   73    3   14   25
   37   48   59   70   81    2   13   24   35

>> sum(A,1)
ans =

   369   369   369   369   369   369   369   369   369

>> sum(A,2)
ans =

   369
   369
   369
   369
   369
   369
   369
   369
   369

>> eye(9)
>> 
>> eye(9)
>> A .* eye(9)
ans =

   47    0    0    0    0    0    0    0    0
    0   68    0    0    0    0    0    0    0
    0    0    8    0    0    0    0    0    0
    0    0    0   20    0    0    0    0    0
    0    0    0    0   41    0    0    0    0
    0    0    0    0    0   62    0    0    0
    0    0    0    0    0    0   74    0    0
    0    0    0    0    0    0    0   14    0
    0    0    0    0    0    0    0    0   35

>> sum(sum(A.*eye(9)))
ans =  369
>> sum(sum(A.*flipup(eye(9))))
error: `flipup' undefined near line 127 column 12
error: evaluating argument list element number 1
error: evaluating argument list element number 1
error: evaluating argument list element number 1
error: evaluating argument list element number 1
>> sum(sum(A.*flipud(eye(9))))
ans =  369
>> flipud(eye(9))
>> A = magic(3)
A =

   8   1   6
   3   5   7
   4   9   2

>>% Matrix inverse (pseudo-inverse) 
>> pinv(A)   % inv(A'*A)*A'
ans =

   0.147222  -0.144444   0.063889
  -0.061111   0.022222   0.105556
  -0.019444   0.188889  -0.102778

>> 

{% endhighlight %}
