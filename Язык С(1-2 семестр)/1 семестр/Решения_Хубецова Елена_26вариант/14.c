#include<stdio.h>
int main () {
   int i, j, array[10][10], str[100], n, mlt, count = 0, c;
   printf("Input size of matrix (n <= 10): "); scanf("%d", &n);


   for(i = 0; i < n; i++) for(j = 0; j < n; j++)
      array[i][j] = (i+1)*10 + j+1;

   printf("\nSource matrix:\n");
   for(i = 0; i < n; i++) {
      for(j = 0; j < n; j++) printf("%4d", array[i][j]);
      printf("\n");
   }

   mlt = n*n; i =n -1;  j = n;
   while(count < mlt) {
      for(c = n;   c && count < mlt; c--) str[count++] = array[i][--j];
      for(c = --n; c && count < mlt; c--) str[count++] = array[--i][j];
      for(c = n;   c && count < mlt; c--) str[count++] = array[i][++j];
      for(c = --n; c && count < mlt; c--) str[count++] = array[++i][j];
   }
   
   printf("\nResulting string:\n");
   for(i = 0; i < mlt; i++) printf("%4d",str[i]);
   return 0;
}


