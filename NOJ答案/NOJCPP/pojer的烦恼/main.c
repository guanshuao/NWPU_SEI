#include <stdio.h>
int main()
{
	int n;
	int a[32],i,j,k;

	scanf("%d",&n);
	j=n;
	k=0;
	for(i=0;i<32;i++)
	{	a[i]=j%2;
		j=j/2;
		k++;
		if(j==1)
		{	a[i+1]=1;
			k=k+1;
			break;
		}
		if(j==0)
			break;
	}
	for(i=k-1;i>=0;i--)
		printf("%d",a[i]);
	printf("\n");

	return 0;
}
