#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"


int main(){
//set up basic game information and cards
struct gameState G;
int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
		   
int players, seed, index, curPlayer, HandLoc, initHandCount, afterHandCount, value;
int pass;
for(index=0;index<500;index++)
{
	pass=1;
	printf("Test: %d \n",index);
	players=rand()%4+1;
	seed=rand();
	initializeGame(players,k,seed, &G);
	curPlayer=rand()%players;
	HandLoc=rand()%MAX_HAND;
	G.whoseTurn=curPlayer;
	G.hand[curPlayer][HandLoc]=adventurer;
	initHandCount=G.handCount[curPlayer];
	value=playCard(HandLoc,0,0,0,&G);
	afterHandCount=G.handCount[curPlayer];
	printf("Testing handCount size, should not be greater than 2 than initial. initial= %d,after=%d\n",initHandCount,afterHandCount);
	if(afterHandCount-initHandCount>2)
	{
		pass=0;
		printf("HandCount Too large with Player: %d and HandPos: %d\n",curPlayer,HandLoc);
	}
	printf("testing return value\n");
	if(value!=0)
	{
	pass=0;
	printf("incorrect return value, was not 0 with Player: %d and HandPos: %d\n",curPlayer,HandLoc);
	}
	printf("storing copper and silver in hand for proper increase\n");
	initializeGame(players,k,seed, &G);
	G.whoseTurn=curPlayer;
	G.hand[curPlayer][HandLoc]=adventurer;
	G.hand[curPlayer][rand()%MAX_HAND]=copper;
	G.hand[curPlayer][rand()%MAX_HAND]=silver;
	initHandCount=G.handCount[curPlayer];
	value=playCard(HandLoc,0,0,0,&G);
	afterHandCount=G.handCount[curPlayer];
	if(afterHandCount!=initHandCount+2)
	{
	pass=0;
	printf("HandCount Not increased properly,handcoutn =%d\n", afterHandCount);
	}
	if(afterHandCount<initHandCount)
	{
	pass=0;
	printf("HandCount Decreased:ERROR\n");
	}

	if(pass==1)
	{
	printf("Test Passed with Player: %d and HandPos: %d\n",curPlayer,HandLoc);
	}
	else
	{
	printf("Bug in adventurer with Player: %d and HandPos: %d\n",curPlayer,HandLoc);
	}
	
}

return 0;
}
