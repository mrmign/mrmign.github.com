---
layout: post
title: "8.1 Clustering: K-means algorithm"
description: "clustering"
category: course 
tags: [ml]
---
{% include JB/setup %}

### Input:

* K (number of clusters)
* Training set {$$ x^{(1)}, x^{(2)}, \cdots, x^{(m)} $$}

**Notation**

$$ x^{(i)} \in \mathbb{R}^n $$ (drop $$ x_0 = 1 $$ convention)

### K-means algorithm

Randomly initialize K cluster centroids $$ \mu_1, \mu_2, \cdots, \mu_k \in \mathbb{R}^n $$ 

Repeat {

/* Cluster assignment step */

for $$ i = 1 $$ to $$ m $$

$$ c^{(i)} $$ := index (from i to K) of cluster centroid closest to $$ x^{(i)} $$

$$ \boxed{min_k = \Vert x^{(i)} - \mu_k \Vert^2} $$

/* Move centroid */

for $$ k = 1 $$ to K

$$ \mu_k $$ := average(mean) of points assigned to cluster k

}

### K-means optimizaiton objective

* $$ c^{(i)} $$ = index of cluster(1,2,...,K) to which example $$ x^{(i)} $$ is currently assigned
* $$ \mu_k $$ = cluster centroid k ($$ \mu_k \in \mathbb{R}^n $$)
* $$ \mu_c^{(i)} $$ = cluster centroid of cluster to which 

$$ J(c^{(1)},\cdots,c^{(m)},\mu_1,\cdots,\mu_k) = \frac{1}{m} \sum_{i=1}^{m} \Vert x^{(i)} - \mu_k \Vert^2 $$

### Random initialization

Randomly initialize K cluster centroids $$ \mu_1, \mu_2, \cdots, \mu_k \in \mathbb{R}^n $$

* Should have $$ k < m $$ $$
* Randomly pick K training examples
* Set $$ \mu_1, \mu_2, \cdots, \mu_k $$ equal to these K examples

For i = 1 to 100 {

* Randomly initialize K-means
* Run K-means. Get $$ c^{(1)}, \cdots, c^{(m)},\mu_1, \cdots, \mu_k $$
* Compute cost function( **distortion** ) $$ J(c^{(1)},\cdots,c^{(m)},\mu_1,\cdots,\mu_k) $$

}

**Pick clustering that gave lowest cost** $$ J(c^{(1)},\cdots,c^{(m)},\mu_1,\cdots,\mu_k) $$

### Choosing the value of K

**Elbow method** 