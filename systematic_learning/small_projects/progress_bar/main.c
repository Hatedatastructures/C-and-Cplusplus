#include <stdio.h>
#include <windows.h>
#include <string.h>

int main()
{
    char buffer[102];  //防止溢出
    memset(buffer, ' ', 100);
    buffer[100] = '\0';
    
    for (int i = 0; i <= 100; i++)
    {
        if (i > 0) 
        {
            buffer[i-1] = '#';  
            // 将前一个空格替换为#,只需要打印这个数组就行
        }
        printf("当前进度:%.100s %d%%\r", buffer, i);
        fflush(stdout);
        Sleep(100);
    }
    return 0;
}
