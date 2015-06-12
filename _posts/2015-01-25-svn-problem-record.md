---
layout: post
title: "svn problem record"
categories:
tags: svn
---

## SVN obstructed

copy them to a save place! Now remove all .svn dirs from your copy and run an update on your local project and copy back the »obstructed« dirs/files.
`Find and delete the .svn files
$ find ./ -name ".svn" | xargs rm -Rf`
