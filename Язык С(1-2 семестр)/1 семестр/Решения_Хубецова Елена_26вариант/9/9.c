#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int min(int a, int b)
{
	if(a >= b) 
	return b;
	return a;
}

int max(int a, int b)
{
	if(a >= b) 
	return a;
	return b;
}

int sign(int a)
{
	if(a == 0)
	return 0;
	if(a >= 0)
	return 1;
	return -1;
}


int main(){
	int i= -10, j = -10, l = 6, k, 
	 next_i, next_j, next_l;

	 
	  
	  for(k = 0; k < 50; k++)
	 {
		 double r = (double)((i-20.)*(i-20.))/100. + (double)(j*j)/25.;
		  if(r <= 1.)
		 {
			 printf("Intersection in I = %d, J = %d, L = %d on %d step.\n", i, j, l, k);
			 return 0;
		 }
		 next_i = abs(max(min(i + j, i + l)%30, max(i + l, j + k)%25));
		 next_j = abs(i + k)%10 + abs(j + k)%10 + abs(l + k)%10;
		 next_l = (i*i*i + j*j*j +l*l*l - k)%35;
		
		   i =next_i;
		   j =next_j;
		   l =next_l;
		   
		 }
		 printf("No intersection\n"); 
		 return 0;
}
