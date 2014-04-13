---
layout: post
title: "Map Reduce"
description: ""
category: course
tags: [datasci]
---

## MapReduce Programming Model

* Input & Output: each a set of key/value parirs
* Programmer specifies two functions:
    * `map(in_key, in_value)->list(out_key,intermediate_value)`
        * Process input key/value pair
        * Produces set of intermediate pairs
    * `reduce(out_key,list(intermediate_value))->list(out_value)`
        * Combines all intermediate values for particular key
        * Produces a set of merged output values(usually just one)


>Inspired by primitives from functional programming languages such as Lisp, Scheme, and Haskell

> **MapReduce Extensions and contemporaries**

* Pig(Yahoo, available open source) 
    * Relational Algebra over Hadoop
* HIVE(Facebook, available open source)
    * SQL over Hadoop
* Impala
    * SQL over HDFS, uses some HIVE code
* Cascading
    * Relational Algebra
* Dryad(Microsoft, not available)
    * Relational Algebra
* Clustera(U of Wisconsin, not available)
    * Relational Algebra

## Quiz question

In solving the '4cardstraight' problem, we must emit the '4cardstraight' just after 'straight', why? If not, we can't get the right answer. Why the order influence the result?