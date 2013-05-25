---
layout: post
title: "5 Neural Networks: Learning"
description: ""
category: course 
tags: [ml]
---
{% include JB/setup %}

## Cost Function

**Notation**

* L = total no. of layers in network
* $$ s_l $$ no. of units(not counting bias unit) in layer l

**Binary classification**

y=0 or 1, just 1 output unit

$$ h_\theta(x) \in \mathbb{R} $$

**Multi-class classification** (k classes)

$$ y\in \mathbb{R}^K, $$ k output units,($$ k \geq 3 $$)

$$ h_\theta(x) \in \mathbb{R} $$

### cost function

**Logistic regression**

$$
J(\theta) = -\frac{1}{m} \left [ \sum_{i=1}^m y^{(i)}\log h_\theta(x^{(i)})+(1-y^{(i)})\log(1-h_\theta(x^{(i)})) \right ] + \frac{\lambda}{2m}\sum_{j=1}^n\theta_j^2
$$

**Neural network**

$$
h_\Theta(x) \in \mathbb{R}^K  \ (h_\Theta(x))_i = i^{th} \textrm{ output}
$$

$$
J(\Theta) = -\frac{1}{m} \left [ \sum_{i=1}^m \sum_{k=1}^K y_k^{(i)} \log(h_\Theta(x^{(i)}))_k + (1-y_k^{(i)})\log(1-(h_\Theta(x^{(i)}))_k) \right ] + \frac{\lambda}{2m}\sum_{l=1}^{L-1} \sum_{i=1}^{s_l} \sum_{j=1}^{s_l + 1}(\Theta_{ji}^{(l)})^2
$$

## Backpropagation algorithm

**Gradient computation**

>Need code to comput:

* $$ J(\Theta) $$
* $$ \frac{\partial}{\partial \Theta_{ij}^{(l)}} J(\Theta)  \ \ \ \Theta_{ij}^{(l)} \in \mathbb{R}$$

>Forward propagaton:(presume there are 4 layers)

$$
\begin{align*}
&a^{(1)} = x \\
&z^{(2)} = \Theta^{(1)}a^{(1)} \\
&a^{(2)} = g(z^{(2)}) \ \ (add \ \ a_0^{(2)}) \\
&z^{(3)} = \Theta^{(2)}a^{(2)} \\
&a^{(3)} = g(z^{(3)}) \ \ (add \ \ a_0^{(3)}) \\
&z^{(4)} = \Theta^{(3)}a^{(3)} \\
&a^{(4)} = h_\Theta(x) = g(z^{(4)})
\end{align*}
$$

>Backpropagation algorithm

Intuition: $$ \delta_j^{(l)}  $$ = "error" of node $$ j $$ in layer $$ l $$.

For each output unit(layer L=4)

$$
\begin{align*}
&\delta_j^{(4)} = a_j^{(4)} - y_j \\
\\
&\delta^{(3)} = (\Theta^{(3)})^T \delta^{(4)} .* {g}'(z^{(3)}) \\
&\delta^{(2)} = (\Theta^{(2)})^T \delta^{(3)} .* {g}'(z^{(2)}) \\
&{g}'(z^{(3)}) = a^{(3)} .* (1 - a^{(3)}) \\
&{g}'(z^{(2)}) = a^{(2)} .* (1 - a^{(2)}) \\
\end{align*}
$$

**ATTENTION:**

There is no $$ \delta^{(1)} $$.

$$ \frac{\partial}{\partial \Theta_{ij}^{(l)}} J(\Theta) = a_j^{(l)}\delta_i^{(l+1)} $$

(Ignore $$ \lambda $$ if $$ \lambda = 0 $$)

The other part can be found [here](/files/5 nueral networks: learning.pdf)