---
layout: post
title: "iOS上播放消息提示音及振动总结"
category: "iOS"
tags: "iOS"
description: ""
---

在QQ，微信中当收到新消息的时候会播放提示音或是振动，亦或是声音+振动，如何在自己的应用中实现同样的功能呢？

### 播放提示音

当应用在前台运行收到消息时，这个时候要播放消息的提示音了，如何播放直接上代码：

~~~objc
/* 播放完成回调 */
void AudioSoundPlayComplete(SystemSoundID soundid, void* clientData)
{
    AudioServicesRemoveSystemSoundCompletion(soundid);
    AudioServicesDisposeSystemSoundID(soundid);
    AlertSoundService *alerService = (__bridge AlertSoundService*)clientData;
    [alerService stopPlaySound:soundid];
}

- (SystemSoundID)playSound:(NSString *)soundName
{
    SystemSoundID ssid;
    NSString* pathName = nil; 
    pathName = [[NSBundle mainBundle]pathForResource:soundName ofType:nil];
    if (pathName) {
        //将NSString类型路径名转换为NSURL类型
        NSURL* pathUrl = [[NSURL alloc] initFileURLWithPath:pathName];
        if (pathUrl) {
            OSStatus err = AudioServicesCreateSystemSoundID((__bridge CFURLRef)pathUrl, &ssid);
            if (err == kAudioServicesNoError) {
                AudioServicesAddSystemSoundCompletion(ssid, NULL, NULL, AudioSoundPlayComplete,  (__bridge void*)self);
                AudioServicesPlaySystemSound(ssid);
                return ssid;
            }
            else
            {
                NSLog(@"create system sound id fail,%s",__FUNCTION__);
                return 0;
            }
        }
        else
        {
            NSLog(@"path with NSString convert to path with NSURL fail!!!,%s",__FUNCTION__);
            return 0;
        }
    }
    else
    {
        NSLog(@"the path for sound play is nil,%s",__FUNCTION__);
        return 0;
    }
}
~~~

播放提示音是传入要播放的声音文件的名称，从bundle寻找对应文件找到了就进行播放，这里添加了系统声音播放完成后的回调，以便在声音播放结束后进行其他处理，比如如果需要根据不同的消息播放不同的提示音，如果当前正在播放提示音1，此时收到其他消息要播放提示音2，这里就不能简单的直接调用该方法进行播放了，我们需要一个播放队列，把要播放的提示音添加到队列中来处理，当播放完成一个后就需要从队列移除，此时播放完成的回调就派上用场了。

### 振动

如果要振动提示又该如何实现呢？系统为我们提供了振动的soundID `kSystemSoundID_Vibrate`，可以直接使用该soundID实现振动，代码如下:

~~~objc
void VibratePlayComplete(SystemSoundID soundId, void* clientData)
{
    AudioServicesRemoveSystemSoundCompletion(kSystemSoundID_Vibrate);
    AudioServicesDisposeSystemSoundID(kSystemSoundID_Vibrate);
}

- (void)playVibrate
{
    AudioServicesAddSystemSoundCompletion(kSystemSoundID_Vibrate, NULL, NULL, VibratePlayComplete, (__bridge void*)self);
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}
~~~

这里振动实现与播放提示音方法基本一致，只是传的soundID参数不同，在播放提示音时ssid是根据我们的音频文件生成的，而振动是系统定义的。振动完成后也有回调方法进行特殊处理，与播放声音的实现一致。

通过上面的方法我们就实现了消息提示音及振动，这里只是简单的实现，但是在实际场景下还需要添加其他的逻辑处理，比如连续收消息，不能一直播放提示音或是振动吧，用户会不爽的，可以在播放完成提示音后设置一个时间间隔，比如2秒钟内收到消息就不播提示音不振动，超过2秒再有提示，这些都需要根据具体业务需求来处理了。

既然已经实现了播放提示音与振动，那如果我想根据系统是否静音来选择哪种提示：

* 如果系统是静音模式，消息提示为振动
* 如果系统是正常模式，消息提示为提示音

看起来不难嘛，我们读取系统的音量，根据音量大小来判断系统是否是静音不就OK了，那如何读取系统音量呢，一番查资料后，找到如下几种方案：

#### 方案1：

~~~objc
Float32 volume;
UInt32 dataSize = sizeof(Float32);
AudioSessionGetProperty (
                     kAudioSessionProperty_CurrentHardwareOutputVolume,
                     &dataSize,
                     &volume
                     );
