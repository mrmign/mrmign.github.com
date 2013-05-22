---
layout: post
title: "4 Neural Networks: Representation"
description: "Neural Networks"
category: course 
tags: [ml]
---
{% include JB/setup %}

## Model Representation

**Notation**

* $$ a_i^{(j)} $$ = "activation" of unit $$ i $$ in layer $$ j $$
* $$ \Theta^{(j)} $$ = matrix of weights controlling function mapping from layer $$ j $$ to layer $$ j+1 $$

"activation function" is the same with sigmoid function.

If networks has $$ s_j $$ units in layer $$j, s_{j+1}$$ units in layer $$ j + 1 $$, then $$ \Theta^{(j)} $$ will be of dimension $$ s_{j + 1} \times (s_j + 1) $$

**Quiz**

* We must compose multiple logical operations by using a hidden layer to represent the XOR function.
* Since we can build the basic AND, OR, and NOT functions with a two layer network, we can (approximately) represent any logical function by composing these basic functions over multiple layers.
* A smaller value of λ allows the model to more closely fit the training data, thereby increasing the chances of overfitting.
* A larger value of λ will shrink the magnitude of the parameters Θ, thereby reducing the chance of overfitting the data.