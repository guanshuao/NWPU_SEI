#include <stdio.h>

int nixu(int n)
{
    if(n>10) {
        printf("%d",n%10);
        nixu(n/10);
    }
    else{
    printf("%d",n);
    return 0;}
}
int main()
{
    int n;
    scanf("%d",&n);
    nixu(n);
   return 0;
}
