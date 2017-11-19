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

int index, players, seed, pass, curPlayer,HandLoc,sizeofHand, correct;
printf("Testing Village Card\n");
for(index=0;index<500;index++)
{
	if(index==235)
	{
		printf("DEBUG");
	}
	pass=1;
	printf("Test: %d \n",index);
	players=(rand()%(4+1-2))+2;
	seed=rand();
	initializeGame(players,k,seed, &G);
	curPlayer=rand()%5;
	G.whoseTurn=curPlayer;
	G.handCount[curPlayer]=rand()%MAX_HAND;
	sizeofHand=G.handCount[curPlayer];
	correct=sizeofHand+2;
	printf("current size of hand %d\n", sizeofHand);
	HandLoc=rand()%MAX_HAND;
	G.hand[curPlayer][HandLoc]=smithy;	
	playCard(HandLoc,0,0,0,&G);
	sizeofHand=G.handCount[curPlayer];
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
}
	
/*		   
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
	
	*/	   
return 0;
}
