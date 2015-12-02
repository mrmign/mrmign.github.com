---
layout: post
title: "iOS7 Programming Cookbook笔记"
category: "iOS"
tags: "iOS"
description: ""
---

# Chapter 1

## Adding Object and Index Subscription Support

类似Dictionary和Array那种用下标来访问。


~~~objc
@interface Person : NSObject

@property (nonatomic, copy) NSString *firstName;
@property (nonatomic, copy) NSString *lastName;

// object subscription
- (id) objectForKeyedSubscript:(id<NSCopying>)paramKey;
- (void) setObject:(id)paramObject forKeyedSubscript:(id<NSCopying>)paramKey;

// index subscription
- (id) objectAtIndexedSubscript:(NSUInteger)paramIndex;
- (void) setObject:(id)paramObject atIndexedSubscript:(NSUInteger)paramIndex;
@end
~~~

~~~objc
NSString *const kFirstNameKey = @"firstName";
NSString *const kLastNameKey = @"lastName";

@implementation Person

- (id) objectForKeyedSubscript:(id<NSCopying>)paramKey{
    NSObject<NSCopying> *keyAsObject = (NSObject<NSCopying> *)paramKey;
    if ([keyAsObject isKindOfClass:[NSString class]]){
        NSString *keyAsString = (NSString *)keyAsObject;
        if ([keyAsString isEqualToString:kFirstNameKey] ||
            [keyAsString isEqualToString:kLastNameKey]){
            return [self valueForKey:keyAsString];
        }
    }
    return nil;
}

- (void) setObject:(id)paramObject forKeyedSubscript:(id<NSCopying>)paramKey{
    NSObject<NSCopying> *keyAsObject = (NSObject<NSCopying> *)paramKey;
    if ([keyAsObject isKindOfClass:[NSString class]]){
        NSString *keyAsString = (NSString *)keyAsObject;
        if ([keyAsString isEqualToString:kFirstNameKey] ||
            [keyAsString isEqualToString:kLastNameKey]){
            [self setValue:paramObjectforKey:keyAsString];
        }
    }
}

- (id) objectAtIndexedSubscript:(NSUInteger)paramIndex{

    switch (paramIndex){
        case 0:{
            return self.firstName;
            break;
        }
        case 1:{
            return self.lastName;
            break;
        }
        default:{
            [NSException raise:@"Invalid index" format:nil];
        }
    }

    return nil;
}

- (void) setObject:(id)paramObject atIndexedSubscript:(NSUInteger)paramIndex{
    switch (paramIndex){
        case 0:{
            self.firstName = paramObject;
            break;
        }
        case 1:{
            self.lastName = paramObject;
            break;
        }
        default:{
            [NSException raise:@"Invalid index" format:nil];
        }
    }
} 
@end
~~~

利用下标来操作对象。

~~~objc
Person *person = [Person new];
person[kFirstNameKey] = @"Tim";
person[kLastNameKey] = @"Cook";
NSString *firstNameByKey = person[kFirstNameKey];
NSString *lastNameByKey = person[kLastNameKey];

NSString *firstNameByIndex = person[0];
NSString *lastNameByIndex = person[1];

if ([firstNameByKey isEqualToString:firstNameByIndex] &&
    [lastNameByKey isEqualToString:lastNameByIndex]){
    NSLog(@"Success");
} else {
    NSLog(@"Something is not right");
}
~~~


