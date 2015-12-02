---
layout: post
title: "learning AFNetworking"
categories: iOS
tags: iOS network
---
**下文针对1.x**

AFNetworking-1.x(2.x架构已经完全不一样了)针对不同的请求数据类型有不同的类，如果json, xml, 图片的等。还有个`AFHTTPClient`包含
与API交互的通用模式，如果设置请求的HTTP头或使每个请求使用相对路径。然而，不要直接使用`AFHTTPClient`，应该创建它的子类，从而可以定义有base URL的单例，并且所有的请求基于该base URL使用相对路径完成。
{% highlight objc %}
@interface ALGitHubAPIClient : AFHTTPClient
+ (ALGitHubAPIClient *)sharedClient;
+ @end
{% endhighlight %}

实现下面的方法：
{% highlight objc lineons%}
static NSString * const kAFGitHubAPIBaseURLString = @"https://api.github.com/";

+ (ALGitHubAPIClient *)sharedClient {
    static ALGitHubAPIClient*_sharedClient = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedClient = [[ALGitHubAPIClient alloc] initWithBaseURL:[NSURL URLWithString:kAFGitHubAPIBaseURLString]];
    });

    return _sharedClient;
}

- (id)initWithBaseURL:(NSURL *)url 
{
  self = [super initWithBaseURL:url];
  if (!self) return nil;

  //这里定义了返回数据类型
  [self registerHTTPOperationClass:[AFJSONRequestOperation class]];
  //定义了头部
  [self setDefaultHeader:@"Accept" value:@"application/json"];
  return self;
}
{% endhighlight %}
