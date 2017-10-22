#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"


int main(){
struct gameState G;
int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
initializeGame(2,k,1,&G);
G.hand[1][0]=gardens;
G.whoseTurn=1;
int pass=1;
printf("testing gardens card should return -1\n");
//Test Gardens
int value=playCard(0,0,0,0,&G);
if(value!=-1)
{
	pass=0;
	printf("Gardens returned value other than -1, returned %d\n",value);
}	

if(pass==1)
{
	printf("Test Passed\n");
}
else
{
	printf("Bug in gardens\n");
}
		   
return 0;
}
