#include <stdio.h>
#include <string.h>
void shengxu(char s[],int n)
{
    int i,j,k;
    char t;
    for (i=1;i<n;i++){
        t=s[i];
        k=i-1;
        while (t<s[k]){
            s[k+1]=s[k];
            k--;
            if(k==-1) break;
        }
        s[k+1]=t;
    }
}
void jiangxu(char s[],int n)
{
    int i,j,k;
    char t;
    for (i=1;i<n;i++){
        t=s[i];
        k=i-1;
        while (t>s[k]){
            s[k+1]=s[k];
            k--;
            if(k==-1) break;
        }
        s[k+1]=t;
    }
}
int main()
{
    char s[100];
    int n,i,j,t,k,a,p,q;
    gets(s);
    n=strlen(s);
    if (n%2==0){
        shengxu(s,n);
        t=n/2;
        for (i=0;i<t;i++){
            printf("%c",s[i]);
        }
        jiangxu(s,n);
        for (i=0;i<t;i++){
            printf("%c",s[i]);
        }
    }
    else{
        k=(n-1)/2;
        a=s[k];
        shengxu(s,n);
        p=n/2;
        for (i=0;i<p;i++){
            printf("%c",s[i]);
        }
        printf("%c",s[k]);
        jiangxu(s,n);
        n=n/2;
        for (i=0;i<n;i++){
            printf("%c",s[i]);
        }
    }
    return 0;

}
