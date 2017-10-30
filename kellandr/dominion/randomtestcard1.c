/* 	Author: 	Andrius Kelly
	Date:		10/28/2017
	Description: Random test for "adventurer" card
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#ifndef NOISY_TEST
#define NOISY_TEST 1
#endif
#ifndef NUM_TESTS 
#define NUM_TESTS 1000
#endif
//definine max supply to 60, for valid test
#ifndef MAX_SUPPLY
#define MAX_SUPPLY 60
#endif

void validRandomGameState(struct gameState* G);
int assertGameState(struct gameState *pre, struct gameState *post); 
void adventurerGameStateHelper(struct gameState *G, int handPos);
int assertDeckAndDiscard(struct gameState *G, struct gameState *pre, int p);

int main(int argc, char* argv[]){

	int testSeed = 1000;
	
	if(argc == 2){
		testSeed = atoi(argv[1]);
	}
	srand(testSeed);

	int numTests;
	int numChecks;
	int numFails;

	struct gameState G;
    struct gameState pre;
    int handPos;
    int whoseTurn;
    int bonus;

	//run series of tests with valid random gamestates
    numFails = numChecks = 0;
    numTests = NUM_TESTS;
	for(int i=0; i < numTests; i++){
		//create random gameState
		validRandomGameState(&G);
		whoseTurn = G.whoseTurn;
		handPos = rand() % (G.handCount[whoseTurn] + 1);
		bonus = rand();

		memcpy(&pre, &G, sizeof(struct gameState));
		cardEffect( adventurer,  rand(),  rand(), rand(), &G,  handPos, &bonus);
		adventurerGameStateHelper(&pre, handPos);
		numFails += assertGameState( &pre, &G);
		numChecks += 11 + 2 * pre.numPlayers;
		//decksize and discardsize should be equal
		numFails += assertDeckAndDiscard(&G, &pre, whoseTurn);
		numChecks += 2;
	}

	printf("%d Total Tests: %d Checks , %d Failures , %d Passes\n\n", numTests, numChecks, numFails, numChecks - numFails);

	return 0;
}



// ----------------------------FUNCTIONS-----------------------------

//prints gamestate Initializers
void printgameState(int k[], int kSize, int numPlayers){

}


/* populates gamestate with valid card enums and does not violate minimum or maximums
** k is filled with random nonrepeating enums from adventurer to treasure_map, inclusive
** gameSeed is set to rand()
** numPlayers is set between 1 and MAX_PLAYERS
*/
void validRandomGameState(struct gameState* G){

	int i, j;

	//randomly populate deck
	G->numPlayers = rand() % MAX_PLAYERS + 1;
	//first zero-out supplies
	for( i = 0; i<treasure_map+1; i++){
		G->supplyCount[i] = rand() % (MAX_SUPPLY + 1);
		G->embargoTokens[i] = rand() % (MAX_SUPPLY + 1);
	}

	G->outpostPlayed = rand() % (MAX_SUPPLY + 1);
	G->outpostTurn = rand() % G->numPlayers;
	G->whoseTurn = rand() % G->numPlayers;
	G->phase = rand() % 2;
	G->numActions = rand() % (MAX_SUPPLY + 1); /* Starts at 1 each turn */
	G->coins = rand() % (MAX_SUPPLY + 1); /* Use as you see fit! */
	G->numBuys = rand() % (MAX_SUPPLY + 1); /* Starts at 1 each turn */

	for ( i = 0; i < MAX_PLAYERS; i++){
		G->handCount[i] = rand() % MAX_HAND;
		G->deckCount[i] = rand() % MAX_DECK;
		G->discardCount[i] = rand() % MAX_DECK;

		for( j = 0; j < MAX_DECK; j++){
			G->hand[i][j] = rand() % (treasure_map + 1);
			G->deck[i][j] = rand() % (treasure_map + 1);
			G->discard[i][j] = rand() % (treasure_map + 1);
		}
	}

	for( j = 0; j < MAX_DECK; j++)
		G->playedCards[i] = rand() % (treasure_map + 1);

}


int assertDeckAndDiscard(struct gameState *G, struct gameState *pre, int p){
	int failures = 0;
	if (G->deckCount[p] != pre->deckCount[p] ){
		failures++;
		if (NOISY_TEST) printf("  FAIL: gameState.deckCount = %d expected %d\n", G->deckCount[p], pre->deckCount[p] );	
	}
	if (G->discardCount[p] != pre->discardCount[p] ){
		failures++;
		if (NOISY_TEST) printf("  FAIL: gameState.discardCount = %d expected %d\n", G->discardCount[p], pre->discardCount[p] );	
	}
	return failures;
}


