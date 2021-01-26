#include<stdio.h>


int main()
{
 
 long n,m,v,w, p=1, s=1,t=0;
 int i=1, j=1, k, l;
 
   printf("Input first number n="); 
   scanf("%ld",&n);
   printf("Input second number m="); 
   scanf("%ld",&m);
   v=n;
   w=m;
   while(v/=10) {p*=10; i++;} 
   while(w/=10) {s*=10; j++;} 
   v=n;
   w=m;
   if (j>i) i=j;
   
   for (j=0; j<i; j++)
   {k=v/p; l=w/s; v=v-k*p; w=w-l*s;
   if (l>k) k=l;
   t=t*10+k;
   p/=10; s/=10;
   if(!p) p=1; if(!s) s=1; 
   }
   
   printf("New number = %ld\n",t);
   printf("Doubled new number = %ld\n",t*2);
 return 0;
}
