---
layout: post
title: "6 Advice for applying machine learning"
description: ""
category: course 
tags: [ml]
---

>Quize

Suppose an implementation of linear regression (without regularization) is badly overfitting the training set. In this case, we would expect: The training error $$ J(\theta) $$ to be low, the test error $$ J_{test}(\theta) $$ to be high.

## Deciding what to try next

* Get more training examples
* Try smaller sets of features
* Try getting additional features
* Try adding polynomial features ($$ x_1^2, x_2^2,x_1x_2 $$ etc)
* Try decreasing $$ \lambda $$
* Try increading $$ \lambda $$

## Evaluating a hypothesis

**Training/testing procedure for linear regression**

* Learn parameter $$ \theta $$ from training data(minimizing training error $$ J(\theta) $$)
* Compute test set error.$$ J_{test}(\theta) $$

$$ J_{test}(\theta) = \frac{1}{2m_{test}} \sum_{i=1}^{m_{test}}(h_\theta(x_{test}^{(i)}) - y_{test}^{(i)})^2$$

把training data 分成２组，一组用来training(如70%的数据),另一组test(30%的数据)用来验证。

**Training/testing procedure for	logistic regression**	
  
* Learn	parameter $$\theta$$ from training	data
* Compute test set error

$$ J_{test}(\theta) = -\frac{1}{m_{test}} \sum_{i=1}^{m_{test}} \left[y_{test}^{(i)}\log h_\theta(x_{test}^{(i)}) + (1- y_{test}^{(i)})\log h_\theta(x_{test}^{(i)}) \right]$$

* MisclassificaDon error (0/1 misclassificaDon error):
 
## Model selection and training/validation/test sets

**Model selection**

d = degree of polynomial,即 $$　h_\theta(x) $$　中x的最高次。如 $$ h_\theta(x) = \theta_0 + \theta_1x + \cdots + \theta_3x^3 $$ d=3

把数据集随机的分成３部分，可以先将数据随机的打乱，然后取前60%作为training set,再接着取20%作为cross validation set，最后的20%作为test set.

**Train/validation/test error**

* Training error:

$$ J_{train}(\theta) = \frac{1}{2m} \sum_{i=1}^m(h_\theta(x^{(i)}) - y^{(i)})^2  $$

* Corss validation error:

$$ J_{cv}(\theta) = \frac{1}{2m_{cv}} \sum_{i=1}^{m_{cv}}(h_\theta(x_{cv}^{(i)}) - y_{cv}^{(i)})^2 $$

* Test error：

$$ J_{test}(\theta) = \frac{1}{2m_{test}} \sum_{i=1}^{m_{test}}(h_\theta(x_{test}^{(i)}) - y_{test}^{(i)})^2 $$

## Diagnosing bias vs. variance

**Bias/Variance**

* High bias(underfit) small d.
* High variance(overfit) large d

`图参考slides#p17`

* Bias(underfit):
    * $$ J_{train}(\theta) $$ will be high
    * $$ J_{cv}(\theta) \approx  J_{train}(\theta) $$
* Variance(overfit)
    * $$ J_{train}(\theta) $$ will be low
    * $$ J_{cv}(\theta) \gg  J_{train}(\theta) $$

上面讨论的是error 与　d的关系。当d较小时，会导致error偏大underfit,　$$J_{train}(\theta) $$值较大，与$$J_{cv}(\theta) $$接近。
当d很大时,error较小overfit，$$J_{train}(\theta) $$较小，$$J_{cv}(\theta) $$远大于$$J_{train}(\theta) $$

#＃　Regularization and bias/variance

* High bias(underfit) large $$ \lambda $$
* High variance(overfit) small $$ \lambda $$

`参考slide#p23`

这里讨论的是error与$$\lambda$$的关系。当$$\lambda$$较小时，error较小(overfit).

## Learning curves

`slide#p25`

* If a learning algorithm is suffering from high bias, getting more training data will not(by itsetl) help much.
* If a learning algorithm is suffering from high vairance, getting more training data is likely to help.

## Deciding what to try next

* Get more training examples $$ \Rightarrow  $$ fixes high vairance
* Try smaller sets of features $$ \Rightarrow  $$ fixes high vairance
* Try getting additional features $$ \Rightarrow  $$ fixes hig bias
* Try adding polynomial features ($$ x_1^2, x_2^2,x_1x_2 $$ etc) $$ \Rightarrow  $$ fixes hig bias
* Try decreasing $$ \lambda $$ $$ \Rightarrow  $$ fixes hig bias
* Try increading $$ \lambda $$ $$ \Rightarrow  $$ fixes high vairance

**Neural networks and overfitting**

* "Small" neural network(fewer parameters; more prone to underfitting) 
    * Computationally cheaper
* "Large" neural network(more parameters; more prone to overfitting) 
    * Computationally more expensive
    * Use regularization($$ \lambda $$) to address overfitting

[**Slides**](/files/6-1 Advice for applying machine learning.pdf)
