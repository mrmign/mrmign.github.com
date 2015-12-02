---
layout: post
title: "3 Logic Regression and Regularization"
description: "logic regression and regularization"
category: course 
tags: [ml]
---

# Logistic Regression

## Classification

$$ y \in {0, 1} $$

* 0: "Negative Class"
* 1: "Positive Class"

Threshold classifier output $$ h_\theta(x) $$ at o.5:

* if $$ h_\theta(x) \geq 0.5 $$, predict "y = 1"
* if $$ h_\theta(x) < 0.5 $$, predict "y = 0"

Classification:  **y = 0 or 1**

$$ h_\theta(x) $$ can be > 1 or < 0

Logistic Regression: $$ 0 \leq h_\theta(x) \leq 1 $$

## Hypothesis Representation

**Logistic Regresssion Model**

Want $$ 0 \leq h_\theta(x) \leq 1 $$

$$ h_\theta(x) = g(\theta^Tx) \\
g(z)=\frac{1}{1+e^{-z}} \\
z = \theta^Tx $$

>`g(z)`always lies between 0 and 1.


`g(z)` is called *Sigmoid function* or *Logistic function*

## Descision Boundary

* Predict "y=1" if $$ \theta^T \geq 0 $$ or $$ h_\theta(x) \geq 0.5 $$
* Predict "y=0" if $$ \theta^T < 0 $$ or $$ h_\theta(x) < 0.5 $$

## Cost Function

Training examples:

$$ 
\left [ 
\begin{array}{rrrr}
x_0 \\
x_1 \\
\ldots \\
x_n
\end{array}
 \right ],

x_0 = 1, y \in\{ 0, 1\}
$$

**Logistic regression Cost function**

$$
Cost(h_\theta(x),y) =\left\{
\begin{array}{rcl}
-\log (h_\theta(x)) & \mbox{if} & y = 1 \\
-\log (1 - h_\theta(x)) & \mbox{if} & y = 0
\end{array}
\right.
$$

>**Notice:** In the formula above, the *dot* in the end can't be omitted!!!


>The hypothesis will now be more accurate (or at least just as accurate) with new features, so the cost function will decrease.


>The cost function J(θ) is guaranteed to be convex for logistic regression.

## Simplifiled Cost Function and Gradient Descent

$$ 
J(\theta) = \frac{1}{m}\sum_{i=1}^{m}Cost(h_\theta(x^{(i)}),y^{(i)})
$$

The $$ Cost(h_\theta(x),y) $$ Can be written in the below form:

$$
Cost(h_\theta(x),y) = -y\log(h_\theta(x)) - (1-y)\log(1-h_\theta(x))
$$

$$
\begin{eqnarray}
J(\theta) &=& \frac{1}{m}\sum_{i=1}^{m}Cost(h_\theta(x^{(i)}),y^{(i)})  \nonumber \\
          &=& -\frac{1}{m} \sum_{i=1}^{m} \left [ y^{(i)}\log(h_\theta(x^{(i)})) - (1-y^{(i)})\log(1-h_\theta(x^{(i)}))  \right ]

\end{eqnarray}
$$

Want $$ min_\theta J(\theta) $$:

**Gradient Descent:**

Repeat {

$$
\begin{eqnarray}
 \theta_j &:=& \theta_j - \alpha\frac{\partial}{\partial\theta_j} J(\theta)     \nonumber \\
   &:=& \theta_j - \alpha\sum_{i=1}^{m}(h_\theta(x^{(i)}) - y^{(i)})x_j^{(i)}
\end{eqnarray}
$$

}

$$
\frac{\partial}{\partial\theta_j} J(\theta) = \frac{1}{m}\sum_{i=1}^{m}(h_\theta(x^{(i)}) - y^{(i)})x_j^{(i)}
$$

## Advanced Optimization

{% highlight octave %}
options = optimset('GradObj', 'on', 'MaxIter', '100');
initialTheta = zeros(2,1);
[optTheta, functionVal, exitFlag] ...
    = fminunc(@costFunction, initialTheta, options);

funciton [jVal, gradient] = costFunction(theta)
    jVal = [code to comput J(θ)];
    gradient(1) = [code to compute ∂/∂θ1J(θ)];
    .
    .
    gradient(n+1) = [code to compute ∂/∂θnJ(θ)];
{% endhighlight %}


## Multiclass Classification: One-vs-all

Train a logistic regression classifier $$ h_\theta^{(i)}(x) $$ for each class $$ i $$ to predict the probability that $$ y = i $$ .

$$ h_\theta^{(i)}(x) = P(y=i \vert x;\theta) \ (i=1,2,3,...) $$


# Regularization

## The problem of Overfitting

**Overfitting:** If we have too many features, the learned hypothesis may fit the training set very well, but fail to generalize to new examples.

**Addressing overfitting:**

Options:

1. Reduce number of features.
    * Manually select which features to keep
    * Model selection algorithm

2. Regularization
    * Keep all the features, but reduce magnitude/values of parameters $$ \theta_j $$
    * Works well when we have a lot of features, each of which contributes a bit to predicting y.


>By adding a new feature, our model must be more (or just as) expressive, thus allowing it learn more complex hypotheses to fit the training set.

>Adding many new features gives us more expressive models which are able to better fit our training set. If too many new features are added, this can lead to overfitting of the training set.

## Cost Funciton

$$
J(\theta)=\frac{1}{2m}\left [ \sum_{i=1}^{m}\left(h_\theta(x^{(i)}) - y^{(i)}\right)^2 + \lambda\sum_{j=1}^{n}\theta_j^2 \right ]
$$

## Regularized Linear Regression

$$
J(\theta)=\frac{1}{2m}\left [ \sum_{i=1}^{m}\left(h_\theta(x^{(i)}) - y^{(i)}\right)^2 + \lambda\sum_{j=1}^{n}\theta_j^2 \right ]
$$

Gradient descent:

Repeat {

$$
\theta_0 := \theta_0 - \alpha\frac{1}{m}\sum_{i=1}^{m}\left(h_\theta(x^{(i)}) - y^{(i)} \right )x_0^{(i)}  \\

\theta_j := \theta_j - \alpha \left[\frac{1}{m}\sum_{i=1}^{m}\left(h_\theta(x^{(i)}) - y^{(i)} \right )x_j^{(i)} -\frac{\lambda}{m}\theta_j \right ] \ (j=1,2,3\ldots)
$$

}

$$
\theta_j := \theta_j(1-\alpha\frac{\lambda}{m}) - \alpha \frac{1}{m}\sum_{i=1}^{m}\left(h_\theta(x^{(i)}) - y^{(i)} \right )x_j^{(i)} \ (j=1,2,3\ldots)
$$

## Regularized Logistic Regression

$$
J(\theta)=-\frac{1}{m} \sum_{i=1}^{m} \left [ y^{(i)}\log(h_\theta(x^{(i)})) - (1-y^{(i)})\log(1-h_\theta(x^{(i)}))  \right ]
$$

Gradient descent:

Repeat {

$$
\theta_0 := \theta_0 - \alpha\frac{1}{m}\sum_{i=1}^{m}\left(h_\theta(x^{(i)}) - y^{(i)} \right )x_0^{(i)}  \\

\theta_j := \theta_j - \alpha \left[\frac{1}{m}\sum_{i=1}^{m}\left(h_\theta(x^{(i)}) - y^{(i)} \right )x_j^{(i)} -\frac{\lambda}{m}\theta_j \right ] \ (j=1,2,3\ldots)
$$

}