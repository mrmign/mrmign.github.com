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

<div>
J(\theta_0, \theta_1) = \frac{1}{2m}\sum_{i=1}^{m}(h_\theta(x^{(i)}) - y^{(i)})^{2}
</div>
**Unsupervised learning** refers to the problem of trying to find hidden structure in unlabeled data.
