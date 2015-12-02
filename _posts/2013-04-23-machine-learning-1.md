---
layout: post
title: "1 Linear Regression with One Variable"
description: "machine learing notes 1"
category: course
tags: [ml]
---

## Machine learning algorithms:
1. Supervised learning
2. Unsupervised learning
3. others: 
    + Reinforcement learning
    + Recommender systems

> **Practical advice for applying learning algorithms**

**Supervised learning** is the machine learning task of inferring a function from labeled training data. The training data consist of a set of training examples.

supervised learning give the "right answer" for each example in the data.

+ Regression Problem: predict real-valued output(continuous-value)
+ Classification Problem: discrete-valued output

#### Notation:
+ m = Number of training examles
+ x's = "input" variable / features
+ y's = "output" variable /"target" variable
+ (x, y) -- one training example
+ (x^i, y^i) -- i^th training example

With the training set and learning algorithm, we get hypothesis, which we use to make predictions, is this linear function.

**Hypothesis:** h<sub>θ</sub>(x) = θ<sub>0</sub> + θ<sub>1</sub>x


$$J(\theta_0, \theta_1) = \frac{1}{2m}\sum_{i=1}^{m}(h_\theta(x^{(i)}) - y^{(i)})^{2}$$

minimize θ<sub>0</sub>, θ<sub>1</sub>, J(θ<sub>0</sub>, θ<sub>1</sub>) is cost function(squared error function).

**Want** $$\underset{\theta_{0},\theta_{1}}{min} J(\theta_{0},\theta_{1})$$

**Gradient descent** to minimize some arbitrary function J.

#### Outline
+ Start with some θ<sub>0</sub>,θ<sub>1</sub>
+ Keep changing θ<sub>0</sub>,θ<sub>1</sub> to reduce J(θ<sub>0</sub>,θ<sub>1</sub>) until we hopefully end up at a minimum

#### Gradient descent algorithm(梯度下降)

$$repeat\ until \ convergence 
\left \{  \theta_j := \theta_j - \alpha\frac{\partial }{\partial \theta_j} J(\theta_0, \theta_1)\ \ (for\ j = 0\ and\ j = 1) \right \}$$

Here α is learning rate,it controls how big a step we take when updating parameter theta J.$$ \frac{\partial}{\partial\theta_{i}}J(\theta_{0},\theta_{1}) $$ is the derivative(导数) term. 

We must update θ<sub>0</sub> and θ<sub>1</sub> simultaneously.

Correct: Simultaneously update

$$ temp0 := \theta_0 - \alpha \frac{\partial }{\partial \theta_0} J(\theta_0, \theta_1)\\
temp1 := \theta_1 - \alpha \frac{\partial }{\partial \theta_1} J(\theta_0, \theta_1)\\
\theta_0 := temp0 \\
\theta_1 := temp1 $$

**!Incorrect**

$$ temp0 := \theta_0 - \alpha \frac{\partial }{\partial \theta_0} J(\theta_0, \theta_1)\\
\theta_0 := temp0 \\
temp1 := \theta_1 - \alpha \frac{\partial }{\partial \theta_1} J(\theta_0, \theta_1)\\
\theta_1 := temp1 $$

#### Gradient descent alogirthm
repeat until convergence {

$$ \theta_{0}:=\theta_{0}-\frac{1}{m}\sum^{m}_{i=1}(h_{\theta}(x^{(i)})-y^{(i)}) $$

$$ \theta_{1}:=\theta_{1}-\frac{1}{m}\sum^{m}_{i=1}(h_{\theta}(x^{(i)})-y^{(i)})\cdot x^{(i)} $$

}

**Unsupervised learning** refers to the problem of trying to find hidden structure in unlabeled data.

