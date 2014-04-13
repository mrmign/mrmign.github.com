---
layout: post
title: "6 machine learning system design"
description: ""
category: course 
tags: [ml]
---

## Error analysis

**Recommended approch**

* Start with a simple algorithm that you can implement quickly
* Plot learning curves to decide if more data, more features, etc. are likely to help
* Error analysis: Manually examine the examples(in cross validataion set) that your algorithm made errors on. See if you spot any systematic trend in what type of examples it is making errors on.

## Error metrics for skewed classes

**Precision/Recall**

![precision_recall.png](/images/ml/precision_recall.png)

* $$ Accuracy = \frac{true \ positives + true \ negatives}{total\ examples} $$
* $$ Precision = \frac{true\ positives}{true\ positives + false\ positives} $$
* $$ Recall = \frac{true\ positives}{true\ positives + false\ negatives} $$
* $$ F_1 score = 2 \frac{precision * recall}{precision + recall} $$

用slide上的例子解释上面的图

* Precision: 在我们所预测的y=1的病人中，有多少是真的得了癌症
* Recall：在所有的有癌症的病人当中，有多少被正确预测到了。

## Trading off precision and recall

Logistic regression: $$ 0 \leq h_\theta(x) \leq 1 $$

**Prediect 1 if** $$ h_\theta(x) \geq $$ **threshold**

* Suppose we want to predict y = 1(cancer) only if very confident. $$ \longrightarrow $$ Higher precision, lower recall. 可以让threshold大点
* Suppose we want to avoid missing too many cases of cancer(avoid false negative) {$$ \longrightarrow $$ Higher recall, lower precision} 可以让threshold小点

