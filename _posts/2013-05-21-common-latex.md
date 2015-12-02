---
layout: post
title: "common latex"
description: ""
category: tool
tags: [latex]
---

## LaTeX – Multiline equations, systems and matrices

### Multiline Equations

You can present equations with several lines, using the array statement. Inside its declaration you must :

* Define the number of columns
* Define column alignment
* Define column indentation
* Indicate column separator with & symbol &

Example: `{lcr}` means: 3 columns with indentations respectively left, center and right.

{% highlight latex %}
\begin{array}{lcl} z & = & a \\ f(x,y,z) & = & x + y + z \end{array}
{% endhighlight %}

$$ \begin{array}{lcl} z & = & a \\ f(x,y,z) & = & x + y + z \end{array} $$


{% highlight latex %}
\begin{array}{rcr} z & = & a \\ f(x,y,z) & = & x + y + z \end{array}
{% endhighlight %}

$$ \begin{array}{rcr} z & = & a \\ f(x,y,z) & = & x + y + z \end{array} $$

{% highlight latex %}
\begin{array}{rcl} f: R^3 & \to & R \\ (x,y,z) & \to & x + y + z \\ f(x,y,z) & = & x + y + z \end{array}
{% endhighlight %}

$$\begin{array}{rcl} f: R^3 & \to & R \\ (x,y,z) & \to & x + y + z \\ f(x,y,z) & = & x + y + z \end{array}  $$

{% highlight latex %}
\begin{array} {lcl} f(x) & = & (a+b)^2 \\ & = & a^2+2ab+b^2 \end{array}
{% endhighlight %}

$$ \begin{array} {lcl} f(x) & = & (a+b)^2 \\ & = & a^2+2ab+b^2 \end{array} $$

### Case definitions

Used when a definition have two or more cases. Use the case statement. Notice that the spaces after the instances of if were included inside the mbox declarations.


{% highlight latex %}
f(n) = \begin{cases} n/2, & \mbox{if } n\mbox{ is even} \\ 3n+1, & \mbox{if } n\mbox{ is odd} \end{cases}
{% endhighlight %}

$$ f(n) = \begin{cases} n/2, & \mbox{if } n\mbox{ is even} \\ 3n+1, & \mbox{if } n\mbox{ is odd} \end{cases}  $$

### Simultaneous Equations

Here we have a very simple application of the case statement.

{% highlight latex %}
\begin{cases} 3x + 5y + z \\ 7x – 2y + 4z \\ -6x + 3y + 2z \end{cases}
{% endhighlight %}

$$ \begin{cases} 3x + 5y + z \\ 7x – 2y + 4z \\ -6x + 3y + 2z \end{cases} $$

### Matrices

Matrices can be assembled by using the array statement, like in this example:

{% highlight latex %}
\left| \begin{array}{cc} x_{11} & x_{12} \\ x_{21} & x_{22} \end{array} \right|
{% endhighlight %}

$$ \left \| \begin{array}{cc} x_{11} & x_{12} \\ x_{21} & x_{22} \end{array} \right \| $$


Matrix frames are provided by \left and \right. If you suppress these statements, it will be displayed like:

{% highlight latex %}
\begin{array}{cc} A & B \\ C & D \end{array}
{% endhighlight %}

$$ \begin{array}{cc} A & B \\ C & D \end{array} $$

However, there is another statement, the matrix declaration, slightly easier to use:
{% highlight latex %}
\begin{matrix} x & y \\ z & v \end{matrix}
{% endhighlight %}

$$\begin{matrix} x & y \\ z & v \end{matrix}  $$

The frames of the matrix can be displayed in several forms, by just changing the matrix declaration to vmatrix, Vmatrix, bmatrix, Bmatrix or pmatrix, as shown ahead:
{% highlight latex %}
\begin{vmatrix} x & y \\ z & v \end{vmatrix}
{% endhighlight %}

$$ \begin{vmatrix} x & y \\ z & v \end{vmatrix} $$

{% highlight latex %}
\begin{Vmatrix} x & y \\ z & v \end{Vmatrix}
{% endhighlight %}

$$\begin{Vmatrix} x & y \\ z & v \end{Vmatrix}  $$

{% highlight latex %}
\begin{bmatrix} x & y \\ z & v \end{bmatrix}
{% endhighlight %}

$$\begin{bmatrix} x & y \\ z & v \end{bmatrix}  $$

{% highlight latex %}
\begin{Bmatrix} x & y \\ z & v \end{Bmatrix}
{% endhighlight %}

$$ \begin{Bmatrix} x & y \\ z & v \end{Bmatrix} $$

{% highlight latex %}
\begin{pmatrix} x & y \\ z & v \end{pmatrix}
{% endhighlight %}

$$ \begin{pmatrix} x & y \\ z & v \end{pmatrix} $$

{% highlight latex %}
\begin{bmatrix} 0 & \cdots & 0 \\ \vdots & \ddots & \vdots \\ 0 & \cdots & 0 \end{bmatrix}
{% endhighlight %}

$$ \begin{bmatrix} 0 & \cdots & 0 \\ \vdots & \ddots & \vdots \\ 0 & \cdots & 0 \end{bmatrix} $$

{% highlight latex %}
\left[ \begin{array}{c} x_1 \\ x_2 \end{array} \right] = \begin{bmatrix} A & B \\ C & D \end{bmatrix} \times \left[ \begin{array}{c} y_1 \\ y_2 \end{array} \right]
{% endhighlight %}

$$ \left[ \begin{array}{c} x_1 \\ x_2 \end{array} \right] = \begin{bmatrix} A & B \\ C & D \end{bmatrix} \times \left[ \begin{array}{c} y_1 \\ y_2 \end{array} \right] $$

{% highlight latex %}
\begin{bmatrix} xz & xw \\ yz & yw \end{bmatrix} = \left[ \begin{array}{c} x \\ y \end{array} \right] \times \left[ \begin{array}{cc} z & w \end{array} \right]
{% endhighlight %}

$$ \begin{bmatrix} xz & xw \\ yz & yw \end{bmatrix} = \left[ \begin{array}{c} x \\ y \end{array} \right] \times \left[ \begin{array}{cc} z & w \end{array} \right] $$
