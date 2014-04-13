---
layout: post
title: "编程之美－3.2　电话号码对应英语单词"
description: "关于编程之美中的问题。"
category: algorithm
tags: [algorithm]
---

>**题目:** 对如非全键盘的手机上的数字，每个数字都对应一些字母，比如2对应ABC，3对应DEF.....，8对应TUV，9对应WXYZ，要求对一段数字，输出其代表的所有可能的字母组合，如5869，可能代表JTMW、JTMX......

{% highlight cpp %}
#include<iostream>
using namespace std;

const int MaxLength = 9;
char c[10][10] = {"", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};
int total[10] = {0,0,3,3,3,3,3,4,3,4};

int main()
{
	int number[MaxLength] = {2,3,4}; //本例输入数字2,3,4
	int answer[MaxLength] = {0};
	int len = 3;
	
	while(true){
		for(int i = 0; i < len; i++)
			printf("%c", c[number[i]][answer[i]]);
		printf("\n");
		
		int k = len - 1;
		while(k >= 0){
			if(answer[k] < total[number[k]] - 1){
				answer[k]++;
				break;
			}
			else{
				answer[k] = 0;
				k--;
			}
		}
		if(k < 0)
			break;
	}
	return 0;
}

{% endhighlight %}

上述算法很巧妙的替代了多重for循环。如果用for来实现的话，有几个数字就得写几个循环，还需要修改程序，可扩展性不好，如上面的程序就不会有此限制，对于多个数字同样适用。

上面的算法可以用来枚举所有的类型，适合排列组合的生成。

