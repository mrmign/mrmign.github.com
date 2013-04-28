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