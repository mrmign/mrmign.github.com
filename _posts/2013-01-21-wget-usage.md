---
layout: post
title: "wget usage"
category: tool
tags: [wget]
description: Recorde the usual usage of wget.
---

## Download a certain folder and subfolders.
Case: recursively download all the files that are in the ‘ddd’  folder for the url http://hostname/aaa/bbb/ccc/ddd/&#8217;

Solution:
`wget -r -np -nH –cut-dirs=3 -R index.html http://hostname/aaa/bbb/ccc/ddd/`

Explanation:

It will download all files and subfolders in ddd directory:

recursively (-r),

not going to upper directories, like ccc/… (-np),

not saving files to hostname folder (-nH),

but to ddd by omitting first 3 folders aaa, bbb, ccc (–
cut-dirs=3),

excluding index.html files (-R index.html)