---
layout: post
title: "8.2 Dimensionality	Reduction, PCA"
description: "PCA"
category: course 
tags: [ml]
---
{% include JB/setup %}

### Data Compression

从2D到1D，3D到2D

###　Principal Component Analysis(PCA) 

Reduce from n-dimension to k-dimension: 

Find k vectors $$ \mu^{(1)}, \mu^{(2)},\cdots, \mu^{(k)}$$ onto which to project the data, so as to minimize the projection error.

**PCA is not linear regression**

**Data preprocessing**

Traing set: $$ x^{(1)}, x^{(2)}, \cdots, x^{(m)}$$

Preprocessing(feature scaling/mean normalization): 

$$ \mu_j = \frac{1}{m} \sum_{i=1}^m x_j^{(i)}$$

Replace each $$x_j^{(i)}$$ with $$ x_j - \mu_j $$

If different features on different scales, scale features to have comparable range of values.

$$ x_j^{(i)} \leftarrow \frac{x_j^{(i)} - \mu_j}{s_j} $$

**Reduce data from n-dimensions to k-dimensions**

* Compute"covriance matrix": X(m*n)中的每一行是一个example

$$ Sigma \ \sum = \frac{1}{m} \sum_{i=1}^n (x^{(i)})(x^{(i)})^T \\
Sigma = \frac{1}{m} X' * X;
$$

* Compute "eigenvectors" of matrix $$\sum$$:

$$ [U, S, V] = svd(Sigma); \\
U_{reduce} = U(:,1:k); \\
Z = U_{reduce}^T * X;
$$

* U是n*n的矩阵
* S是n*n矩阵
* $$U_{reduce}$$ 是n*k矩阵
* Z 是　k*n

### Reconstruction from compressed representation

$$ z = U_{reduce}^T x \\
X_{approx}^{(i)} = U_{reduce} * Z^{(i)}$$

### Choosing the number of principal components

**Choose K to be smallest value so that**

$$
\frac{ \frac{1}{m} \sum_{i=1}^{m} \Vert x^{(i)} - x_{approx}^{(i)} \Vert^2}{\frac{1}{m} \sum_{i=1}^{m} \Vert x^{(i)}\Vert^2} \leq 0.01 
$$

**99% of variance is retained!!**

[More detail slides#24](/files/8-2 Dimensionality Reduction.pdf)

### Advice for applying PCA

* Supervised learning speedup. $$ (x_{(1)},y_{(1)}), (x_{(2)},y_{(2)}),\cdots, (x_{(m)},y_{(m)}) \longrightarrow   (z_{(1)},y_{(1)}), (z_{(2)},y_{(2)}),\cdots, (z_{(m)},y_{(m)}) $$. New training sets have low dimensions.

**NOTE**

Mapping $$ x^{(i)} \rightarrow z^{(i)} $$ should be defined by running PCA only on the training set. This mapping can be applied as well to the examples $$ x_{cv}^{(i)} $$ and $$ x_{test}^{(i)}$$ in the cross validation and test sets.

* Reduce memory/disk needed to store data
* Visualization

**Bad use of PCA**

* Use $$ z^{(i)} $$ instead of $$ x^{(i)} $$ to reduce the number of features to k<n. Thus, fewer features, less likely to overfit. Use regularization instead.

### PCA正解使用

在使用PCA前，先用原始数据运行，如果结果不是想要的，然后再用PCA.

[slide](/files/8-2 Dimensionality Reduction.pdf)




