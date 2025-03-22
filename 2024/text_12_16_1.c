#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
//研究malloc函数申请内存的过程
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    long long p = 0;
    while (1)
    {
        malloc(1);
        p++;
        printf("已申请%lld字节的空间\n", p);
    }
    return 0;
}