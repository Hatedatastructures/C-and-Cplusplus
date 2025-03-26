#include <stdio.h>
#include <winsock.h>

int main()
{
    char arr[] ={'1','2','3','4','5','6','7','8','9'};
    const char *p = arr;
    char* const cou = arr;
    printf("%p\n%p\n",arr,&arr[0]);
    printf("%p\n%p\n",p,&p[0]);
    printf("%p\n%p\n",cou,&cou[0]);
    char * arrs = 1;
    char * p = 2;
    printf("%d\n",p-arr);
    return 0;
}