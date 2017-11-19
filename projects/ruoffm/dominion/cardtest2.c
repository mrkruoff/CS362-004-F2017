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
G.hand[1][0]=adventurer;
G.whoseTurn=1;
int pass=1;
printf("testing adventurer\n");
//Test Adventurere
int initHandCount=G.handCount[1];
int value=playCard(0,0,0,0,&G);
int afterHandCount=G.handCount[1];
printf("Testing handCount size, should not be greater than 2 than initial. initial= %d,after=%d\n",initHandCount,afterHandCount);
if(afterHandCount-initHandCount>2)
{
	pass=0;
	printf("HandCount Too Large");
}
if(afterHandCount<initHandCount)
{
	pass=0;
	printf("HandCount Decreased:ERROR");
}
printf("testing return value\n");
if(value!=0)
{
	pass=0;
	printf("incorrect return value, was not 0\n");
}
printf("storing copper and silver in hand for proper increase\n");
initializeGame(2,k,1,&G);
G.whoseTurn=1;
G.hand[1][0]=adventurer;
G.hand[1][1]=copper;
G.hand[1][2]=silver;
initHandCount=G.handCount[1];
value=playCard(0,0,0,0,&G);
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
printf("testing return value\n");
if(value!=0)
{
	pass=0;
	printf("incorrect return value, was not 0, was %d\n", value);
}

if(pass==1)
{
	printf("Test Passed\n");
}
else
{
	printf("Bug in adventurer\n");
}
			   
return 0;
}
