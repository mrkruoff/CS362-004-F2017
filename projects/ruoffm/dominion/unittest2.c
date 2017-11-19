#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

///test endTurn

int main(){
struct gameState G;
int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
		   
initializeGame(2,k,1,&G);
G.whoseTurn=0;
int pass=1;
int currentTurn=G.whoseTurn;
printf("testing endTurn()\n");
printf("testing hand count\n");
endTurn(&G);
int handcount1=G.handCount[0];
int handcount2=G.handCount[1];
printf("size of player one hand %d, size of player two hand %d\n", handcount1,handcount2);
if(handcount1!=0 && handcount2==0)
{
	pass=0;
	printf("Wrong Hand Counts\n");
}
printf("testing turn incremented\n");
printf("previoius turn %d, current turn %d\n",currentTurn, G.whoseTurn);
if(currentTurn==G.whoseTurn)
{
	pass=0;
	printf("turn not incremented\n");
}
currentTurn=G.whoseTurn;
printf("testing turn incremented part 2\n");
endTurn(&G);
printf("previoius turn %d, current turn %d\n",currentTurn, G.whoseTurn);
if(currentTurn==G.whoseTurn)
{
	pass=0;
	printf("turn not incremented\n");
}


if(pass==1)
{
	printf("Test Passed\n");
}
else
{
	printf("Bug in function\n");
}
return 0;
}
