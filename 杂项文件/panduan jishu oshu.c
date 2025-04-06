#include <stdio.h>

int main() 
{
    int sum;
    scanf("%d", &sum);
    while (sum)
    {
       if (sum%2==1)
       {
         printf("奇数");
       }
       else 
       {
         printf("偶数");
       }
       sum++;
    }
    return 0;
}
continue;//跳出当前循环进入下一次循环