/* 	Author: 	Andrius Kelly
	Date:		10/13/2017
	Description: Unit test for "drawCard()" function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//set to 1 to remove prints on every test
#define NOISY_TEST 1

//checks that the gamestate is the same for everything that should be unchanged
int gameStateChanges(int player, int numPlayers, struct gameState *pre, struct gameState *post);
int checkHandAndDeck(struct gameState* G, int p, int handCount, int hand[], int deckCount, int deck[]);


int main(void){

	//gamestate vars
	int seed = 1000;
	int numPlayers = 2;    
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    struct gameState pre;

   //vars for testing
    int testCount;
    int failures;
    int p;
    int handCount;
    int deckCount;

	testCount = failures = 0;

	//initialize new game
	initializeGame(numPlayers, k, seed, &G);	
	p = G.whoseTurn;

	printf ("Testing drawCard():\n");

//VALID INPUT
	if(NOISY_TEST) 
			printf("TESTING VALID INPUT\n");

//TEST 1: drawcard on full deck
	handCount = pre.handCount[p];
	deckCount = pre.deckCount[p];

	if(NOISY_TEST) 
		printf("Testing drawCard() on player %d, deck of size %d,\n", p, deckCount);
	//copy pre gamestate
	memcpy(&pre, &G, sizeof(struct gameState));

	//pop card off top of deck and into hand
	pre.hand[p][handCount] = pre.deck[p][deckCount-1];
	pre.handCount[p] += 1;
	pre.deckCount[p] -= 1;

	drawCard(p, &G);

	//check gamestate changes
	failures += gameStateChanges(p, numPlayers, &pre, &G);	
	testCount += 11 + 6 * numPlayers;	


//TEST 2:  draw if deck and discard are empty (should do nothing)
	G.deckCount[p] = G.discardCount[p] = 0; 

	if(NOISY_TEST) 
		printf("Testing drawCard() on player %d, deck of size %d, discard of size %d\n", p, G.deckCount[p], G.discardCount[p]);

	//copy pre gamestate
	memcpy(&pre, &G, sizeof(struct gameState));

	drawCard(p, &G);

	//check gamestate changes
	failures += gameStateChanges(p, numPlayers, &pre, &G);	
	testCount += 11 + 6 * numPlayers;


//TEST 3: if deck is empty and discard > 0, 
//  new deckCount = discardCount-1, new hand = hand+1, new discard = 0
	
	G.deckCount[p] = 0; 
	G.discardCount[p] = 1;

	if(NOISY_TEST) 
		printf("Testing drawCard() on player %d, deck of size %d, discard of size %d\n", p, G.deckCount[p], G.discardCount[p]);

	//copy pre gamestate
	memcpy(&pre, &G, sizeof(struct gameState));

	handCount = pre.handCount[p];
	pre.hand[p][handCount] = pre.discard[p][0];	
	pre.handCount[p] += 1;
	pre.deckCount[p] = 0;

	drawCard(p, &G);

	//check gamestate changes
	failures += gameStateChanges(p, numPlayers, &pre, &G);	
	testCount += 11 + 6 * numPlayers;
	

//INVALID INPUT

//print results
	printf("%d Total Tests: %d Failures, %d Passes\n\n", testCount, failures, testCount-failures);

	return 0;
}



//---------------------------     FUNCTIONS        --------------------------


//Helper Function: checks integer property of pre and post gameState
int testStateInt(int prop1, int prop2, const char* name){
	if (prop1 != prop2 ){
		if (NOISY_TEST) 
			printf(" FAIL: gameState.%s not as expected\n", name );
		return 1;
	}
	return 0;
}


//Helper Function: checks array property of pre and post gameState
int testStateArray(int a1[], int a2[], int size, const char* name){
	if( memcmp(a1, a2, size) ){
		if (NOISY_TEST) 
			printf(" FAIL: gameState.%s not as expected\n", name);
		return 1;
	}
	return 0;
}


/*   
**	 gameStateChanges() checks any differences between pre and post gamstate 
**   gameStateChanges() will return number of differences and 
**     prints differences to console if( NOISY_TEST )
**     performs 11 + 6 * numPlayers total tests
*/
int gameStateChanges(int player, int numPlayers, struct gameState *pre, struct gameState *post){
	
	char buffer[100];

	int changes = 0;
	
	changes += testStateInt(pre->numPlayers, post->numPlayers, "numPlayers");
	changes += testStateArray(pre->supplyCount, post->supplyCount, sizeof(pre->supplyCount), "supplyCount");
	changes += testStateArray(pre->embargoTokens, post->embargoTokens, sizeof(pre->embargoTokens), "embargoTokens");
	changes += testStateInt(pre->outpostPlayed, post->outpostPlayed, "outpostPlayed");
	changes += testStateInt(pre->whoseTurn, post->whoseTurn, "whoseTurn");
	changes += testStateInt(pre->phase, post->phase, "phase");
	changes += testStateInt(pre->numActions, post->numActions, "numActions");
	changes += testStateInt(pre->coins, post->coins, "coins");
	changes += testStateInt(pre->numBuys, post->numBuys, "numBuys");
	changes += testStateArray(pre->playedCards, post->playedCards, sizeof(pre->playedCards), "playedCards");
	changes += testStateInt(pre->playedCardCount, post->playedCardCount, "playedCardCount");

	for( int i=0; i < numPlayers; i++){

		sprintf(buffer, "discardCount for player %d", i);
		changes += testStateInt(pre->discardCount[i], post->discardCount[i], buffer);

		sprintf(buffer, "discard[] for player %d", i);
		changes += testStateArray(pre->discard[i], post->discard[i], sizeof(pre->discard[i]), buffer);

		sprintf(buffer, "handCount for player %d", i);	
		changes += testStateInt(pre->handCount[i], post->handCount[i], buffer);

		sprintf(buffer, "hand[] for player %d", i);	
		changes += testStateArray(pre->hand[i], post->hand[i], sizeof(pre->hand[i]), buffer);

		sprintf(buffer, "deckCount for player %d", i);
		changes += testStateInt(pre->deckCount[i], post->deckCount[i], buffer);

		sprintf(buffer, "deck[] for player %d", i);
		changes += testStateArray( pre->deck[i], post->deck[i], sizeof(pre->deck[i]), buffer);
	}

	return changes;
} 