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
G.handCount[1]=4;
G.hand[1][0]=village;
G.whoseTurn=1;
int pass=1;
printf("testing village card\n");
//Test Village
printf("Printing intial states\n");
int initActions=G.numActions;
int initHandCount=G.handCount[1];
printf("number of actions %d\n",initActions);
int value=playCard(0,0,0,0,&G);
int afterActions=G.numActions;
int afterHandCount=G.handCount[1];
printf("after play\n");
printf("number of actions %d\n", afterActions);
if(afterActions<=initActions)
{
	pass=0;
	printf("error in actions changes\n");
}
printf("testing handcounts end up equal after play, before=%d after=%d\n",initHandCount,afterHandCount);
if(initHandCount!=afterHandCount)
{
	pass=0;
	printf("error in handcount\n");	
}
printf("testing return value\n");
if(value!=0)
{
	pass=0;
	printf("incorrect return value, was not 0\n");
}
if(pass==1)
{
	printf("Test Passed\n");
}
else
{
	printf("Bug in village\n");
}
		   
return 0;
}
