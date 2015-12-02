---
layout: post
title: "用vundle重新配置vim"
categories: tool
tags: vim vundle
---

1. 根据此文章配置最基本的[这里][1]
2. 配置写代码不可缺少的代码提示，自动完成功能，这里安装`YouCompleteMe`[看这里][2]
    * ubuntu13.04升级vim到7.4 [看这里][3]
    * 其中遇到ubuntu13.04安装clang-3.4问题，安装clang-3.4，[看这里][4]
    * 在`sudo apt-get update`时遇到个问题，`http://llvm.org llvm-toolchain-raring Release: 
      The following signatures couldn't be verified because the public key is not available: NO_PUBKEY 15CF4D18AF4F7421`， [解决方法][5]
    * 然后才执行`sudo apt-get update` 0error，接着安装就好了。
3. 找需要的插件，这个得慢慢补，有好用的，大家来推荐哈。


  [1]: http://hahaya.github.io/2013/07/26/use-vundle.html
  [2]: http://hahaya.github.io/2013/07/29/build-YouCompleteMe.html
  [3]: http://my.oschina.net/floger/blog/152271
  [4]: http://llvm.org/apt/
  [5]: https://groups.google.com/forum/#!msg/idris-lang/Cgp99-iQmsQ/QSFE2hW949QJ
