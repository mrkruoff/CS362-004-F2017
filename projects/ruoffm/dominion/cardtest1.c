#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

//testing smithy
int main(){
struct gameState G;
int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
int pass=1;
printf("Testing Smithy \n");

initializeGame(2,k,1,&G);
G.hand[1][0]=smithy;
G.whoseTurn=1;
int sizeofHand=G.handCount[1]; //get current size
int correct=sizeofHand+2;
printf("current size of hand %d\n", sizeofHand);
playCard(0,0,0,0,&G);
sizeofHand=G.handCount[1];
printf("current size of hand after smithy should be +2 %d\n", sizeofHand);
if(sizeofHand!=correct)
{
	pass=0;
	printf("Hand Size is %d, should be %d\n",sizeofHand,correct);
}
if(pass==1)
{
	printf("Test Passed\n");
}
else
{
	printf("Bug in Smithy\n");
}
	
		   
return 0;
}
