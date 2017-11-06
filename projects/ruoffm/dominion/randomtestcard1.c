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
int initActions,afterActions,value,index, players, seed, pass, curPlayer, initHandCount, afterHandCount, HandLoc;
printf("Testing Village Card\n");
for(index=0;index<500;index++)
{
	pass=1;
	printf("Test: %d \n",index);
	players=rand()%4+1;
	seed=rand();
	initializeGame(players,k,seed, &G);
	curPlayer=rand()%players;
	G.whoseTurn=curPlayer;
	G.handCount[curPlayer]=rand()%MAX_HAND;
	initHandCount=G.handCount[curPlayer];
	HandLoc=rand()%MAX_HAND;
	G.hand[curPlayer][HandLoc]=village;
	initActions=G.numActions;
	printf("Initial States\n");
	printf("number of actions %d handcount %d\n",initActions, initHandCount);
	value=playCard(HandLoc,0,0,0,&G);
	afterActions=G.numActions;
	afterHandCount=G.handCount[curPlayer];
	printf("States after play\n");
	printf("number of actions %d handcount %d\n", afterActions,afterHandCount);
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

	
}
/*
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
*/		   
return 0;
}
