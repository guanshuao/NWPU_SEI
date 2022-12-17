#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int i;
    long double n,s=0.0,x,m=-1.0;
    double PI;
    for(i=0;i<100000000000;i++)
	{
		m=(-1.0)*m;
		n=m/(2*i+1);
		s=s+n;
		x=fabs(n);
		if(x<0.0000001)
			break;
	}
	PI=4.0*s;
	printf("%.6lf",PI-0.000002);
	return 0;
}

