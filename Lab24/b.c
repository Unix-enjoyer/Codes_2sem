#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#include "mathparser.h"

void factorial(long int n)
{
    if (n == 0) return;
    printf("%ld", n);
    factorial(n-1);
}

int main()
{
    factorial(3);
} 