~~~

该方案中获取的音量值一直不变。放弃！

#### 方案2：[链接](http://blog.csdn.net/slinloss/article/details/7870559)

~~~objc
 - (BOOL)isMuted  
{  
    CFStringRef route;  
    UInt32 routeSize = sizeof(CFStringRef);  
    OSStatus status = AudioSessionGetProperty(kAudioSessionProperty_AudioRoute, &routeSize, &route);  
    if (status == kAudioSessionNoError)  
    {  
        if (route == NULL || !CFStringGetLength(route))  
            return TRUE;  
    }  
    return FALSE;  
} 

 - (BOOL)addMutedListener  
{  
    OSStatus s = AudioSessionAddPropertyListener(kAudioSessionProperty_AudioRouteChange,  
    audioRouteChangeListenerCallback,  
    self);  
    return s == kAudioSessionNoError;  
}  
void audioRouteChangeListenerCallback (void *inUserData,  
                                       AudioSessionPropertyID inPropertyID,  
                                       UInt32 inPropertyValueSize,  
                                       const void *inPropertyValue  
                                       )  
{  
    if (inPropertyID != kAudioSessionProperty_AudioRouteChange) return;  
    BOOL muted = [mediaVolume isMuted];  
    // add code here  
}
~~~

该方案中使用的方法在iOS7中已不建议使用了，而且该方案在尝试的过程中一直不成功。

####  方案3：[链接](http://sharkfood.com/content/Developers/content/Sound%20Switch/)

该方案中使用的方法是播放一段无声的系统声，判断播放完成所需要的时间，如果获得的时长接近0则表示系统处于静音状态。该方案通过笨方法实现静音的检测，虽然性能不高，因为要一直循环着播放无声的音频文件来检测系统静音状态，但是可以通过正常的API调用来得到系统状态。

根据上面的三种方案感觉通过判断系统音量的方案可以放弃了，再想想其他办法，随着iOS系统的不断完善，硬件也有直接切换静音的按钮(可设置)，系统会不会自动帮我们处理静音振动与非静音播放声音呢？

~~~objc
- (void)playMsgSound
{
    [self playDefaultSound];
    [self playVibrate];
}
~~~

摒着试一试的心态在收到消息时先播放声音，再振动，并尝试通过按键设置系统的静音状态，这里先说明一下iOS系统的设置里针对振动的设置项：

1. 响铃模式振动
2. 静音模式振动

* 关闭1，在收到消息时切换静音状态，可以得到结果静音下只振动，非静音下只播放声音
* 关闭2，静音下不振动也没有播放声音，非静音下，振动+播放声音
* 关闭1和2，不管在静音状态还是非静音状态都没振动和声音
* 打开1和2，静音下振动，非静音下振动+声音

因此我们可以得出系统已经根据用户的设置自动选择了振动与声音模式，我们可以不用判断系统音量来选择振动或是播放声音了，直接播放声音，然后振动。到此问题算是解决了。

### 插播一黑魔法

在上面的方法中振动我们使用系统定义的`kSystemSoundID_Vibrate`来实现，如果在设置中关闭振动选项，就不会再振动了，如果此时不管怎样都要振动，该怎么办呢？黑魔法黑科技来拯救你：

~~~objc
#define kSystemSoundID_Vibrate 1352
- (void)playVibrate
{
    AudioServicesAddSystemSoundCompletion(kSystemSoundID_Vibrate, NULL, NULL, VibratePlayComplete, (__bridge void*)self);
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}
~~~

1352 完全无视系统的静音振动设置，至于为什么会成功还没有深入研究。待补充~~

如果使用该方法能不能正常通过苹果审核不确定，如若被拒，后果自负~~

#### 参考
* [http://stackoverflow.com/questions/4724980/making-the-iphone-vibrate?rq=1](http://stackoverflow.com/questions/4724980/making-the-iphone-vibrate?rq=1)
* [https://github.com/TUNER88/iOSSystemSoundsLibrary](https://github.com/TUNER88/iOSSystemSoundsLibrary)
* [http://sharkfood.com/content/Developers/content/Sound%20Switch/](http://sharkfood.com/content/Developers/content/Sound%20Switch/)
* [http://blog.csdn.net/slinloss/article/details/7870559](http://blog.csdn.net/slinloss/article/details/7870559)




