---
layout: post
title: "NoSQL"
description: ""
category: 
tags: []
---
{% include JB/setup %}

## Memcache
**Key Point:** Consistency Hashing

## Dynamo

Configurable Consistency

* R = Minumum number of nodes that participate in a successful read
* W = Minumum number of nodes that participate in a successful write
* N = Replication factor
* If R + W > N, you can claim consistency
* But R + W < N means lower latency

## CouchDB

## BigTable

## Other Google Systems

* HBase
* ...

## Pig

[Pig Intro](http://en.wikipedia.org/wiki/Pig_(programming_tool))

**Data Model**

* Atom: Integer, string, etc
* Tuple:
    * Sequence of fields
    * Each field of any type
* Bag:
    * A collection of tuples
    * Not necessarily the same type
    * Duplicates allowed
* Map:
    * String literal keys mapped to any type

**Example**

t = <1, {<2,3>,<4,6>,<5,7>}, ['apache':'search']>

* f1: atom
* f2: bag
* f3: map

<table>
    <tr>
        <th>expression</th>
        <th>result</th>
    </tr>
    <tr>
        <td>$0</td>
        <td>1</td>
    </tr>
    <tr>
        <td>f2</td>
        <td>Bag{<2,3>,<4,6>,<5,7>}</td>
    </tr>
    <tr>
        <td>f2.$0</td>
        <td>{<2>,<4>,<5>}</td>
    </tr>
    <tr>
        <td>f3#'apache'</td>
        <td>Atom "search"</td>
    </tr>
    <tr>
        <td>sum(f2.$0)</td>
        <td>2+4+5</td>
    </tr>
</table>

### Pig Functions

