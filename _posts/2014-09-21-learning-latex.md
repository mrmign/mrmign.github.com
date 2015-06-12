---
layout: post
title: "LATEX学习"
categories: tools
tags: latex
---

## MacTex 中文显示问题 ##

{%highlight latex%}
\documentclass{article}

%下面两行是用来支持中文的
\usepackage{fontspec,xltxtra,xunicode}
\defaultfontfeatures{Mapping=tex-text}

\setmainfont{Songti SC Regular} %设置字体，字体可以从系统的字体册里查找

\newfontfamily{\H}{Times New Roman} %字体也是从字体册里找，必须是系统里有的字体才行

\begin{document}
\LaTeX3是一个长远的目标，在它最张骞害怕成前, \LaTeXe{}是标准 \LaTeX\ 版本.

{\H this is english}

aaabbb
\end{document}
{% endhighlight %}

一时兴起，体会了把高大上的Latex，功能是强大的很啊，可是对于我等码农不用写高深的公式，也不出书立传的，貌似用不到点上了，用markdown足矣。。。束之高阁。


