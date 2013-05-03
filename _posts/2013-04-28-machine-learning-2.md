---
layout: post
title: "machine learning 2"
description: "Multiple features(variables)"
category: course 
tags: [ml]
---
{% include JB/setup %}
## Multivariate linear regression

### Notation:

* m = number of training examples
* n = number of features
* $$ x^{(i)} $$ = input(features) of $$ i^{th} $$ training example.
* $$ x_{j}^{(i)} $$ = value of feature $$ j $$ in $$ i^{th} $$ training example.

**Hypothesis**: $$ h_{\theta}(x)=\theta_{0} + \theta_{1}x_{1} + \theta_{2}x_{2} + \cdots  + \theta_{n}x_{n} $$

For convenience of notation, define $$ x_{0}=1 $$.

$$ x=\begin{bmatrix}
x_{0} \\ 
x_{1} \\ 
x_{2} \\ 
\vdots\\ 
x_{n}
\end{bmatrix} \in \mathbb{R}^{n+1}
\ 
\Theta=\begin{bmatrix}
\Theta_{0} \\ 
\Theta_{1} \\ 
\Theta_{2} \\ 
\vdots\\ 
\Theta_{n}
\end{bmatrix} \in \mathbb{R}^{n+1} 
\\
h_{\theta}(x)= \Theta_{0}x_{0} + \Theta_{1}x_{1} + \cdots + \Theta_{n}x_{n}
             = \Theta^{T}x
$$ 

Cost funciton:
$$ J(\theta_{0},\theta_{1},\ldots,\theta_{n})=\frac{1}{2m}\sum_{i=1}^{m} \left ( h_\theta(x^{(i)})-y^{(i)} \right)^2 $$

**Gradient descent:**

Repeat {
$$ \theta_{j} := \theta_{j} - \alpha \frac{\partial}{\partial\theta_{j}}J(\theta_{0},\cdots,\theta_{n}) $$
} (simultaneously update for every $$ j=0, \cdots, n $$)

New algorithm $$ (n \geq 1) $$ :

Repeat {

$$ \theta_{j} := \theta_{j} - \alpha \frac{1}{m}\sum_{i=1}^{m} \left( h_{\theta}(x^{(i)})-y^{(i)} \right) x^{(i)}_{j} $$ }
(simultaneously update $$ \theta_{j} $$ for $$ j=0, \cdots, n $$)

### Gradient Descent in Practice 1 -- Feature Scaling 

#### Feature Scaling
Get every feature into approximately a $$ -1 \le x_i \le 1 $$ range.

#### Mean normalization
Replace $$ x_i $$ with $$ x_i - \mu_i $$ to make features have aproximately zero mean(Do not apply to  $$ x_0 = 1 $$)

$$ x_1 \leftarrow \frac{x_1 - \mu_1}{s_1} $$, $$ \mu_1 $$ is the average value of $$ x_1 $$ in training set, $$ s_1 $$ is the range (max-min) (or standard deviation)

### Gradient Descent in Practice 2 - Learning Rate

#### Gradient descent
$$ \theta_j := \theta_j - \alpha\frac{\partial}{\partial\theta_j}J(\theta) $$

1. "Debugging": how to make sure gradient descent is working correctly
2. How to choose learning rate $$ \alpha $$.

Making sure gradient descent is working correctly

* For sufficiently small $$ \alpha, J(\theta) $$ should decrease on every iteration
* Buf if $$ \alpha $$ is too small, gradient descent can be slow to converge.

**Summary**

* if $$ \alpha $$ is too small: slow convergence.
* if $$ \alpha $$ is too large: $$ J(\theta) $$ may not decrease on every iteration;may not converge.

To choose $$ \alpha $$, try $$ \ldots, 0.001, 0.003, 0.01, 0.03, 0.1, 0.3, 1, \ldots $$ 

### Features and Polynomial（多项式的） Regression

#### Polynomial Regression

$$ h_\theta(x)=\theta_0 + \theta_1(size) + \theta_2(size)^2 \\
   h_\theta(x)=\theta_0 + \theta_1(size) + \theta_2\sqrt{(size)} $$
   
### Normal Equation
Normal Equation: Method to solve for $$ \theta $$ analytically.

$$ \theta \in \mathbb{R}^{n+1} \  
J(\theta_{0},\theta_{1},\ldots,\theta_{n})=\frac{1}{2m}\sum_{i=1}^{m} \left ( h_\theta(x^{(i)})-y^{(i)} \right)^2 $$

$$ \frac{\partial}{\partial\theta_j}J(\theta) = \ldots = 0 \textbf{for every } j \\
\textbf{Solve for } \theta_0, \theta_1, \ldots, \theta_n
$$

$$ \theta = \left( X^TX \right)^{-1}X^Ty $$

$$ 
m \textbf{ examples }  \left( x^{(1)}, y^{(1)} \right),\ldots, \left( x^{(m)}, y^{(m)} \right) \textbf{;} n \textbf{ features.}
\\
x^{(i)} = \begin{bmatrix} 
x_0^{(i)} \\
x_1^{(i)} \\
x_2^{(i)} \\
\vdots \\
x_n^{(i)} 
\end{bmatrix} \in \mathbb{R}^{n+1} \hspace{15 mm}
\underset{design \ matrix}{\operatorname{X}} = \begin{bmatrix}
\cdots & \left( x^{(1)}\right )^T & \cdots \\
\cdots & \left( x^{(2)}\right )^T & \cdots \\
\vdots & \vdots & \vdots \\
\cdots & \left( x^{(n)}\right )^T & \cdots \\
\end{bmatrix}
\\
X=\begin{bmatrix} 
1 & x_1^{(1)} \\
1 & x_2^{(1)} \\
1 & x_3^{(1)} \\
\vdots & \vdots \\
1 & x_m^{(1)} \\
\end{bmatrix} \hspace{20 mm} 
y= \begin{bmatrix} p
y^{(1)}\\
y^{(2)}\\
y^{(3)}\\
\vdots \\
y^{(m)}\\
\end{bmatrix}
$$

**summary**

m training examples, n features.

Gradient Descent:

* Need to choose $$ \alpha $$
* Needs many iterations.
* Works weel even when n is large.

Normal Equation:

* No need to choose $$ \alpha $$
* Don't need to iterate.
* Need to compute $$ \left( X^TX \right)^{-1} $$
* Slow if n is very large

when $$ n = 10^6 $$, we should use gradient descent, and when n is smaller than that, we can use normal equation.

### Normal Equation Noninvertibility
What if $$ X^TX $$ is non-invertible?

* Redundant features(linearly dependent)
* Too many features(e.g. $$ m \leq n $$) -
   Delete some features, or use regularization.