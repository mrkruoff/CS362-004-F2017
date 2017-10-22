#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

int main(){
printf("testing whoseTurn\n");
struct gameState G;
int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
int pass=1;		   
initializeGame(2,k,1,&G);
G.whoseTurn=0;
int correct=G.whoseTurn;
printf("current turn is %d, whoseTurn proivdes %d\n", correct, whoseTurn(&G));
if(correct!=whoseTurn(&G))
{
	pass=0;
	printf("error, turns are incorrect\n");
}

G.whoseTurn=1;
correct=G.whoseTurn;
printf("current turn is %d, whoseTurn proivdes %d\n", correct, whoseTurn(&G));
if(correct!=whoseTurn(&G))
{
	pass=0;
	printf("error, turns are incorrect\n");
}
if(pass==1)
{
	printf("Test Passed\n");
}
else
{
	printf("Test Failed\n");
}
return 0;
}
