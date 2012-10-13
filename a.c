#include <msp430.h>
int fun(void)
{
int i = 10, j = 20;
return i + j;
}
int main()
{
int k = 50;
k = fun();
}

