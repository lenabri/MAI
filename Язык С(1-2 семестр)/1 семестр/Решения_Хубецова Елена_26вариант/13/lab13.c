#include<stdio.h>
#include"Set.h"

char Word[20], S[2*N],              // S - set for word
Consonants[]="BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz", Sc[2*N],   // Sc - set for consonants
SZ[]="SZsz", Ss[2*N], S1[2*N];   // Ss - set for letters s,z

int main()
{ int i=1, n, m=0; char oldc=' ', c;
    CreateSet(Consonants,Sc); CreateSet(SZ,Ss);
//      DisplaySet(Sc); DisplaySet(Ss);   // print for test
  while(i!=EOF)
  { i=getchar(); c=i;
    if(!Letter(oldc)&&Letter(c)){n=0;Word[0]=c;}  // begin of word
    if(Letter(oldc)&&Letter(c)) Word[++n]=c;
    if(Letter(oldc)&&!Letter(c))                  // end of word
    { Word[++n]='\0';
      CreateSet(Word,S); IntersSet(S,Sc,S1);      // intersection of sets
//	DisplaySet(S); DisplaySet(S1);                    // print for test
       if(!EmptySet(S1)&&IncludeSet(S1,Ss))       // only our vowels
	 { printf("%s ",Word); if(!(++m%10)) printf("\n"); }
    }
   oldc=c;
  }
}
