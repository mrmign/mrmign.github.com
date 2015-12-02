---
layout: post
title: "libc function code"
description: "Functions in libc"
category: programming
tags: [c]
---

## `atoi`

{% highlight c %}
int atoi(const char *s)
{
    static const char digits[] = "0123456789";  /* legal digits in order */
    unsigned val=0;         /* value we're accumulating */
    int neg=0;              /* set to true if we see a minus sign */

    /* skip whitespace */
    while (*s==' ' || *s=='\t') {
            s++;
    }

    /* check for sign */
    if (*s=='-') {
            neg=1;
            s++;
    }
    else if (*s=='+') {
            s++;
    }

    /* process each digit */
    while (*s) {
            const char *where;
            unsigned digit;
            
            /* look for the digit in the list of digits */
            where = strchr(digits, *s);
            if (where==NULL) {
                    /* not found; not a digit, so stop */
                    break;
            }

           /* get the index into the digit list, which is the value */
            digit = (where - digits);

            /* could (should?) check for overflow here */

            /* shift the number over and add in the new digit */
            val = val*10 + digit;

            /* look at the next character */
            s++;
    }
    
    /* handle negative numbers */
    if (neg) {
            return -val;
    }
    
    /* done */
    return val;
}
{% endhighlight %}