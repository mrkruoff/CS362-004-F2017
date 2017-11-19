#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

int main(){
///test kingdomCards
int* test=malloc (10*sizeof(int));//to be filled with function
assert(test);
int i;
int j;
int a=1,b=2,c=3,d=4,e=5,f=6,g=7,h=8,k=9,m=10;
test=kingdomCards(1,2,3,4,5,6,7,8,9,10);
printf("Beginning test\n");
printf("testing direct inputs\n");
int pass=1; 
for(i=0;i<9;i++)
{
	j=i+1;
	printf("values are %d %d\n",i,j);
	if(test[i]==test[j])
		{
			printf("test failed, values %d and %d are equal \n", i,j);
			pass=0;
		}
}

printf("testing inputs via variable\n");
test=kingdomCards(a,b,c,d,e,f,g,h,k,m);
for(i=0;i<9;i++)
{
	j=i+1;
	int val1=test[i];
	int val2=test[j];
	printf("values are %d %d\n", val1,val2);
	if(val1==val2)
	{
		printf("test failed, values %d and %d are equal \n", val1,val2);
		pass=0;
	}
	
	
}
if(pass==1)
{
 printf("Test Passed\n");
}
else
{
	printf("kingdomCards did not pass\n");
}

return 0;

}
