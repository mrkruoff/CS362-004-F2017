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
int pass=1;
printf("testing isGameOver\n");
printf("testing initial game state should not be Game over\n");
int gameOver=isGameOver(&G);
if (gameOver==1)
{
	pass=0;
	printf("Game is listed as over, should not be\n");
}

G.supplyCount[province]=0;
gameOver=isGameOver(&G);
printf("province=0 game should be over\n");
gameOver=isGameOver(&G);
if (gameOver==0)
{
	pass=0;
	printf("Error: Game is not over\n");
}

initializeGame(2,k,1,&G);
printf("testing isGameOver\n");
printf("testing initial game state should not be Game over\n");
gameOver=isGameOver(&G);
if (gameOver==1)
{
	pass=0;
	printf("Game is listed as over, should not be\n");
}
printf("setting 3 supply piles to 0, should be game over\n");
G.supplyCount[2]=0;
G.supplyCount[5]=0;
G.supplyCount[11]=0;
gameOver=isGameOver(&G);
if (gameOver==0)
{
	pass=0;
	printf("Error: Game is not over\n");
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
