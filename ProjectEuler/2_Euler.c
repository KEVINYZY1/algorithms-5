/*
 * author:	luo feng
 * date:	2013/10/15
 * source:	Problem 2 of Project Euler.net
 * title:	Even Fibonacci numbers
 * info:	

Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms will be:

1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.

 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned int item1 = 1, item2 = 2;
    unsigned long long cur = item1+item2;
    unsigned long long sum = item2;
    unsigned int up = 4000000;

    while(cur < up) {
        if(!(cur%2)) {
            sum += cur;
        }
        printf("%d\n", cur);
        item1 = item2;
        item2 = cur;
        cur = item1+item2;
    }

    printf("sum of the even-valued terms: %ld\n", sum);

    return 0; 
}