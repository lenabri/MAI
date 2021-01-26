#include<stdio.h>
#define zero '0'
#define nine '9'
#define base 10
#define blanc ' '

int main()
{
  int i=1,n=0,m=0,p=0; char c=' ';
  int result,result1;

  while(i!=EOF)
 {  result=0;

    while(i!=EOF&&(c<zero||c>nine))
      { i=getchar(); c=i; }

    while(i!=EOF&&c>=zero&&c<=nine)
     { result=result*base+c-zero;  p++;
       i=getchar(); c=i;
       if (c==blanc)
       { result1=result;
		   m=p;
		   result=0;
		 p=0;
	   }
     }

    
    n++; 
 }  
printf("Последнее число:%d. Его длина:%d\n",result1,m);
   return 0;
} 
