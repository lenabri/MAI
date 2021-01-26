#include <stdlib.h> // var 26
#include <stdio.h>
int main()
{
	int a[9][9], n,m,i,j,jmax, max;
	printf ("Input size of matrix <10: n=");
	scanf ("%d",&n);

	for(j=0;j<n;j++)
	 { 
	    for(i=0;i<n;i++) 
	    a[i][j]=rand()%20;
	 }


	printf ("Started matrix:a\n");
	for(i=0;i<n;i++)
	 { 
		 for(j=0;j<n;j++)
		 printf (" %3d ",a[i][j]);
		 printf ("\n");
	 }
	 
	 max = 0;
	 for(i=0;i<n;i++)
	 {
		 for(j=0;j<n;j++) 
		 if(a[i][j] > max)
		 {
			 max = a[i][j];
		 }
	 }
	 printf ("Max = %d ",max);
	 printf ("\n");
	 
	 m=n;
	 for(i=0;i<n;i++)
	 {
		 for(j=0;j<m;j++)
		 if (a[i][j]==max)
		 {
			 m=m-1;
			 jmax=j;
			  for(i=0;i<n;i++)
			  {
				  for(j=jmax;j<m;j++)
				  a[i][j]=a[i][j+1];
			  }
			  i=0;
			  j=0;
		 }
	 }
	 

	 
	
printf ("Finish matrix:\n");
	for(i=0;i<n;i++)
	{  for(j=0;j<m;j++)
		printf (" %3d ",a[i][j]);
		printf ("\n");
	}
 return 0;
}