//sets the gamestate to its expected value based on the card effect
void adventurerGameStateHelper(struct gameState *G, int handPos){
	
	int i;
	int p = G->whoseTurn;
//printf("hand: %d, deck: %d, discard: %d\n", G->handCount[p], G->deckCount[p], G->discardCount[p]);
	//treasure picked flag
	int t_flag = 0;
	
	//drawn array to store drawn cards
	int drawnCard;
	int drawn[MAX_DECK];
	int drawnCount = 0;

	while(t_flag < 2 ) {

		if ( G->deckCount[p] == 0 ){
						
			if ( G->discardCount[p] == 0 ){
				//nothing to do, so break

				break;
			} 

			else {
				//add discarded cards to deck
				for( i = 0 ; i < G->discardCount[p]; i++ ){
					G->deck[p][i] = G->discard[p][i];
				}
				G->deckCount[p] = G->discardCount[p];
				G->discardCount[p] = 0;
			}

		}

		//draw until treasure cards are picked
		drawnCard = G->deck[p][ G->deckCount[p]-1 ];
		G->deckCount[p] -= 1;

		//if treasure picked, add to hand
		if( drawnCard == copper || drawnCard == silver || drawnCard == gold){
			t_flag++;
			G->hand[p][ G->handCount[p] ] = drawnCard;
			G->handCount[p] += 1;
		}
		else{		//else add to drawn
			drawn[drawnCount] = drawnCard;
			drawnCount++;
		}
	}

	//add drawn cards to discard pile
	for( i = 0 ; i < drawnCount; i++){
		G->discard[p][ G->discardCount[p] ] = drawn[i];
		G->discardCount[p] += 1;
	}

	//remove adventurer card from hand and add to played
	G->hand[p][handPos] = G->hand[p][ G->handCount[p]-1 ];
	G->handCount[p] -= 1;

	G->playedCards[ G->playedCardCount ] = adventurer;
	G->playedCardCount += 1;

//printf("hand: %d, deck: %d, discard: %d\n", G->handCount[p], G->deckCount[p], G->discardCount[p]);

}

//Helper Function: checks integer property of pre and post gameState
int testStateInt(int prop1, int prop2, const char* name){
	if (prop1 != prop2 ){
		if (NOISY_TEST) 
			printf("  FAIL: gameState.%s = %d expected %d\n", name, prop2, prop1 );
		return 1;
	}
	return 0;
}


//Helper Function: checks array property of pre and post gameState
int testStateArray(int a1[], int a2[], int size, const char* name){
	for(int i=0; i< size; i++ ) {
		if ( a1[i] != a2[i] ) {
			if (NOISY_TEST) 
				printf("  FAIL: gameState.%s array did not match expected\n", name);
			return 1;
		}
	}
	return 0;
}


/*   
**	 assertGameState() checks between pre and post gamstate and returns differences
**   prints differences to console if( NOISY_TEST )
**     performs 11 + 2 * numPlayers total tests
**
**	 NOTE: cannot compare deck and discardelements due to randomness of shuffling
*/
int assertGameState(struct gameState *pre, struct gameState *post){
	
	int numPlayers = pre->numPlayers;

	char buffer[100];

	int changes = 0;
	
	changes += testStateInt(pre->numPlayers, post->numPlayers, "numPlayers");
	changes += testStateArray(pre->supplyCount, post->supplyCount, treasure_map+1, "supplyCount");
	changes += testStateArray(pre->embargoTokens, post->embargoTokens, treasure_map+1, "embargoTokens");
	changes += testStateInt(pre->outpostPlayed, post->outpostPlayed, "outpostPlayed");
	changes += testStateInt(pre->whoseTurn, post->whoseTurn, "whoseTurn");
	changes += testStateInt(pre->phase, post->phase, "phase");
	changes += testStateInt(pre->numActions, post->numActions, "numActions");
	changes += testStateInt(pre->coins, post->coins, "coins");
	changes += testStateInt(pre->numBuys, post->numBuys, "numBuys");
	changes += testStateArray(pre->playedCards, post->playedCards, pre->playedCardCount, "playedCards");
	changes += testStateInt(pre->playedCardCount, post->playedCardCount, "playedCardCount");

	for( int i=0; i < numPlayers; i++){

		sprintf(buffer, "hand[] for player %d", i);	
		changes += testStateArray(pre->hand[i], post->hand[i], pre->handCount[i], buffer);
		
		sprintf(buffer, "handCount for player %d", i);	
		changes += testStateInt(pre->handCount[i], post->handCount[i], buffer);

	}

	return changes;
} 
