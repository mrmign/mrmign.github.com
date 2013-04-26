---
layout: post
title: "machine learning 1"
description: "machine learing notes"
category: course
tags: [ml]
---
{% include JB/setup %}

## Machine learning algorithms:
1. Supervised learning
2. Unsupervised learning
3. others: 
    + Reinforcement learning
    + Recommender systems

> **Practical advice for applying learning algorithms**

**Supervised learning** is the machine learning task of inferring a function from labeled training data. The training data consist of a set of training examples.

supervised learning give the "right answer" for each example in the data.

+ Regression Problem: predict real-valued output
+ Classification Problem: discrete-valued output

#### Notation:
+ m = Number of training examles
+ x's = "input" variable / features
+ y's = "output" variable /"target" variable
+ (x, y) -- one training example
+ (x^i, y^i) -- i^th training example

With the training set and learning algorithm, we get hypothesis, which we use to make predictions, is this linear function.

**Hypothesis:** h<sub>θ</sub>(x) = θ<sub>0</sub> + θ<sub>1</sub>x


J(\theta_0, \theta_1) = \frac{1}{2m}\sum_{i=1}^{m}(h_\theta(x^{(i)}) - y^{(i)})^{2}

![cost function](/images/ml/1-1.gif)

minimize θ<sub>0</sub>, θ<sub>1</sub>, J(θ<sub>0</sub>, θ<sub>1</sub>) is cost function(squared error function).

\underset{\theta_{0},\theta_{1}}{min} J(\theta_{0},\theta_{1})

**Want** ![min](http://latex.codecogs.com/gif.latex?\underset{\theta_{0},\theta_{1}}{min}J(\theta_{0},\theta_{1}))



**Gradient descent** to minimize some arbitrary function J.

#### Outline
+ Start with some θ<sub>0</sub>,θ<sub>1</sub>
+ Keep changing θ<sub>0</sub>,θ<sub>1</sub> to reduce J(θ<sub>0</sub>,θ<sub>1</sub>) until we hopefully end up at a minimum

#### Gradient descent algorithm(梯度下降)
![gradient descent algorithm](http://latex.codecogs.com/gif.latex?repeat\&space;until\&space;convergence&space;\left\{&space;\theta_{j}&space;:=\theta_{j}&space;-&space;\alpha\frac{\partial&space;}{\partial\theta_{j}}J(\theta_{0},\theta{1})&space;\&space;(for\&space;j=0&space;\&space;and&space;\&space;j&space;=&space;1)&space;\right&space;\})
Here α is learning rate. 

We must update θ<sub>0</sub> and θ<sub>1</sub> simultaneously.

Correct: Simultaneously update

![simultaneously update](http://latex.codecogs.com/gif.latex?\\*&space;temp0&space;:=&space;\theta_{0}&space;-&space;\alpha\frac{\partial&space;}{\partial&space;\theta_{0}}J(\theta_{0},\theta_{1})&space;\\*&space;temp1&space;:=&space;\theta_{1}&space;-&space;\alpha\frac{\partial&space;}{\partial&space;\theta_{1}}J(\theta_{0},\theta_{1})&space;\\*&space;\theta_{0}:=temp0&space;\\*&space;\theta_{1}:=temp1)

**!Incorrect**

![incorrect](http://latex.codecogs.com/gif.latex?\\*&space;temp0&space;:=&space;\theta_{0}&space;-&space;\alpha\frac{\partial&space;}{\partial&space;\theta_{0}}J(\theta_{0},\theta_{1})&space;\\*&space;\theta_{0}:=temp0&space;\\*&space;temp1&space;:=&space;\theta_{1}&space;-&space;\alpha\frac{\partial&space;}{\partial&space;\theta_{1}}J(\theta_{0},\theta_{1})&space;\\*&space;\theta_{1}:=temp1)

**Unsupervised learning** refers to the problem of trying to find hidden structure in unlabeled data.
