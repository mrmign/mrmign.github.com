---
layout: post
title: "iOS9 https问题"
category: "iOS"
tags: "iOS https"
description: ""
---

iOS9提高了http的请求安全，需要进行如下设置：

~~~xml
<key>NSAppTransportSecurity</key>  
  <dict>  
  <key>NSAllowsArbitraryLoads</key>  
  <true/>  
  </dict>
~~~