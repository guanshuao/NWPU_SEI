#include <stdio.h>
#include <string.h>
#define max(a,b) a>b?a:b
#define min(a,b) a>b?b:a
int sum[101];
void jia(char a[],char b[])
{
  int flag=0,i,len1,len2,lenmax,lenmin;
  len1=strlen(a),len2=strlen(b);
  lenmax=max(len1,len2),lenmin=min(len1,len2);
  for(i=1;i<=lenmax;i++)
  {
    if(i<=lenmin)
    {
      sum[lenmax-i]=a[len1-i]+b[len2-i]-'0'-'0'+flag;
            if(sum[lenmax-i]>=10)
      {
      sum[lenmax-i]=sum[lenmax-i]-10;
      flag=1;
      }
        else flag=0;
    }
    else{
      if(len1>len2)
      {
        sum[lenmax-i]=a[len1-i]-'0'+flag;
        if(sum[lenmax-i]>=10)
        {
               sum[lenmax-i]=sum[lenmax-i]-10;
               flag=1;
        }
        else flag=0;
      }
      else
      {
        sum[lenmax-i]=b[len2-i]-'0'+flag;
        if(sum[lenmax-i]>=10)
        {
            sum[lenmax-i]=sum[lenmax-i]-10;
            flag=1;
        }
        else flag=0;
      }
    }
  }
  if(flag==1)
    printf("1");
  for(i=0;i<lenmax;i++)
    printf("%d",sum[i]);
  printf("\n");
}
void jian(char a[],char b[])
{
    int flag=0,i;
  int len1,len2;
  len1=strlen(a),len2=strlen(b);
  for(i=1;i<=len1;i++)
  {
    if(i<=len2)
    {
      if(a[len1-i]-b[len2-i]-flag>=0)
      {
        sum[len1-i]=a[len1-i]-b[len2-i]-flag;
        flag=0;
      }
      else
      {
                sum[len1-i]=a[len1-i]-b[len2-i]-flag+10;
        flag=1;
      }
    }
    else
    {
      if(a[len1-i]-flag-'0'>=0)
      {
        sum[len1-i]=a[len1-i]-flag-'0';
        flag=0;
      }
      else
      {
                sum[len1-i]=a[len1-i]-flag+10-'0';
        flag=1;
      }
    }

  }
    for(i=0;i<len1&&sum[i]==0;i++);
  for(;i<len1;i++)
      printf("%d",sum[i]);
        printf("\n");
}
void compare(char a[],char b[])
{
  int len1,len2;
  len1=strlen(a),len2=strlen(b);
    if(len1>len2||(len1==len2&&strcmp(a,b)>0))
    jian(a,b);
  else if(strcmp(a,b)!=0)
  {
    printf("-");
    jian(b,a);
  }
  else
    printf("0\n");
}
int main()
{
  char a[100],b[100];
  gets(a);
  gets(b);
  if(a[0]=='-'&&b[0]!='-')
  {
    printf("-");
    jia(&a[1],b);
  }
  else if(a[0]=='-'&&b[0]=='-')
    compare(&b[1],&a[1]);
  else if(a[0]!='-'&&b[0]=='-')
    jia(a,&b[1]);
  else
    compare(a,b);
  return 0;
}
